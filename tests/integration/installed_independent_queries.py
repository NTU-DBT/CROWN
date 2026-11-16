#!/usr/bin/env python3
"""Compile a relocated public consumer and check unseen independent SQL streams."""
import hashlib
import json
from pathlib import Path
import shutil
import sqlite3
import subprocess
import sys
import tempfile

sys.dont_write_bytecode = True


def require(value,message):
    if not value:
        raise RuntimeError(message)


def expected(sql,events):
    """Independent physical pair-table execution, with no native plan helper."""
    database = sqlite3.connect(':memory:')
    database.execute('CREATE TABLE r(a INTEGER,b INTEGER)')
    database.execute('CREATE TABLE s(b INTEGER,c INTEGER)')
    for operation,table,values in events:
        columns = ('a','b') if table == 'r' else ('b','c')
        statement = 'INSERT INTO '+table+' VALUES(?,?)' if operation == '+' else \
                    'DELETE FROM '+table+' WHERE '+columns[0]+'=? AND '+columns[1]+'=?'
        database.execute(statement,values)
    rows = sorted(list(row) for row in database.execute(sql))
    database.close()
    if sql.startswith('SELECT EXISTS('):
        rows = [[bool(row[0])] for row in rows]
    return rows


def main():
    require(len(sys.argv) in (5,6), 'usage: installed_independent_queries.py SOURCE BUILD COMPILER SANITIZE [NEW_ARTIFACT_DIRECTORY]')
    root,build = [Path(value).resolve() for value in sys.argv[1:3]]
    compiler,sanitize = sys.argv[3:5]
    temporary = None
    if len(sys.argv) == 6:
        base = Path(sys.argv[5]).resolve(); base.mkdir(parents=True,exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-installed-queries-'); base = Path(temporary.name)
    records = []
    def run(arguments):
        command = list(map(str,arguments)); number = len(records)
        child = subprocess.run(command,capture_output=True,text=True,timeout=300)
        out,err = base/(str(number)+'.stdout'),base/(str(number)+'.stderr')
        out.write_text(child.stdout); err.write_text(child.stderr)
        records.append({'arguments':command,'exit_code':child.returncode,'stdout':out.name,'stderr':err.name,
                        'stdout_sha256':hashlib.sha256(out.read_bytes()).hexdigest(),
                        'stderr_sha256':hashlib.sha256(err.read_bytes()).hexdigest()})
        (base/'commands.json').write_text(json.dumps(records,indent=2)+'\n')
        require(child.returncode == 0, 'public consumer command failed: '+child.stderr[-2500:])
        return child.stdout
    stage,prefix = base/'stage',base/'relocated SDK'
    run(['cmake','--install',build,'--prefix',stage]); stage.rename(prefix)
    require(not stage.exists(), 'unmoved install prefix remains')
    source,consumer = base/'outside-source',base/'outside-build'
    shutil.copytree(prefix/'share/crown/examples/independent-queries',source)
    configs = list(prefix.rglob('CrownConfig.cmake')); require(len(configs) == 1, 'ambiguous installed package')
    arguments = ['cmake','-S',source,'-B',consumer,'-DCMAKE_BUILD_TYPE=Release',
                 '-DCMAKE_CXX_COMPILER='+compiler,'-DCrown_DIR='+str(configs[0].parent),
                 '-DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF']
    if sanitize.upper() in ('ON','TRUE','YES','1'):
        arguments.append('-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer')
    run(arguments); run(['cmake','--build',consumer,'--parallel','2'])
    entries = json.loads((consumer/'compile_commands.json').read_text())
    require(len(entries) == 1 and '-std=c++23' in entries[0]['command'], 'consumer lost public language requirement')
    for path in (root/'include',root/'third_party',build,stage):
        require(str(path) not in entries[0]['command'], 'consumer depends on producer headers or old prefix')
    link = (consumer/'CMakeFiles/crown_independent_queries.dir/link.txt').read_text()
    require('libcrown_queries.a' in link and 'libcrown_reference' not in link and 'testing' not in link,
            'consumer linked wrong public/private closure')
    catalog = {'schema_version':1,'catalog':{'version':1,'tables':[
        {'name':table,'source_schema_version':1,'constraints':[],'key_hints':[],
         'statistics':{'distinct_counts':[]},'columns':[{'name':column,'type':'int64','nullable':False} for column in columns]}
        for table,columns in [('r',('a','b')),('s',('b','c'))]]}}
    path = base/'catalog.json'; path.write_text(json.dumps(catalog)+'\n')
    canonical = json.dumps(json.loads(run([prefix/'bin/crown','canonicalize-catalog',path])),
                           sort_keys=True,ensure_ascii=False,separators=(',',':')).encode()
    catalog_hash = hashlib.sha256(canonical).hexdigest()
    first = [('+','r',[1,10]),('+','s',[10,90]),('+','s',[10,91]),('+','r',[2,11]),
             ('+','s',[11,92]),('-','s',[10,90])]
    second = [('+','r',[7,70]),('+','s',[70,700]),('+','r',[8,80]),('+','s',[80,800]),('-','s',[70,700])]
    body = ' FROM r JOIN s ON r.b=s.b'
    pairs = [('SELECT DISTINCT r.a'+body,'SELECT DISTINCT s.c,r.b,r.a,17 AS fixed'+body),
             ('SELECT EXISTS(SELECT 1'+body+')','SELECT DISTINCT r.b'+body+' WHERE r.a>0')]
    for number,queries in enumerate(pairs):
        files = []
        for label,sql,events in zip(('a','b'),queries,(first,second),strict=True):
            sql_path,input_path = base/(str(number)+label+'.sql'),base/(str(number)+label+'.jsonl')
            sql_path.write_text(sql+'\n')
            input_path.write_text(''.join(json.dumps({'schema_version':1,'catalog_sha256':catalog_hash,
                'catalog_version':1,'source_schema_version':1,'sequence':index,'table':table,
                'operation':'insert' if operation == '+' else 'delete','values':values})+'\n'
                for index,(operation,table,values) in enumerate(events,1)))
            files.extend([sql_path,input_path])
        report = json.loads(run([consumer/'crown_independent_queries',path,*files]))
        require(report['execution'] == 'independent_serial_v1' and report['remaining_queries'] == 0,
                'public query ownership/execution mode differs')
        require(report['queries'][0]['account_owner'] != report['queries'][1]['account_owner'], 'queries share native account')
        for actual,sql,events in zip(report['queries'],queries,(first,second),strict=True):
            wanted = expected(sql,events)
            require(actual['sequence'] == len(events) and
                    json.dumps(sorted(actual['rows']),sort_keys=True) == json.dumps(wanted,sort_keys=True),
                    'unseen independent SQL results/progress differ from SQLite')
    print('Installed independent queries: relocated public consumer, four unseen SQL streams and separate native budgets passed')
    if temporary: temporary.cleanup()


if __name__ == '__main__':
    main()
