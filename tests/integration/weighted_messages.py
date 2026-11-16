#!/usr/bin/env python3
"""Compare W02 state after every update against unbounded full-assignment joins.

The driver transports actual runtime snapshots. The oracle does no incremental
maintenance, checked-u64 arithmetic or runtime storage access. This is a semantic
and overflow regression, not a performance benchmark. Refactor.md §10.2.
"""
import importlib.util
import json
import pathlib
import random
import subprocess
import sys

root = pathlib.Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('weighted_oracle', root / 'tests/reference/weighted_oracle.py')
oracle = importlib.util.module_from_spec(spec)
spec.loader.exec_module(oracle)


def canonical(actual):
    """Ignore storage iteration order, preserving every typed key and count."""
    rows = {node['id']: {json.dumps(row['row']): (row['local'], row['subtree'], row['children'], row['supported'])
                        for row in node['rows']} for node in actual['nodes']}
    messages = {(entry['node'], json.dumps(entry['key'])): entry['count'] for entry in actual['messages']}
    return actual['root_count'], rows, messages


def expected_state(result):
    rows = {node['id']: {json.dumps(row['row']): (row['local'], row['subtree'],
            [child['value'] for child in row['cached_child_messages']], int(row['supported_count']))
            for row in node['rows']} for node in result['nodes']}
    messages = {(entry['node'], json.dumps(entry['key'])): entry['count'] for entry in result['messages']}
    return result['root_count'], rows, messages


def check_case(driver, fixture, updates, indexed, limit=(1 << 64)-1):
    request = dict(fixture=fixture, indexed=indexed, limit=str(limit), updates=updates)
    process = subprocess.run([driver], input=json.dumps(request)+'\n', text=True, capture_output=True, check=True)
    lines = [json.loads(line) for line in process.stdout.splitlines()]
    shape = lines.pop(0)
    assert len(lines) == len(updates)
    inputs = [{} for _ in shape['shape']]
    sequence = 0
    for step, (operation, actual) in enumerate(zip(updates, lines)):
        node = operation['node']
        key = tuple(operation['row'])
        before, after = int(operation['before']), int(operation['after'])
        old = inputs[node].get(key, 0)
        error = 'weight_conflict' if before != old else ''
        if not error:
            if after:
                inputs[node][key] = after
            else:
                inputs[node].pop(key, None)
        payload = dict(nodes=shape['shape'], root=shape['root'], route='tree',
                       inputs=[[dict(row=list(row), weight=str(weight)) for row, weight in table.items()]
                               for table in inputs])
        result = oracle.evaluate(payload)
        counts = [int(result['root_count'])]
        counts += [int(row[field]) for data in result['nodes'] for row in data['rows'] for field in ('local', 'subtree')]
        counts += [int(message['count']) for message in result['messages']]
        if not error and max(counts, default=0) > limit:
            error = 'annotation_overflow'
            if old:
                inputs[node][key] = old
            else:
                inputs[node].pop(key, None)
            payload['inputs'] = [[dict(row=list(row), weight=str(weight)) for row, weight in table.items()]
                                 for table in inputs]
            result = oracle.evaluate(payload)
        assert actual['error'] == error, (fixture, indexed, step, operation, actual['error'], error)
        sequence += not error
        assert actual['sequence'] == sequence
        assert canonical(actual) == expected_state(result), (fixture, indexed, step, operation)
    return len(updates)


def updates_for(fixture, count):
    randomizer = random.Random(720200 + count)
    current = {}
    result = []
    for _ in range(count):
        if fixture == 'generalized':
            node = randomizer.choice([1, 3, 4])
            row = [randomizer.randrange(3)]
            if node != 1:
                row += [randomizer.randrange(3), randomizer.randrange(2)]
        elif fixture == 'fanout':
            node = randomizer.choice([1, 2, 3])
            row = [randomizer.randrange(2)]
            if node == 1:
                row += [randomizer.randrange(2), randomizer.randrange(3)]
        else:
            node = randomizer.randrange(3)
            row = [randomizer.randrange(3)]
            if node != 2:
                row += [randomizer.randrange(3)]
        key = (node, tuple(row))
        before = current.get(key, 0)
        after = randomizer.randrange(8)
        result.append(dict(node=node, row=row, before=str(before), after=str(after)))
        current[key] = after
    return result


def main():
    driver = sys.argv[1]
    checked = 0
    for indexed in (False, True):
        for fixture in ('path', 'generalized', 'fanout'):
            checked += check_case(driver, fixture, updates_for(fixture, 250), indexed)
        # Exceed both binary64 precision and the declared u64 domain; the
        # unbounded reference determines rejection, then verifies retry/state.
        checked += check_case(driver, 'unary', [
            dict(node=0, row=[1], before='0', after='9007199254740993'),
            dict(node=0, row=[2], before='0', after=str((1 << 64)-1)),
            dict(node=0, row=[1], before='9007199254740993', after='0'),
            dict(node=0, row=[2], before='0', after=str((1 << 64)-1)),
            dict(node=0, row=[2], before=str((1 << 64)-1), after='1'),
            dict(node=0, row=[2], before='99', after='5')], indexed)
        checked += check_case(driver, 'nullary', [
            dict(node=0, row=[], before='0', after=str((1 << 64)-1)),
            dict(node=0, row=[], before=str((1 << 64)-1), after='0')], indexed)
    print(f'weighted arbitrary-precision oracle: {checked} update states, both backends')


if __name__ == '__main__':
    main()
