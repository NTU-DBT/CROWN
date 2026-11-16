#!/usr/bin/env python3
"""Check real calibration replay against independent SQL/trace fixtures."""
from pathlib import Path
from fractions import Fraction
import hashlib,json,math,subprocess,sys,tempfile
import jsonschema

def require(value,message):
    if not value:raise RuntimeError(message)
def key(value):return json.dumps(value,sort_keys=True,ensure_ascii=False,separators=(',',':'))
def run(command,raw_path=None):
    result=subprocess.run([str(x) for x in command],capture_output=True,text=True,timeout=180)
    require(result.returncode==0,f'{command}: {result.stderr[-1500:]}')
    if raw_path is not None:raw_path.write_text(result.stdout)
    return json.loads(result.stdout)
def fraction(value):return Fraction(value['numerator'],value['denominator'])
def main():
    require(len(sys.argv) in [4,5],'usage: CALIBRATOR CROWN SOURCE [ARTIFACT_DIRECTORY]')
    calibrator,crown,source=sys.argv[1:4];root=Path(source).resolve();fixture=root/'tests/workflow'
    artifacts=Path(sys.argv[4]).resolve() if len(sys.argv)==5 else None
    if artifacts is not None:artifacts.mkdir(parents=True,exist_ok=False)
    manifest=json.loads((fixture/'manifest.json').read_text());order=json.loads((root/'tests/cost_model/calibration-fit-v1.json').read_text())['component_order']
    schema_path=root/'schemas/cost-calibration-v1.schema.json';schema=json.loads(schema_path.read_text());schema['$id']=schema_path.as_uri()
    cq=root/'schemas/cq-v2.schema.json'
    resolver=jsonschema.RefResolver(base_uri=schema_path.as_uri(),referrer=schema,store={cq.as_uri():json.loads(cq.read_text())})
    validator=jsonschema.Draft202012Validator(schema,resolver=resolver)
    with tempfile.TemporaryDirectory(prefix='crown-calibration-') as temporary:
        for name,case in manifest['cases'].items():
            catalog=fixture/case['catalog'];query=fixture/case['query'];expected=json.loads((fixture/case['expected_oracle']).read_text())
            canonical=run([crown,'canonicalize-catalog',catalog]);digest=hashlib.sha256(key(canonical).encode()).hexdigest()
            events=[json.loads(line) for line in (fixture/case['events_template_jsonl']).read_text().splitlines()]
            for event in events:event['catalog_sha256']=digest
            updates=Path(temporary)/(name+'.jsonl');updates.write_text(''.join(key(event)+'\n' for event in events))
            if artifacts is not None:(artifacts/(name+'.input.jsonl')).write_bytes(updates.read_bytes())
            report=run([calibrator,query,catalog,updates,len(events),2,2],artifacts/(name+'.report.json') if artifacts is not None else None)
            validator.validate(report)
            require(report['kind']=='c03_measured_calibration' and report['schema_version']==1,'calibration format differs')
            require(report['source_sha256']==hashlib.sha256(query.read_bytes()).hexdigest() and report['input_sha256']==hashlib.sha256(updates.read_bytes()).hexdigest(),'calibration input binding differs')
            require(0<report['candidate_count']<=2 and report['repetitions']==2,'calibration candidate/repetition bound differs')
            require(len(report['candidates'])==report['candidate_count'],'registered candidate/report count differs')
            require('no WAL or sink' in report['scope'] and 'no held-out' in report['qualification'],'calibration scope became a performance claim')
            for candidate in report['candidates']:
                require(candidate['backend']=='reference_ordered_v1' and candidate['modes']['delta_owner'] and candidate['modes']['resolved_mode']=='delta','calibration changed actual backend/mode')
                require(candidate['records_per_repetition']==len(events),'replay lost physical input')
                require(candidate['delta_rows_per_repetition']==sum(len(x['signed_delta']) for x in expected['events']),'raw delta count differs from oracle')
                require(candidate['snapshot_rows_per_repetition']==sum(len(x['current_rows']) for x in expected['events']),'full snapshot row count differs from oracle')
                actual=candidate['final_rows'];oracle=expected['events'][-1]['current_rows']
                require(len(actual)==len(oracle) and {key(x) for x in actual}=={key(x) for x in oracle},'calibration replay state differs from independent oracle')
                raw=candidate['observations'];require(len(raw)==6*len(events),'raw phase observation count differs')
                rates=[]
                for i,component in enumerate(order):
                    coefficient=candidate['coefficients'][component];units=sum(row['units'][i] for row in raw);samples=sum(row['units'][i]>0 for row in raw)
                    require((coefficient is None)==(units==0),'unobserved feature got a fitted zero or observed feature disappeared')
                    if coefficient is not None:
                        require(coefficient['origin']=='fitted_linear_assumption' and coefficient['observed_units']==units and coefficient['observed_samples']==samples,'inferred coefficient presented as an observed unit timing')
                        rates.append(fraction(coefficient['rate']))
                    else:rates.append(Fraction(0))
                errors=[];phase_costs={}
                for row in raw:
                    require(isinstance(row['elapsed_ns'],int) and row['elapsed_ns']>=0 and len(row['units'])==len(order),'bad native timing or feature shape')
                    epoch=expected['events'][row['sequence']-1]
                    if row['phase']=='input_decode_native_prepare_commit':require(row['units'][0]==1,'maintenance phase does not represent one physical input')
                    elif row['phase']=='read_committed_output_spool':
                        require(row['units'][order.index('delta_start')]==row['units'][order.index('delta_end')]==1,'output timing scope differs')
                        require(row['units'][order.index('delta_row')]==len(epoch['signed_delta']),'per-epoch raw output count differs from independent oracle')
                    else:
                        require(row['phase']=='materialize_committed_snapshot' and row['units'][order.index('snapshot_start')]==row['units'][order.index('snapshot_end')]==1,'snapshot timing scope differs')
                        require(row['units'][order.index('snapshot_row')]==len(epoch['current_rows']),'per-epoch full result count differs from independent oracle')
                    predicted=sum((rate*unit for rate,unit in zip(rates,row['units'])),Fraction(0));errors.append(float(predicted-row['elapsed_ns']))
                    if row['repetition']==0:phase_costs[row['phase']]=phase_costs.get(row['phase'],Fraction(0))+predicted
                fit=candidate['fit'];require(fit['numerical_rank']<=fit['observed_features'] and fit['underdetermined']==(fit['numerical_rank']<fit['observed_features']),'rank/confidence fields disagree')
                require(math.isclose(fit['rmse_ns_on_calibration_data'],math.sqrt(sum(x*x for x in errors)/len(errors)),rel_tol=1e-10,abs_tol=1e-5),'recorded fit residual cannot be reproduced')
                require(math.isclose(fit['max_error_ns_on_calibration_data'],max(map(abs,errors)),rel_tol=1e-10,abs_tol=1e-5),'recorded maximum residual cannot be reproduced')
                price=candidate['replay_horizon_estimate'];require(price['issues']==0,'same replay profile has unavailable estimate')
                require(fraction(price['maintenance_ns'])==phase_costs['input_decode_native_prepare_commit'] and fraction(price['delta_ns'])==phase_costs['read_committed_output_spool'] and fraction(price['snapshot_ns'])==phase_costs['materialize_committed_snapshot'],'decomposed exact estimate differs from recorded features/coefficient arithmetic')
                require(fraction(price['total_ns'])==sum(phase_costs.values()) and price['future_memory_unknown'],'cost sum or future memory scope differs')
            print('C03 measured calibration',name,'oracle/phase counters/raw timings/rank/coefficient provenance/exact replay arithmetic passed')
    return 0
if __name__=='__main__':
    try:raise SystemExit(main())
    except Exception as error:print(str(error));raise SystemExit(1)
