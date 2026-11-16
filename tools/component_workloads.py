#!/usr/bin/env python3
"""Deterministic B04 cohorts and independent exact SQLite prefix observations.

The oracle is experiment code. It never calls native planning/runtime helpers or
uses SQLite floating AVG; the explicit output map declares numeric formatting.
"""
from collections import Counter
from copy import deepcopy
from fractions import Fraction
import argparse
import hashlib
import json
from pathlib import Path
import random
import sqlite3

from run_measurements import indexed_options, require

L3_SQL = 'SELECT DISTINCT g1.a,g1.b,g2.c,g3.d FROM g1,g2,g3 WHERE g1.b=g2.b AND g2.c=g3.c'
L5_FROM = ' FROM graph g1,graph g2,graph g3,graph g4,graph g5 WHERE g1.dst=g2.src AND g2.dst=g3.src AND g3.dst=g4.src AND g4.dst=g5.src'
L5_DISTINCT = 'SELECT DISTINCT g2.src,g3.src,g4.src,g5.src' + L5_FROM
L5_GROUP = 'SELECT g3.src,g3.dst,COUNT(*)' + L5_FROM + ' GROUP BY g3.src,g3.dst'
OP_FROM = ' FROM r0,r1 WHERE r0.c1=r1.c0'


def catalog(tables):
    return {'schema_version': 1, 'catalog': {'version': 1, 'tables': [
        {'name': name, 'source_schema_version': 1, 'constraints': [], 'key_hints': [],
         'statistics': {'distinct_counts': []},
         'columns': [{'name': column, 'nullable': False, 'type': 'int64'} for column in columns]}
        for name, columns in tables.items()]}}


def event(operation, table, pair, phase='updates'):
    return {'operation': operation, 'table': table, 'values': list(pair), 'phase': phase}


def layered_events(family, width, cycles=1):
    """Adjacent complete layers; every physical fact is a unique unit pair."""
    require(family in ('l3_full_rows','l5_distinct_count','l5_group_count'), 'unknown layered cohort family')
    require(type(width) is int and 1 <= width <= 8 and type(cycles) is int and 1 <= cycles <= 16, 'invalid layered cohort bounds')
    layers = [[layer*100000+index+1 for index in range(width)] for layer in range(4 if family == 'l3_full_rows' else 6)]
    facts = [(('g'+str(layer+1)) if family == 'l3_full_rows' else 'graph', (left, right))
             for layer in range(len(layers)-1) for left in layers[layer] for right in layers[layer+1]]
    shuffled = list(facts)
    random.Random(0xB040+width+(0x100 if family == 'l3_full_rows' else 0)).shuffle(shuffled)
    events = [event('+', table, pair, 'charged_load') for table, pair in shuffled]
    if family != 'l5_distinct_count':
        first = facts[:width*width]
        center = facts[len(facts)//2]
        for _ in range(cycles):
            events.extend(event('-', table, pair) for table, pair in reversed(first))
            events.extend(event('+', table, pair) for table, pair in first)
            events.extend([event('-', *center), event('+', *center)])
    return events


def operational_events(width, cycles):
    require(type(width) is int and 1 <= width <= 8 and type(cycles) is int and 1 <= cycles <= 16, 'invalid operational cohort bounds')
    facts = [('r0', (key, 100+middle)) for key in range(1,width+1) for middle in range(width)]
    facts += [('r1', (100+middle, sign*value)) for middle in range(width) for value in range(1,width+1) for sign in (-1,1)]
    random.Random(0x0B04+width).shuffle(facts)
    events = [event('+', table, pair, 'charged_load') for table, pair in facts]
    for _ in range(cycles):
        # Two cancelling edits share a net-batch endpoint; numeric changes keep
        # the projected set/group alive while bag/aggregate annotations change.
        events.extend([event('+','r1',(100,0)), event('-','r1',(100,0)),
                       event('-','r1',(100,1)), event('+','r1',(100,1))])
    removed = [(1,100+middle) for middle in range(width)]
    events.extend(event('-','r0',pair) for pair in removed)
    events.extend(event('+','r0',pair) for pair in removed)
    return events


def numeric(value, scale=0):
    """Canonical NUMERIC with exact round-half-away-from-zero."""
    require(type(scale) is int and 0 <= scale <= 38, 'invalid NUMERIC scale')
    value = Fraction(value)
    scaled = abs(value)*10**scale
    integer, remainder = divmod(scaled.numerator, scaled.denominator)
    integer += 2*remainder >= scaled.denominator
    digits = str(integer).rjust(scale+1,'0')
    if scale:
        digits = (digits[:-scale]+'.'+digits[-scale:]).rstrip('0').rstrip('.')
    if value < 0 and integer:
        digits = '-'+digits
    return {'decimal': digits}


def bind_oracle(sql, kind='rows', **mapping):
    return {'kind': kind, 'source_sql_sha256': hashlib.sha256(sql.encode()).hexdigest(), **mapping}


def evaluate_request(request, specification):
    """Recompute all physical prefixes; transactions observe selected endpoints."""
    require(specification['source_sql_sha256'] == hashlib.sha256(request['program']['sql'].encode()).hexdigest(), 'oracle/query binding differs')
    database = sqlite3.connect(':memory:')
    tables = {table['name']: table for table in request['program']['catalog']['catalog']['tables']}
    for name, table in tables.items():
        require(name.replace('_','').isalnum() and all(column['name'].replace('_','').isalnum() for column in table['columns']), 'non-cohort SQL identifier')
        columns = ','.join(column['name']+' INTEGER NOT NULL' for column in table['columns'])
        database.execute('CREATE TABLE '+name+'('+columns+')')
    live, previous_rows, previous_groups = set(), set(), {}

    def observe(offset):
        nonlocal previous_rows, previous_groups
        frame = {'physical_input_end': offset}
        if specification['kind'] == 'rows':
            bag = Counter(database.execute(request['program']['sql']))
            current = set(bag)
            frame.update(rows=[list(row) for row in sorted(current)], cardinality=len(current),
                         bag=[{'values': list(row), 'multiplicity': weight} for row, weight in sorted(bag.items())],
                         delta=[{'operation': operation, 'values': list(row)}
                                for operation, rows in [('-',previous_rows-current), ('+',current-previous_rows)] for row in sorted(rows)])
            previous_rows = current
        else:
            require(specification['kind'] == 'aggregate', 'unknown independent oracle kind')
            groups = {}
            for record in database.execute(specification['oracle_sql']):
                key = tuple(record[index] for index in specification['key_columns'])
                values = []
                for field in specification['outputs']:
                    kind = field['kind']
                    if kind == 'average':
                        total, count = record[field['sum_column']], record[field['count_column']]
                        value = numeric(Fraction(total,count),field.get('scale',18)) if count else None
                    else:
                        value = record[field['column']]
                        require(kind in ('integer','numeric'), 'unknown oracle output mapping')
                        if kind == 'numeric' and value is not None:
                            value = numeric(value,field.get('scale',0))
                    values.append(value)
                require(key not in groups, 'duplicate SQL oracle group')
                groups[key] = values
            frame['groups'] = [{'key': list(key), 'values': values} for key, values in sorted(groups.items())]
            frame['replacements'] = [{'key': list(key), 'before': previous_groups.get(key), 'after': groups.get(key)}
                                     for key in sorted(set(previous_groups)|set(groups)) if previous_groups.get(key) != groups.get(key)]
            previous_groups = groups
        return frame

    initial = observe(0)
    frames = []
    for offset, item in enumerate(request['events'],1):
        name, values = item['table'], tuple(item['values'])
        require(name in tables and len(values) == 2 and all(type(value) is int for value in values), 'invalid oracle physical input')
        key = (name,values)
        if item['operation'] == '+':
            require(key not in live, 'duplicate oracle insertion')
            live.add(key)
            database.execute('INSERT INTO '+name+' VALUES(?,?)',values)
        else:
            require(item['operation'] == '-' and key in live, 'absent oracle erase')
            live.remove(key)
            columns = tables[name]['columns']
            database.execute('DELETE FROM '+name+' WHERE '+columns[0]['name']+'=? AND '+columns[1]['name']+'=?',values)
        frames.append(observe(offset))
    database.close()
    return {'initial': initial, 'epochs': frames}


def base_request(identifier, sql, tables, events, output, backend='reference_ordered_v1'):
    physical = indexed_options()
    if backend == 'reference_ordered_v1':
        del physical['indexed_storage']
        physical['schema_version'] = 1
    return {'schema_version': 1, 'case_id': identifier, 'query_family': identifier,
            'command': 'verify', 'output': output, 'warmup_passes': 0, 'measured_passes': 1,
            'limits': {'input_events': 1000000, 'output_records': 10000000, 'output_bytes': 64*1024*1024},
            'program': {'sql': sql, 'catalog': tables}, 'events': events,
            'native': {'physical_options': physical, 'memory_limit_bytes': 256*1024*1024, 'work_limit': 10000000}}


def cohort_widths(widths):
    """Reject empty/repeated strata before constructing ambiguous arm IDs."""
    result = tuple(widths)
    require(result and all(type(width) is int and 1 <= width <= 8 for width in result), 'invalid cohort widths')
    require(len(set(result)) == len(result), 'duplicate cohort width')
    return result


def build_operational_cohorts(widths=(2,4,8), cycles=2):
    """Explicit finite arms; comparisons declare every intended request change."""
    arms, comparisons = [], []
    tables = catalog({'r0': ('c0','c1'), 'r1': ('c0','c1')})
    for width in cohort_widths(widths):
        events = operational_events(width,cycles)
        for backend in ('reference_ordered_v1','indexed_chained_v1'):
            stem = f'w{width}-{backend}'
            sql = 'SELECT DISTINCT r0.c0'+OP_FROM
            common = base_request(stem,sql,tables,events,'none',backend)
            common['native']['mode'] = 'delta'
            common['session'] = {'transport_batch_size': 4, 'output_action': 'discard', 'durability': 'volatile',
                                 'checkpoint_interval': 0, 'recover_after': [], 'consumer_delay_us': 0,
                                 'state_directory': '__NEW_STATE_DIRECTORY__'}
            local = {}

            def arm(name, adapter, request, oracle):
                identifier = stem+'-'+name
                arms.append({'id': identifier, 'adapter': adapter, 'request': request, 'oracle': oracle})
                local[name] = identifier

            arm('transport','session',deepcopy(common),bind_oracle(sql))
            variants = [
                ('single','updates',{'session.transport_batch_size':1},'transport'),
                ('serialize','output',{'session.output_action':'serialize'},'transport'),
                ('wal','recovery',{'session.durability':'wal'},'transport'),
                ('checkpoint','recovery',{'session.checkpoint_interval':8},'wal'),
                ('restart','recovery',{'session.recover_after':[8]},'wal'),
                ('durable','output',{'session.output_action':'durable'},'wal'),
                ('slow_durable','output',{'session.consumer_delay_us':100},'durable'),
                ('maintenance','output',{'native.mode':'maintenance','session.output_action':'maintenance'},'transport'),
            ]
            requests = {'transport': common}
            for name, axis, changes, baseline in variants:
                request = deepcopy(requests[baseline])
                for path, value in changes.items():
                    section, key = path.split('.')
                    request[section][key] = value
                requests[name] = request
                arm(name,'session',request,bind_oracle(sql))
                comparisons.append({'id':stem+'-'+name,'axis':axis,'baseline':local[baseline],'variant':local[name],
                                    'changed_paths':sorted(changes),'unit':'physical_inputs_and_actual_output_protocol'})
            # The full head has 2*w^3 loaded rows and a transient peak of
            # 2*w^3+w while r1(100,0) is present. Its output-action contrast
            # preserves this query, its actual tree and every snapshot demand.
            # The projected-head arms above are a separate query stratum.
            full_sql = 'SELECT DISTINCT r0.c0,r0.c1,r1.c1'+OP_FROM
            full = deepcopy(common)
            full['program']['sql'] = full_sql
            full['output'] = 'delta_and_snapshot'
            arm('full_discard','session',full,bind_oracle(full_sql))
            serialized = deepcopy(full)
            serialized['session']['output_action'] = 'serialize'
            arm('full_serialize','session',serialized,bind_oracle(full_sql))
            comparisons.append({'id':stem+'-full-serialize','axis':'output','baseline':local['full_discard'],
                                'variant':local['full_serialize'],'changed_paths':['session.output_action'],
                                'unit':'same_full_head_signed_delta_and_snapshot_obligations'})
            # Net batching changes transactions only; output stays at the same
            # source-input multiples of four, including the final partial.
            bag_sql = 'SELECT r0.c0'+OP_FROM
            single = base_request(stem,bag_sql,tables,events,'compressed_bag',backend)
            single['native'].update(transaction_batch_size=1,observation_interval=4)
            net = deepcopy(single)
            net['native']['transaction_batch_size'] = 4
            arm('rows_single','rows',single,bind_oracle(bag_sql))
            arm('rows_net','rows',net,bind_oracle(bag_sql))
            comparisons.append({'id':stem+'-net','axis':'updates','baseline':local['rows_single'],'variant':local['rows_net'],
                                'changed_paths':['native.transaction_batch_size'],'unit':'common_source_observation_endpoints'})
            set_request = base_request(stem,sql,tables,events,'cardinality',backend)
            set_request['native']['mode'] = 'maintenance'
            arm('unweighted','set',set_request,bind_oracle(sql))
            bag_request = base_request(stem,bag_sql,tables,events,'compressed_bag',backend)
            arm('bag','rows',bag_request,bind_oracle(bag_sql))
            # Group and annotation variables lie on r0's full native scope;
            # the endpoint-head SUM(r1.c1) variant is not free-connex here.
            aggregate_sql = 'SELECT r0.c0,COUNT(*),SUM(r0.c1),AVG(r0.c1)'+OP_FROM+' GROUP BY r0.c0'
            oracle_sql = 'SELECT r0.c0,COUNT(*),SUM(r0.c1),SUM(r0.c1),COUNT(r0.c1)'+OP_FROM+' GROUP BY r0.c0'
            aggregate = base_request(stem,aggregate_sql,tables,events,'groups_full',backend)
            arm('aggregate','aggregate',aggregate,bind_oracle(aggregate_sql,'aggregate',oracle_sql=oracle_sql,key_columns=[0],outputs=[
                {'kind':'integer','column':0},{'kind':'integer','column':1},{'kind':'numeric','column':2},
                {'kind':'average','sum_column':3,'count_column':4,'scale':18}]))
            comparisons.extend([
                {'id':stem+'-set-bag','axis':'sql_semantics','baseline':local['unweighted'],'variant':local['bag'],
                 'changed_paths':['adapter','native.mode','output','program.sql'],'unit':'declared_distinct_rows_vs_compressed_multiplicity'},
                {'id':stem+'-bag-aggregate','axis':'sql_semantics','baseline':local['bag'],'variant':local['aggregate'],
                 'changed_paths':['adapter','output','program.sql'],'unit':'declared_compressed_rows_vs_groups_and_exact_annotations'},
            ])
    return {'schema_version':1,'kind':'b04_operational_cohorts','arms':arms,'comparisons':comparisons,
            'scope':'exact finite unit-set integer-pair source; widths and cycles explicit; annotation semantics intentionally differ; actual normalized tree identity must be reported, not presumed equal'}


def build_baseline_cohorts(widths=(2,4,8), cycles=2):
    """Matched original-program/native/SQLite output demands on exact layers.

    These are whole implementations with different layouts, scalar encodings
    and launchers. They do not isolate template dispatch or language overhead.
    """
    arms, comparisons = [], []
    for width in cohort_widths(widths):
        for family, sql, tables, output in [
                ('l3_full_rows',L3_SQL,catalog({'g1':('a','b'),'g2':('b','c'),'g3':('c','d')}),'delta_and_snapshot'),
                ('l5_distinct_count',L5_DISTINCT,catalog({'graph':('src','dst')}),'cardinality'),
                ('l5_group_count',L5_GROUP,catalog({'graph':('src','dst')}),'groups_full')]:
            stem = f'w{width}-{family}'
            events = layered_events(family,width,cycles)
            request = base_request(stem,sql,tables,events,output)
            request['query_family'] = family
            oracle = bind_oracle(sql) if family != 'l5_group_count' else bind_oracle(
                sql,'aggregate',oracle_sql=sql,key_columns=[0,1],outputs=[
                    {'kind':'integer','column':0},{'kind':'integer','column':1},{'kind':'integer','column':2}])
            legacy = 'legacy_scala' if family == 'l3_full_rows' else 'legacy_cpp'
            controls = [(legacy,legacy,deepcopy(request)),('sqlite','sqlite',deepcopy(request))]
            for backend in ('reference_ordered_v1','indexed_chained_v1'):
                native = base_request(stem,sql,tables,events,output,backend)
                native['query_family'] = family
                if family != 'l5_group_count':
                    # Cardinality folds genuine signed changes into one scalar;
                    # it does not drain a full snapshot after every event.
                    native['native']['mode'] = 'delta'
                controls.append((backend,'aggregate' if family == 'l5_group_count' else 'set',native))
            for name, adapter, value in controls:
                arms.append({'id':stem+'-'+name,'adapter':adapter,'request':value,'oracle':deepcopy(oracle)})
            for backend in ('reference_ordered_v1','indexed_chained_v1'):
                comparisons.append({'id':stem+'-'+backend,'baseline':stem+'-'+legacy,'variant':stem+'-'+backend,
                                    'axis':'whole_implementation','unit':output+' after every physical event; charged load included'})
                comparisons.append({'id':stem+'-sqlite-'+backend,'baseline':stem+'-sqlite','variant':stem+'-'+backend,
                                    'axis':'incremental_vs_recomputation','unit':output+' after every physical event; charged load included'})
    return {'schema_version':1,'kind':'b04_matched_baseline_cohorts','arms':arms,'comparisons':comparisons,
            'scope':'finite positive uint32 unit facts; original l5 distinct program is insert-only; full rows/signed rows or full groups are actually drained every event; cross-framework layout/parser/formatting/scalar/JVM costs remain inseparable'}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--width',type=int,action='append')
    parser.add_argument('--cycles',type=int,default=2)
    args = parser.parse_args()
    manifest = build_operational_cohorts(tuple(args.width or [2,4,8]),args.cycles)
    with args.output.open('x') as stream:
        stream.write(json.dumps(manifest,indent=2)+'\n')


if __name__ == '__main__':
    main()
