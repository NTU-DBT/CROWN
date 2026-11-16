#!/usr/bin/env python3
"""Exact finite SQLite recomputation control for the B04 matched study.

Every event changes one unit fact and re-executes the declared SQL. Full rows
and groups are fetched; signed rows are computed from consecutive full sets.
This Python/SQLite process is a whole implementation, not a native operator.
"""
import hashlib
import json
from pathlib import Path
import sqlite3
import sys
from time import monotonic_ns

from run_measurements import require


def run(path):
    started = monotonic_ns()
    require(path.stat().st_size <= 64*1024**2, 'SQLite request exceeds 64MiB')
    request = json.loads(path.read_text())
    read_ns = monotonic_ns()-started
    verify = request['command'] == 'verify'
    require(request['command'] in ('verify','measure'), 'unsupported SQLite command')
    output = request['output']
    require(output in ('cardinality','delta_and_snapshot','groups_full'), 'unsupported SQLite output')
    require(type(request['warmup_passes']) is int and 0 <= request['warmup_passes'] <= 5 and
            type(request['measured_passes']) is int and request['measured_passes'] == 1, 'invalid SQLite pass grant')
    require(0 < len(request['events']) <= request['limits']['input_events'] <= 1000000, 'invalid SQLite input grant')
    tables = request['program']['catalog']['catalog']['tables']
    sql = request['program']['sql']
    # Only generated pair-table cohorts enter this experimental adapter. SQL
    # remains the original query, including its actual DISTINCT/grouping.
    columns = {table['name']:[column['name'] for column in table['columns']] for table in tables}
    require(all(len(names) == 2 and all(name.replace('_','').isalnum() for name in [table,*names])
                for table,names in columns.items()), 'invalid finite SQLite catalog')
    live = set()
    for item in request['events']:
        table, values = item['table'], tuple(item['values'])
        require(table in columns and len(values) == 2 and all(type(value) is int for value in values), 'invalid SQLite event')
        key = (table,values)
        if item['operation'] == '+':
            require(key not in live, 'duplicate SQLite input'); live.add(key)
        else:
            require(item['operation'] == '-' and key in live, 'absent SQLite input'); live.remove(key)
    del live
    shared_ns = monotonic_ns()-started-read_ns
    clock = lambda value: None if verify else value
    passes = []
    for index in range(request['warmup_passes']+request['measured_passes']):
        initializing = monotonic_ns()
        database = sqlite3.connect(':memory:')
        for table,names in columns.items():
            database.execute('CREATE TABLE '+table+'('+','.join(name+' INTEGER NOT NULL' for name in names)+',PRIMARY KEY('+','.join(names)+'))')
        initialize_ns = monotonic_ns()-initializing
        previous, epochs, records, captured = set(), [], 0, 0
        looping = monotonic_ns()
        for offset,item in enumerate(request['events'],1):
            table, names, values = item['table'], columns[item['table']], item['values']
            applying = monotonic_ns()
            if item['operation'] == '+':
                database.execute('INSERT INTO '+table+' VALUES(?,?)',values)
            else:
                database.execute('DELETE FROM '+table+' WHERE '+names[0]+'=? AND '+names[1]+'=?',values)
            apply_ns = monotonic_ns()-applying
            observing = monotonic_ns()
            if output == 'cardinality':
                # Count the actual inner DISTINCT projection, never COUNT(*)
                # of the joined witnesses.
                count = database.execute('SELECT COUNT(*) FROM ('+sql+')').fetchone()[0]
                actual, emitted = count, 1
            else:
                rows = database.execute(sql).fetchall()
                if output == 'groups_full':
                    emitted = len(rows)
                    actual = [{'key':list(row[:2]),'values':list(row)} for row in rows] if verify else None
                else:
                    current = set(rows)
                    require(len(current) == len(rows), 'full-row SQL must be DISTINCT')
                    deleted, inserted = previous-current, current-previous
                    emitted = len(current)+len(deleted)+len(inserted)
                    actual = {'rows':[list(row) for row in sorted(current)],
                              'delta':[{'operation':operation,'values':list(row)}
                                       for operation,changes in [('-',deleted),('+',inserted)] for row in sorted(changes)]} if verify else None
                    previous = current
            output_ns = monotonic_ns()-observing
            records += emitted
            require(records <= request['limits']['output_records'], 'SQLite output record limit exceeded')
            if verify:
                captured += len(json.dumps(actual,separators=(',',':')).encode())
                require(captured <= request['limits']['output_bytes'], 'SQLite capture-byte limit exceeded')
            epochs.append({'sequence':offset,'phase':item.get('phase','updates'),'apply_ns':clock(apply_ns),
                           'output_ns':clock(output_ns),'release_ns':None,'output_records':emitted,
                           'actual':actual if verify else None})
        loop_ns = monotonic_ns()-looping
        destroying = monotonic_ns(); database.close(); teardown_ns = monotonic_ns()-destroying
        passes.append({'warmup':index < request['warmup_passes'],'initialize_ns':clock(initialize_ns),
                       'loop_wall_ns':clock(loop_ns),'teardown_ns':clock(teardown_ns),'output_records':records,
                       'native_memory_before_teardown':None,'epochs':epochs})
    return {'schema_version':1,'implementation':'sqlite_recomputation_v1','case_id':request['case_id'],
            'query_family':request['query_family'],'command':request['command'],'output':output,
            'source_sql_sha256':hashlib.sha256(sql.encode()).hexdigest(),'sqlite_version':sqlite3.sqlite_version,
            'read_request_ns':clock(read_ns),'shared_program_ns':clock(shared_ns),'passes':passes,
            'scope':'fresh in-memory database per pass; every unit fact and required full observation included; default SQLite transaction remains open until close; no durability; Python conversion, comparison and report DTO costs remain; process RSS includes interpreter and all passes'}


if __name__ == '__main__':
    print(json.dumps(run(Path(sys.argv[1])),separators=(',',':')))
