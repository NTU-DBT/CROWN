#!/usr/bin/env python3
"""Independent CROWNRT1/version-1 history-retirement intent fixture."""

import hashlib
import json
from pathlib import Path
import struct


OUT = Path(__file__).resolve().parent
MAGIC = b"CROWNRT1"
VERSION = 1
FLAGS = 0
DEFAULT_POLICY = [
    1, 1000000, 18446744073709551615, 0, 0, 2, 256, 1, 0, 1, 0, 1, 1000000,
    18446744073709551615, 1, 1, 0, 0, 1, 1000000, 1, 1000000, 1, 1000000,
    65536, 67108864,
]


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def span(offset, length):
    return {"offset": offset, "length": length, "end_exclusive": offset + length}


fields = {}
body_parts = []
cursor = 20  # 8-byte magic + u16 version + u16 flags + u64 body length


def add(name, data, value, encoding):
    global cursor
    body_parts.append(data)
    fields[name] = {
        "span": span(cursor, len(data)),
        "value": value,
        "encoding": encoding,
    }
    cursor += len(data)


query_id = b"0123456789abcdef0123456789abcdef"
sink_id = b"fedcba9876543210fedcba9876543210"
checkpoint_sha = sha256(b"checkpoint-payload").encode("ascii")
physical_sha = sha256(b"physical-plan").encode("ascii")
source_sha = sha256(b"source-catalog").encode("ascii")
schema_sha = sha256(bytes([0, 0, 0])).encode("ascii")

# Old selected root (128 bytes).
root_start = cursor
add("old_root.query_id", query_id, query_id.decode("ascii"), "ASCII32")
add("old_root.generation", struct.pack("<Q", 7), 7, "u64le")
add("old_root.first_generation", struct.pack("<Q", 3), 3, "u64le")
add("old_root.checkpoint_sha256", checkpoint_sha, checkpoint_sha.decode("ascii"), "ASCII64 lowercase SHA256")
add("old_root.physical_sequence", struct.pack("<Q", 11), 11, "u64le")
add("old_root.command_sequence", struct.pack("<Q", 13), 13, "u64le")
if cursor - root_start != 128:
    raise AssertionError("old root section must be 128 bytes")

# Sink header bound to the old root (496 bytes).
sink_start = cursor
add("sink_header.query_id", query_id, query_id.decode("ascii"), "ASCII32")
add("sink_header.sink_id", sink_id, sink_id.decode("ascii"), "ASCII32")
add("sink_header.physical_sha256", physical_sha, physical_sha.decode("ascii"), "ASCII64 lowercase SHA256")
add("sink_header.source_sha256", source_sha, source_sha.decode("ascii"), "ASCII64 lowercase SHA256")
add("sink_header.catalog_version", struct.pack("<Q", 5), 5, "u64le")
for index, word in enumerate(DEFAULT_POLICY):
    add("sink_header.policy[{}]".format(index), struct.pack("<Q", word), word, "u64le")
add("sink_header.first_generation", struct.pack("<Q", 3), 3, "u64le")
add("sink_header.base_sequence", struct.pack("<Q", 10), 10, "u64le")
add("sink_header.fields", struct.pack("<Q", 3), 3, "u64le")
add("sink_header.schema_sha256", schema_sha, schema_sha.decode("ascii"), "ASCII64 lowercase SHA256")
if cursor - sink_start != 496:
    raise AssertionError("sink header section must be 496 bytes")

add("acknowledged_generation", struct.pack("<Q", 7), 7, "u64le")
add("acknowledged_sequence", struct.pack("<Q", 11), 11, "u64le")
body = b"".join(body_parts)
if len(body) != 640 or cursor != 660:
    raise AssertionError("intent body must be 640 bytes and end at offset 660")

prefix = MAGIC + struct.pack("<H", VERSION) + struct.pack("<H", FLAGS) + struct.pack("<Q", len(body))
covered = prefix + body
if len(covered) != 660:
    raise AssertionError("checksum input must be the first 660 bytes")
checksum = sha256(covered).encode("ascii")
record = covered + checksum
if len(record) != 724:
    raise AssertionError("retirement intent record must be 724 bytes")

manifest = {
    "format": "CROWNRT1",
    "version": VERSION,
    "flags": FLAGS,
    "values": {
        "query_id": query_id.decode("ascii"),
        "root_generation": 7,
        "root_first_generation": 3,
        "root_checkpoint_sha256": checkpoint_sha.decode("ascii"),
        "root_physical_sequence": 11,
        "root_command_sequence": 13,
        "sink_id": sink_id.decode("ascii"),
        "sink_physical_sha256": physical_sha.decode("ascii"),
        "sink_source_sha256": source_sha.decode("ascii"),
        "sink_catalog_version": 5,
        "sink_policy": DEFAULT_POLICY,
        "sink_first_generation": 3,
        "sink_base_sequence": 10,
        "sink_fields": 3,
        "sink_schema_sha256": schema_sha.decode("ascii"),
        "acknowledged_generation": 7,
        "acknowledged_sequence": 11,
    },
    "layout": {
        "magic": {"span": span(0, 8), "ascii": MAGIC.decode("ascii")},
        "version": {"span": span(8, 2), "value": VERSION, "encoding": "u16le"},
        "flags": {"span": span(10, 2), "value": FLAGS, "encoding": "u16le"},
        "body_length": {"span": span(12, 8), "value": len(body), "encoding": "u64le"},
        "body": {"span": span(20, len(body)), "sha256": sha256(body)},
        "body_fields": fields,
        "checksum": {
            "span": span(660, 64),
            "value": checksum.decode("ascii"),
            "encoding": "ASCII64 lowercase SHA256",
            "covers": span(0, 660),
        },
    },
    "lengths": {"header_prefix": 20, "body": len(body), "checksum": 64, "record": len(record)},
    "hashes": {
        "body_sha256": sha256(body),
        "covered_prefix_sha256": sha256(covered),
        "record_sha256": sha256(record),
    },
}

(OUT / "intent.hex").write_text(record.hex() + "\n", encoding="ascii")
(OUT / "manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")
print("body bytes:", len(body))
print("covered prefix bytes:", len(covered))
print("record bytes:", len(record))
print("body SHA256:", sha256(body))
print("covered prefix SHA256:", sha256(covered))
print("record SHA256:", sha256(record))
