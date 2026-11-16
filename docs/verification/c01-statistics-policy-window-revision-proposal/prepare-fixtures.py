#!/usr/bin/env python3
"""Prepare opt-in fixture variants; never execute a compiler or project binary."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
PACKAGE = Path(__file__).resolve().parent

def replace_once(text, old, new):
    if text.count(old) != 1:
        raise RuntimeError('fixture seam changed: ' + old[:90])
    return text.replace(old, new)

def conditional(body):
    return '#ifdef CROWN_STATISTICS_ACCEPTANCE\n' + body + '#endif\n'

def prepare(name):
    text = (ROOT / 'tests/unit' / name).read_text()
    text = replace_once(text, '#include "evaluator.hpp"\n', '#include "evaluator.hpp"\n' + conditional('#include "statistics_acceptance.hpp"\n'))
    if name == 'delta_runtime_test.cpp':
        text = replace_once(text, '  return DeltaRuntime(std::move(plan),options);',
            '#ifdef CROWN_STATISTICS_ACCEPTANCE\n  DeltaRuntime runtime(std::move(plan),options);\n  statistics_acceptance::enable(runtime);\n  return runtime;\n#else\n  return DeltaRuntime(std::move(plan),options);\n#endif')
        text = replace_once(text, '  PrefixOracle prefixes(runtime.plan(), database);\n',
            '  PrefixOracle prefixes(runtime.plan(), database);\n' + conditional('  const auto c01_before = runtime.workload_statistics();\n'))
        text = replace_once(text, '  ++checked_updates;\n', conditional(
            '  statistics_acceptance::event(c01_before, runtime.workload_statistics(), update, physical_changed, label,\n'
            '      std::span<const DerivationChange>{actual.derivations});\n'
            '  statistics_acceptance::sources(runtime, database, label);\n') + '  ++checked_updates;\n')
        text = replace_once(text, '    exhaustive_binary_domain_toggles();\n',
            '    exhaustive_binary_domain_toggles();\n' + conditional('    statistics_acceptance::print();\n'))
    elif name == 'delta_replay_test.cpp':
        text = replace_once(text, '    database_.tables.resize(table_count);\n',
            '    database_.tables.resize(table_count);\n' + conditional('    statistics_acceptance::enable(runtime_);\n'))
        text = replace_once(text, '    const auto sequence = ++sequence_;\n    auto epoch = runtime_.apply({sequence, table, operation, std::move(row)});',
            conditional('    const auto c01_before = runtime_.workload_statistics();\n'
                        '    const PhysicalSetUpdate c01_update{sequence_ + 1, table, operation, row};\n') +
            '    const auto sequence = ++sequence_;\n    auto epoch = runtime_.apply({sequence, table, operation, std::move(row)});')
        text = replace_once(text, '    database_ = std::move(after_database);\n', conditional(
            '    statistics_acceptance::event(c01_before, runtime_.workload_statistics(), c01_update, changed, label,\n'
            '        std::span<const DerivationChange>{epoch.input().input.derivations});\n') + '    database_ = std::move(after_database);\n')
        text = replace_once(text, '    runtime_.check_invariants();\n  }\n\n  DeltaRuntime runtime_;',
            '    runtime_.check_invariants();\n' + conditional('    statistics_acceptance::sources(runtime_, database_, label);\n') + '  }\n\n  DeltaRuntime runtime_;')
        text = replace_once(text, '  } catch (const std::exception& failure) {',
            conditional('    statistics_acceptance::print();\n') + '  } catch (const std::exception& failure) {')
    else:
        text = replace_once(text, '    session = QuerySession::create_windowed(plan, initial, options);\n',
            '    session = QuerySession::create_windowed(plan, initial, options);\n' + conditional('    statistics_acceptance::enable(*session);\n'))
        text = replace_once(text, '    const auto& update = planned.update;\n', '    const auto& update = planned.update;\n' + conditional(
            '    const auto c01_before = *session->workload_statistics();\n'
            '    const bool c01_changed = update && (update->operation == SetOperation::insert\n'
            '        ? !oracle.database.tables.at(update->table.value).contains(update->values)\n'
            '        : oracle.database.tables.at(update->table.value).contains(update->values));\n'))
        text = replace_once(text, '    compare_canonical(*session, oracle, label);\n',
            '    compare_canonical(*session, oracle, label);\n' + conditional(
            '    statistics_acceptance::event(c01_before, *session->workload_statistics(), update, c01_changed, label, std::nullopt, update.has_value());\n'
            '    statistics_acceptance::sources(*session, oracle.database, label);\n'))
        text = replace_once(text, '    run();\n', '    run();\n' + conditional('    statistics_acceptance::print();\n'))
    target = PACKAGE / 'overlay/tests/unit' / name
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(text)

if __name__ == '__main__':
    for fixture in ['delta_runtime_test.cpp', 'delta_replay_test.cpp', 'window_test.cpp']:
        prepare(fixture)
