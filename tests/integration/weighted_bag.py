#!/usr/bin/env python3
"""W03 projected counts against unbounded full native joins after every update.

Duplicate raw rows in the oracle input fold to the native logical weights sent
to the runtime. This tests bag enumeration, not a physical bag-source router or
SQL frontend. Runtime snapshots/caches are never used as the output oracle.
"""
import importlib.util
import json
import pathlib
import random
import subprocess
import sys

ROOT=pathlib.Path(__file__).resolve().parents[2]


def load(name):
    spec=importlib.util.spec_from_file_location(name,ROOT/'tests/reference'/f'{name}.py')
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


bag=load('weighted_bag_oracle')
subtree=load('weighted_oracle')


def normalize(rows):
    result={json.dumps(row['row'],separators=(',',':')):row['count'] for row in rows}
    assert len(result)==len(rows), 'duplicate projected cursor output'
    return result


def payload(description,inputs):
    tables=[]
    for table in inputs:
        rows=[]
        for encoded,weight in table.items():
            row=json.loads(encoded)
            # Explicit duplicates in the independent oracle: representation
            # differs from the runtime's one exact weight per logical tuple.
            if weight>1:
                rows.extend([dict(row=row,weight='1'),dict(row=row,weight=str(weight-1))])
            else:
                rows.append(dict(row=row,weight=str(weight)))
        tables.append(rows)
    return dict(description,inputs=tables)


def check_case(driver,fixture,indexed,updates,limit=(1<<64)-1):
    request=dict(fixture=fixture,indexed=indexed,updates=updates,limit=str(limit))
    process=subprocess.run([driver],input=json.dumps(request)+'\n',capture_output=True,text=True,check=True)
    outputs=[json.loads(line) for line in process.stdout.splitlines()]
    description=outputs.pop(0)
    inputs=[{} for _ in description['nodes']]
    assert normalize(outputs.pop(0)['rows'])==normalize(bag.evaluate(payload(description,inputs))['rows'])
    assert len(outputs)==len(updates)
    sequence=0
    for number,(update,actual) in enumerate(zip(updates,outputs)):
        node=update['node'];key=json.dumps(update['row'],separators=(',',':'))
        old=inputs[node].get(key,0)
        before,after=int(update['before']),int(update['after'])
        error='weight_conflict' if old!=before else ''
        if not error:
            if after:inputs[node][key]=after
            else:inputs[node].pop(key,None)
        proposed=payload(description,inputs)
        messages=subtree.evaluate(proposed)
        values=[int(messages['root_count']),after]
        values.extend(int(row[field]) for n in messages['nodes'] for row in n['rows'] for field in ('local','subtree'))
        values.extend(int(message['count']) for message in messages['messages'])
        if not error and max(values,default=0)>limit:
            error='annotation_overflow'
            if old:inputs[node][key]=old
            else:inputs[node].pop(key,None)
        expected=bag.evaluate(payload(description,inputs))
        assert actual['error']==error,(fixture,indexed,number,update,actual['error'],error)
        sequence+=not error
        assert actual['sequence']==sequence
        assert normalize(actual['rows'])==normalize(expected['rows']),(fixture,indexed,number,update)
        assert actual['total_count']==expected['total_count']
        assert actual['records_emitted']==len(expected['rows']), 'output-size representation confused'
    return len(updates)+1


def random_updates(fixture,count):
    rng=random.Random(730300+count);weights={};result=[]
    for _ in range(count):
        if fixture=='generalized':
            node=rng.choice([1,3,4]);row=[rng.randrange(3)]
            if node!=1:row.extend([rng.randrange(3),rng.randrange(2)])
        elif fixture=='disconnected':
            node=rng.choice([1,2]);row=[rng.randrange(4)]
        elif fixture in ('counted','tail','repeated'):
            node=rng.randrange(3 if fixture!='counted' else 2)
            if node==0:row=[rng.randrange(3),rng.randrange(3),rng.randrange(2)]
            elif node==1:row=[rng.randrange(3),rng.randrange(3)]
            else:row=[rng.randrange(3)]
        else:
            node=rng.randrange(3);row=[rng.randrange(3)]
            if node!=2:row.append(rng.randrange(3))
        key=(node,tuple(row));before=weights.get(key,0);after=rng.randrange(8)
        result.append(dict(node=node,row=row,before=str(before),after=str(after)));weights[key]=after
    return result


def update(node,row,before,after):
    return dict(node=node,row=row,before=str(before),after=str(after))


def main():
    driver=sys.argv[1];states=0
    for indexed in (False,True):
        for fixture in ('counted','tail','repeated','generalized','disconnected','path'):
            states+=check_case(driver,fixture,indexed,random_updates(fixture,220))
        states+=check_case(driver,'counted',indexed,[
            update(0,[1,10,100],0,2),update(0,[1,10,101],0,3),
            update(1,[10,20],0,5),update(1,[10,21],0,7)])
        states+=check_case(driver,'unary',indexed,[
            update(0,[1],0,9007199254740993),update(0,[1],9007199254740993,(1<<64)-1),
            update(0,[2],0,1),update(0,[1],(1<<64)-1,0),update(0,[2],0,7),update(0,[2],99,5)])
        states+=check_case(driver,'counted',indexed,[
            update(0,[1,7,9],0,2),update(1,[7,10],0,50),update(1,[7,10],50,51),
            update(1,[7,10],50,1),update(0,[2,7,9],0,99),update(0,[2,7,9],0,3)],100)
        states+=check_case(driver,'boolean',indexed,[update(0,[1],0,7),update(0,[2],0,11),update(0,[1],7,0)])
        states+=check_case(driver,'nullary',indexed,[update(0,[],0,(1<<64)-1),update(0,[],(1<<64)-1,0)])
        for fixture in ('true','false'):states+=check_case(driver,fixture,indexed,[])
        deep=[update(0,[1,7],0,2),update(0,[2,7],0,3)]
        deep.extend(update(node,[7],0,1) for node in range(1,96))
        deep.extend([update(95,[7],1,13),update(95,[7],13,0),update(95,[7],0,17)])
        states+=check_case(driver,'deep-hidden',indexed,deep)
    print(f'weighted projected bag oracle: {states} exact states, both backends; compressed output records')


if __name__=='__main__':
    main()
