#!/usr/bin/env python3
"""Independent SQLite snapshots and exact typed sorting for public snapshot top-k.

SQLite executes every finite source/query update. Its AVG is never read: SUM and
COUNT feed exact Fraction rounding at the declared display scale. A separate
symbolic one-row case checks UINT64_MAX weights without expanding copies. No
production comparator, snapshot or expected result enters the oracle.
"""
import argparse
from datetime import date
from fractions import Fraction
from functools import cmp_to_key
import json
from pathlib import Path
import sqlite3
import subprocess

MAXIMUM=(1<<64)-1


def key(value):
    return json.dumps(value,sort_keys=True,ensure_ascii=False,separators=(',',':'))


def scalar(value):
    if value is None:return (-1,None)
    if type(value) is bool:return (2,value)
    if type(value) is int:return (0,value)
    if isinstance(value,str):return (1,value.encode('utf8'))
    if set(value)=={'date'}:return (3,date.fromisoformat(value['date']).toordinal())
    if set(value)=={'decimal'}:return (4,Fraction(value['decimal']))
    raise ValueError('unsupported independent scalar')


def compare(a,b):
    return (a>b)-(a<b)


def row_compare(a,b,order):
    for field in order:
        left=a['values'][field['field']];right=b['values'][field['field']]
        if left is None or right is None:
            result=0 if left is right else -1 if left is None else 1
            if field['nulls']=='last':result=-result
        else:
            result=compare(scalar(left),scalar(right))
            if field['direction']=='desc':result=-result
        if result:return result
    return compare(tuple(map(scalar,a['identity'])),tuple(map(scalar,b['identity'])))


def topk(records,request):
    remaining=request['k'];result=[]
    for record in sorted(records,key=cmp_to_key(lambda a,b:row_compare(a,b,request['order']))):
        if not remaining:break
        take=min(remaining,record['weight'])
        result.append(dict(record,weight=take));remaining-=take
    return {'selected_rows':request['k']-remaining,'entries':result}


def numeric(coefficient,scale):
    sign='-' if coefficient<0 else '';digits=str(abs(coefficient)).rjust(scale+1,'0')
    text=digits if not scale else (digits[:-scale]+'.'+digits[-scale:]).rstrip('0').rstrip('.')
    return {'decimal':'0' if not coefficient else sign+text}


def decimal(value):
    number=Fraction(str(value));denominator=number.denominator;twos=fives=0
    while denominator%2==0:denominator//=2;twos+=1
    while denominator%5==0:denominator//=5;fives+=1
    if denominator!=1:raise ValueError('nonterminating stored decimal')
    scale=max(twos,fives)
    return numeric(number.numerator*(10**scale//number.denominator),scale)


def average(total,count,scale):
    if not count:return None
    coefficient,remainder=divmod(abs(total)*10**scale,count)
    coefficient+=2*remainder>=count
    return numeric(-coefficient if total<0 else coefficient,scale)


def decode(value,kind):
    if value is None:return None
    if kind=='boolean':return bool(value)
    if kind=='date':return {'date':value}
    if kind=='decimal':return decimal(value)
    return value


def catalog():
    columns=[{'name':name,'type':kind,'nullable':name!='id'} for name,kind in
             [('id','int64'),('x','int64'),('t','string'),('flag','bool'),('d','date'),('n','decimal')]]
    return {'version':1,'tables':[{'name':'r','columns':columns}]}


def pool():
    return [[1,None,'b',False,{'date':'0001-01-01'},{'decimal':'-10'}],
            [2,2,'a',True,{'date':'9999-12-31'},{'decimal':'2'}],
            [3,-2,None,None,None,{'decimal':'10'}],
            [4,2,'a',False,{'date':'1970-01-01'},{'decimal':'2'}],
            [-1,0,'z',False,{'date':'2000-02-29'},{'decimal':'0'}],
            [5,1,'é\x01z',True,{'date':'2024-02-29'},
             {'decimal':'0.00000000000000000000000000000000000001'}]]


def updates():
    rows=pool();weights=[0]*len(rows);result=[]
    def put(index,next_weight):
        result.append({'values':rows[index],'before':weights[index],'after':next_weight});weights[index]=next_weight
    for index,weight in enumerate([2,1,3,2,1,1]):put(index,weight)
    for index,weight in [(1,3),(3,0),(1,0),(2,1),(0,2),(0,0),(2,0),(4,0),(5,0)]:put(index,weight)
    return result


def rankings(width):
    orders=[[]]
    orders += [[{'field':0,'direction':direction,'nulls':nulls}]
               for direction in ['asc','desc'] for nulls in ['first','last']]
    orders += [[{'field':field,'direction':'asc','nulls':'first'}] for field in range(1,width)]
    if width>1:orders.append([{'field':0,'direction':'desc','nulls':'last'},
                              {'field':width-1,'direction':'asc','nulls':'first'}])
    orders.append([{'field':0,'direction':'asc','nulls':'first'}]*2)
    return [{'order':order,'k':k} for order in orders for k in [0,1,2,7,MAXIMUM]]


def cases():
    result=[]
    def rows(name,sql,types,reference=None):
        result.append({'id':name,'family':'rows','sql':sql,'reference_sql':reference or sql,
                       'types':types,'updates':updates(),'sql_order_crosscheck':all(t!='decimal' for t in types)})
    rows('bag-projected','SELECT x,t FROM r',['int64','text'])
    rows('distinct-projected','SELECT DISTINCT x,t FROM r',['int64','text'])
    rows('typed-filtered','SELECT x,t,flag,d,n FROM r WHERE id>=0',['int64','text','boolean','date','decimal'])
    rows('exists','SELECT EXISTS(SELECT x FROM r WHERE x>0)',['boolean'])
    rows('self-join','SELECT a.id,a.x,b.t FROM r a JOIN r b ON a.id=b.id',['int64','int64','text'])
    def aggregate(name,sql,reference,keys,outputs):
        result.append({'id':name,'family':'aggregate','sql':sql,'reference_sql':reference,
                       'key_types':keys,'outputs':outputs,'updates':updates(),'average_scale':2})
    aggregate('omitted-keys','SELECT COUNT(*) FROM r GROUP BY id','SELECT id,COUNT(*) FROM r GROUP BY id',
              ['int64'],[{'kind':'int64','column':1}])
    aggregate('count-tie-unranked-sum','SELECT COUNT(*),SUM(x) FROM r GROUP BY id',
              'SELECT id,COUNT(*),SUM(x) FROM r GROUP BY id',['int64'],
              [{'kind':'int64','column':1},{'kind':'decimal','column':2}])
    result[-1]['updates']=[{'values':[1,10,None,None,None,None],'before':0,'after':2},
                          {'values':[2,5,None,None,None,None],'before':0,'after':2},
                          {'values':[1,10,None,None,None,None],'before':2,'after':0}]
    aggregate('global','SELECT COUNT(*),SUM(x),AVG(x) FROM r','SELECT COUNT(*),SUM(x),COUNT(x) FROM r',[],
              [{'kind':'int64','column':0},{'kind':'decimal','column':1},{'kind':'average','sum':1,'count':2}])
    aggregate('groups','SELECT id,COUNT(*),COUNT(x),SUM(x),AVG(x) FROM r GROUP BY id',
              'SELECT id,COUNT(*),COUNT(x),SUM(x) FROM r GROUP BY id',['int64'],
              [{'kind':'int64','column':0},{'kind':'int64','column':1},{'kind':'int64','column':2},
               {'kind':'decimal','column':3},{'kind':'average','sum':3,'count':2}])
    aggregate('nullable-key-average','SELECT AVG(x) FROM r GROUP BY t','SELECT t,SUM(x),COUNT(x) FROM r GROUP BY t',
              ['text'],[{'kind':'average','sum':1,'count':2}])
    aggregate('repeated-sums','SELECT t,SUM(x),SUM(x),COUNT(*) FROM r GROUP BY t',
              'SELECT t,SUM(x),COUNT(*) FROM r GROUP BY t',['text'],
              [{'kind':'text','column':0},{'kind':'decimal','column':1},{'kind':'decimal','column':1},{'kind':'int64','column':2}])
    aggregate('rounded-average-tie','SELECT AVG(x) FROM r GROUP BY id','SELECT id,SUM(x),COUNT(x) FROM r GROUP BY id',
              ['int64'],[{'kind':'average','sum':1,'count':2}])
    result[-1]['updates']=[{'values':[identity,x,None,None,None,None],'before':0,'after':weight}
                          for identity,x,weight in [(1,1,997),(1,2,3),(2,1,249),(2,2,1)]]
    wide=[1,7,None,None,None,None]
    result.append({'id':'symbolic-wide','family':'rows','sql':'SELECT x FROM r','types':['int64'],'symbolic':True,
                   'updates':[{'values':wide,'before':0,'after':MAXIMUM},
                              {'values':wide,'before':MAXIMUM,'after':0},
                              {'values':wide,'before':0,'after':(1<<53)+3}]})
    for item in result:
        item['catalog']=catalog();width=len(item['types']) if item['family']=='rows' else len(item['outputs'])
        item['ranks']=rankings(width)
    return result


def physical(value):
    if isinstance(value,dict):return value.get('decimal',value.get('date'))
    return int(value) if type(value) is bool else value


def query_records(case,database):
    records=[]
    if case['family']=='rows':
        grouped={}
        for result in database.execute(case['reference_sql']):
            values=[decode(v,t) for v,t in zip(result,case['types'])];identity=key(values)
            if identity not in grouped:grouped[identity]={'values':values,'identity':values,'weight':0}
            grouped[identity]['weight']+=1
        return list(grouped.values())
    for record in database.execute(case['reference_sql']):
        identity=[decode(value,kind) for value,kind in zip(record,case['key_types'])]
        values=[]
        for output in case['outputs']:
            if output['kind']=='average':values.append(average(record[output['sum']],record[output['count']],case['average_scale']))
            else:values.append(decode(record[output['column']],output['kind']))
        records.append({'identity':identity,'values':values,'weight':1})
    return records


def sql_rank(case,database,request):
    """Independent SQL ordering for representable row values and full-row ties."""
    fields=[f'c{i}' for i in range(len(case['types']))]
    order=[f"c{k['field']} {k['direction']} NULLS {k['nulls']}" for k in request['order']]
    order += [f'{name} ASC NULLS FIRST' for name in fields]
    statement='WITH q('+','.join(fields)+') AS ('+case['reference_sql']+') SELECT '+','.join(fields)+' FROM q ORDER BY '+','.join(order)+' LIMIT ?'
    grouped=[]
    for record in database.execute(statement,(min(request['k'],(1<<63)-1),)):
        values=[decode(value,kind) for value,kind in zip(record,case['types'])]
        if grouped and grouped[-1]['values']==values:grouped[-1]['weight']+=1
        else:grouped.append({'values':values,'identity':values,'weight':1})
    return grouped


def expected(case):
    database=sqlite3.connect(':memory:');database.execute('CREATE TABLE r(id INTEGER,x INTEGER,t TEXT,flag INTEGER,d TEXT,n TEXT)')
    state={};trace=[];sql_crosschecks=0
    for index in range(len(case['updates'])+1):
        if index:
            update=case['updates'][index-1];identity=key(update['values']);old=state.get(identity,0)
            if old!=update['before']:raise AssertionError('invalid independent source chain')
            state[identity]=update['after']
            if not case.get('symbolic'):
                values=list(map(physical,update['values']))
                database.execute('DELETE FROM r WHERE id IS ? AND x IS ? AND t IS ? AND flag IS ? AND d IS ? AND n IS ?',values)
                database.executemany('INSERT INTO r VALUES(?,?,?,?,?,?)',[values]*update['after'])
        if case.get('symbolic'):
            weight=sum(state.values());records=[] if not weight else [{'identity':[7],'values':[7],'weight':weight}]
        else:records=query_records(case,database)
        ranks=[topk(records,request) for request in case['ranks']]
        if case.get('sql_order_crosscheck'):
            for request,rank in zip(case['ranks'],ranks):
                if sql_rank(case,database,request)!=rank['entries']:raise AssertionError((case['id'],index,request,'SQL rank mismatch'))
                sql_crosschecks+=1
        trace.append({'sequence':index,'ranked':ranks})
    database.close();return trace,sql_crosschecks


def native(case,indexed):
    return {name:value for name,value in dict(case,indexed=indexed).items()
            if name not in ['reference_sql','types','key_types','outputs','symbolic','sql_order_crosscheck']}


def check(case,observed,reference):
    if observed['id']!=case['id'] or len(observed['trace'])!=len(reference):raise AssertionError(('trace-shape',case['id']))
    comparisons=0
    for actual,wanted in zip(observed['trace'],reference):
        if actual['sequence']!=wanted['sequence']:raise AssertionError(('sequence',case['id']))
        if len(actual['ranked'])!=len(wanted['ranked']):raise AssertionError(('rank-count',case['id']))
        for request,rank,goal in zip(case['ranks'],actual['ranked'],wanted['ranked']):
            if key({'entries':rank['entries'],'selected_rows':rank['selected_rows']})!=key(goal):
                raise AssertionError((case['id'],actual['sequence'],request,rank,goal))
            if any(type(rank[name]) is not int or not 0<=rank[name]<=MAXIMUM
                   for name in ['work','candidates','comparisons','fields','scalar_bytes']):
                raise AssertionError('invalid metric integer')
            if request['k']==0 and rank['candidates']!=0:raise AssertionError('k=0 scanned candidates')
            if len({key(r['identity']) for r in rank['entries']})!=len(rank['entries']):raise AssertionError('duplicate selected identity')
            if sum(r['weight'] for r in rank['entries'])!=rank['selected_rows']:raise AssertionError('selected weight mismatch')
            comparisons+=1
    return comparisons


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--driver',required=True)
    parser.add_argument('--artifacts',type=Path);args=parser.parse_args()
    if args.artifacts:args.artifacts.mkdir(parents=True,exist_ok=False)
    suite=cases();references={};sql_checks=0;requests=[]
    for case in suite:
        references[case['id']],count=expected(case);sql_checks+=count
        for indexed in [False,True]:requests.append((case,native(case,indexed)))
    encoded=''.join(key(request)+'\n' for _,request in requests).encode('utf8')
    if args.artifacts:
        (args.artifacts/'native-request.jsonl').write_bytes(encoded)
        (args.artifacts/'expected.json').write_text(key(references)+'\n',encoding='utf8')
        (args.artifacts/'case-catalog.json').write_text(key(suite)+'\n',encoding='utf8')
    process=subprocess.run([args.driver],input=encoded,capture_output=True,timeout=300)
    if args.artifacts:
        (args.artifacts/'native.stdout').write_bytes(process.stdout)
        (args.artifacts/'native.stderr').write_bytes(process.stderr)
    if process.returncode or process.stderr:
        raise AssertionError((process.returncode,process.stderr.decode('utf8',errors='replace'),process.stdout[-2000:].decode('utf8',errors='replace')))
    observed=[json.loads(line) for line in process.stdout.splitlines()]
    if len(observed)!=len(requests):raise AssertionError(('native-case-count',len(observed),len(requests)))
    compared=sum(check(case,result,references[case['id']]) for (case,_),result in zip(requests,observed))
    summary={'status':'PASS_independent_SQL_and_exact_topk_oracle','queries':len(suite),
          'native_cases':len(requests),'ranked_snapshots_compared':compared,'SQLite_order_crosschecks':sql_checks,
          'sqlite_version':sqlite3.sqlite_version,'wide_weights_expanded':False,'AVG':'SQL_SUM_COUNT_then_exact_Fraction_display_rounding',
          'ordering':'requested_keys_then_identity_ASC_NULLS_FIRST','corpus':'fixed'}
    if args.artifacts:(args.artifacts/'summary.json').write_text(key(summary)+'\n',encoding='utf8')
    print(json.dumps(summary,sort_keys=True))


if __name__=='__main__':main()
