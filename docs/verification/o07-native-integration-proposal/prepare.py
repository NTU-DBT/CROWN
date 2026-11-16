from pathlib import Path
import hashlib,json,shutil
H=Path(__file__).resolve().parent;R=H.parents[2];C=H.parent/'o07-composed-explain-proposal';Q=H.parent/'o07-query-explain-proposal'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
base=json.loads((C/'baseline-sha256.json').read_text())
for rel,digest in json.loads((C/'readiness.json').read_text())['files'].items():
 p=C/rel
 if sha(p)!=digest:raise SystemExit('frozen composed package drift: '+rel)
 base[str(p.relative_to(R))]=digest
for p in [C/'readiness.json',R/'CMakeLists.txt',R/'apps/crown/main.cpp',R/'build/release/libcrown_reference.a']:
 base[str(p.relative_to(R))]=sha(p)
for p in (Q/'schemas').glob('*.json'):
 base[str(p.relative_to(R))]=sha(p);shutil.copyfile(p,H/'schemas'/p.name)
(H/'baseline-sha256.json').write_text(json.dumps(dict(sorted(base.items())),indent=2)+'\n')
main=(R/'apps/crown/main.cpp').read_text().replace('#include "evaluator.hpp"','#include "evaluator.hpp"\n#include "explain.hpp"')
anchor='    if (argc >= 2 && std::string(argv[1]) == "validate-input") {'
insert='''    if (argc == 2 && std::string(argv[1]) == "--help") {
      std::cout << "usage: crown COMMAND ...\\n"
          "  --version; --help\\n"
          "  parse-sql; bind-sql; normalize-sql; admit-sql; admit-normalized\\n"
          "  validate-normalized; canonicalize-normalized; upgrade-cq; upgrade-normalized\\n"
          "  fingerprint-cq; fingerprint-normalized; lower-plan; lower-normalized\\n"
          "  support-trace; validate-input; validate-physical; canonicalize-physical\\n"
          "  validate-catalog; canonicalize-catalog; oracle; validate-cq; canonicalize\\n"
          "  classify; tree-oracle; validate-plan; verify-height\\n"
          "  explain {physical|runtime|session|query|progress|replay} INPUT [OPTIONS]\\n"
          "  crown explain --help lists EXPLAIN options.\\n";
      return 0;
    }
    if (argc >= 2 && std::string(argv[1]) == "explain")
      return crown::cli::explain_main(argc-1,argv+1);
'''
assert anchor in main;main=main.replace(anchor,insert+anchor)
(H/'overlay/apps/crown/main.cpp').write_text(main)
(H/'overlay/apps/crown/explain.hpp').write_text('''#pragma once
namespace crown::cli {
// Private application dispatcher. argv[0] is "explain", argv[1] its subcommand.
// Owns EXPLAIN-only diagnostics; the outer CLI keeps all existing handlers.
int explain_main(int argc,char** argv);
} // namespace crown::cli
''')
s=(C/'overlay/apps/crown-explain/main.cpp').read_text();s='#include "explain.hpp"\n'+s
old=''' auto file=a.take("--certificate");const auto budget=a.number("--proof-work",10000000);
 if(!file)return {};'''
new=''' auto file=a.take("--certificate");const auto proof_work=a.take("--proof-work");
 if(!file){if(proof_work)throw Error("usage","--proof-work requires --certificate");return {};}
 const auto budget=proof_work?integer(*proof_work):10000000;'''
assert old in s;s=s.replace(old,new).replace('int main(int argc,char** argv){','int crown::cli::explain_main(int argc,char** argv){')
needle=' try{Arguments args(argc,argv);'
help=''' try{
  if(argc==2 && std::string_view(argv[1])=="--help"){
   std::cout << "usage: crown explain {physical|runtime|session} PLAN [OPTIONS]\\n"
       "       crown explain {query|progress} DOCUMENT [--work N] [--height-policy strict|best-found]\\n"
       "       crown explain replay DOCUMENT --certificate FILE [--work N]\\n"
       "formats: --format text|json|dot|tree-json --max-bytes N\\n"
       "physical proof: --certificate FILE [--proof-work N]\\n"
       "runtime/session: --mode maintenance|delta --observe off|counters|timed|trace\\n"
       "  --live on_output|incremental|eager --completion automatic|ordered_replay|anchored|root_first\\n"
       "  --view core|sql --work-limit N --spool-rows N\\n"
       "  --run-label TEXT --adapter-label TEXT --codec-label TEXT --sink-label TEXT\\n"
       "session: --input FILE --input-format jsonl|binary --events N --steps N\\n"
       "  --consume discard|transfer|retain --lifecycle preserve|stop|drop\\n"
       "Work quanta are explicit producer operations; capture/export never advance a producer.\\n"
       "Labels are caller declarations, unmeasured and without proof/durability authority.\\n";
   if(!std::cout)throw crown::Error("io_error","output failed");
   return 0;
  }
  Arguments args(argc,argv);'''
assert needle in s;s=s.replace(needle,help);(H/'overlay/apps/crown/explain.cpp').write_text(s)
s=(R/'CMakeLists.txt').read_text()
s=s.replace('add_library(crown_sql ','''# Query/search explanation owns only typed planner/core handles.
add_library(crown_query_explain src/observability/query_explain.cpp src/io/query_explain.cpp)
target_include_directories(crown_query_explain PUBLIC include)
target_link_libraries(crown_query_explain PUBLIC crown_core PRIVATE crown_options)

add_library(crown_sql ''',1)
s=s.replace('src/runtime/replay.cpp src/runtime/session.cpp src/runtime/window.cpp)','src/runtime/replay.cpp src/runtime/session.cpp src/runtime/window.cpp src/runtime/observation.cpp)',1)
anchor='# Deliberately separate from the future maintained runtime and tree constructor.'
s=s.replace(anchor,'''# Final report layer: runtime never depends on observability or report IO.
set(CROWN_EXPLAIN_SOURCES src/observability/explain.cpp src/io/explain.cpp
  src/io/run_context.cpp src/io/cursor_observation.cpp)
add_library(crown_explain ${CROWN_EXPLAIN_SOURCES})
target_include_directories(crown_explain PUBLIC include)
target_link_libraries(crown_explain PUBLIC crown_runtime crown_query_explain PRIVATE crown_options)

'''+anchor)
s=s.replace('add_executable(crown apps/crown/main.cpp)','add_executable(crown apps/crown/main.cpp apps/crown/explain.cpp)').replace('target_link_libraries(crown PRIVATE crown_runtime crown_reference crown_options)','target_link_libraries(crown PRIVATE crown_explain crown_reference crown_options)')
anchor='  target_link_libraries(crown_runtime_testing PUBLIC crown_plan PRIVATE crown_options Threads::Threads)'
assert anchor in s;s=s.replace(anchor,anchor+'''
  # Future observation tests link this variant only; never also crown_explain
  # or crown_runtime. The testing definition propagates through runtime_testing.
  add_library(crown_explain_testing STATIC ${CROWN_EXPLAIN_SOURCES})
  target_include_directories(crown_explain_testing PUBLIC include)
  target_link_libraries(crown_explain_testing PUBLIC crown_runtime_testing crown_query_explain PRIVATE crown_options)
  # O07 test registration awaits the independently accepted source list.
''')
(H/'overlay/CMakeLists.txt').write_text(s)
print('Prepared application/build overlay only; no CMake invocation.')
p=H/'overlay/src/io/explain.cpp';p.parent.mkdir(parents=True,exist_ok=True)
s=(C/'overlay/src/io/explain.cpp').read_text().replace(',"native_integration_and_acceptance"','').replace('benchmark/release validation and native integration acceptance.','benchmark/release validation.')
p.write_text(s)
for src in (C/'schemas').glob('*.json'):
 s=json.loads(src.read_text())
 if src.name=='explain-report-v2.schema.json':s['$defs']['physical_report']['properties']['open_gates']['items']['enum'].remove('native_integration_and_acceptance')
 (H/'schemas'/src.name).write_text(json.dumps(s,indent=2)+'\n')
