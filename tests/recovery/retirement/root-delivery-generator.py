#!/usr/bin/env python3
"""Independent CROWNGR1/version-2 root with a durable delivery anchor."""

import hashlib
import json
from pathlib import Path
import struct


OUT = Path(__file__).resolve().parent
MAGIC = b"CROWNGR1"
VERSION = 2
FLAGS = 0


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def span(offset, length):
    return {"offset": offset, "length": length, "end_exclusive": offset + length}


def u16(value):
    return struct.pack("<H", value)


def u64(value):
    return struct.pack("<Q", value)


query_id = b"0123456789abcdef0123456789abcdef"
sink_id = b"fedcba9876543210fedcba9876543210"
checkpoint_sha = sha256(b"checkpoint-payload").encode("ascii")
content_sha = sha256(b"sink-prefix-chain").encode("ascii")

body = b"".join(
    [
        # Original 128-byte selected-root payload.
        query_id,
        u64(7),
        u64(3),
        checkpoint_sha,
        u64(11),
        u64(13),
        # 112-byte durable delivery anchor.
        sink_id,
        u64(11),
        u64(1234),
        content_sha,
    ]
)
if len(body) != 240:
    raise AssertionError("version-2 root body must be 240 bytes")

prefix = MAGIC + u16(VERSION) + u16(FLAGS) + u64(len(body))
covered = prefix + body
if len(covered) != 260:
    raise AssertionError("root checksum input must be the first 260 bytes")
checksum = sha256(covered).encode("ascii")
record = covered + checksum
if len(record) != 324:
    raise AssertionError("version-2 root record must be 324 bytes")

fields = {
    "magic": {"span": span(0, 8), "ascii": MAGIC.decode("ascii")},
    "version": {"span": span(8, 2), "value": VERSION, "encoding": "u16le"},
    "flags": {"span": span(10, 2), "value": FLAGS, "encoding": "u16le"},
    "body_length": {"span": span(12, 8), "value": len(body), "encoding": "u64le"},
    "old_root.query_id": {"span": span(20, 32), "value": query_id.decode("ascii"), "encoding": "ASCII32"},
    "old_root.generation": {"span": span(52, 8), "value": 7, "encoding": "u64le"},
    "old_root.first_generation": {"span": span(60, 8), "value": 3, "encoding": "u64le"},
    "old_root.checkpoint_sha256": {"span": span(68, 64), "value": checkpoint_sha.decode("ascii"), "encoding": "ASCII64 lowercase SHA256"},
    "old_root.physical_sequence": {"span": span(132, 8), "value": 11, "encoding": "u64le"},
    "old_root.command_sequence": {"span": span(140, 8), "value": 13, "encoding": "u64le"},
    "delivery.sink_id": {"span": span(148, 32), "value": sink_id.decode("ascii"), "encoding": "ASCII32"},
    "delivery.sequence": {"span": span(180, 8), "value": 11, "encoding": "u64le"},
    "delivery.bytes": {"span": span(188, 8), "value": 1234, "encoding": "u64le"},
    "delivery.content_sha256": {"span": span(196, 64), "value": content_sha.decode("ascii"), "encoding": "ASCII64 lowercase SHA256"},
    "checksum": {"span": span(260, 64), "value": checksum.decode("ascii"), "encoding": "ASCII64 lowercase SHA256", "covers": span(0, 260)},
}

manifest = {
    "format": "CROWNGR1",
    "version": VERSION,
    "flags": FLAGS,
    "values": {
        "query_id": query_id.decode("ascii"),
        "generation": 7,
        "first_generation": 3,
        "checkpoint_sha256": checkpoint_sha.decode("ascii"),
        "physical_sequence": 11,
        "command_sequence": 13,
        "delivery_sink_id": sink_id.decode("ascii"),
        "delivery_sequence": 11,
        "delivery_bytes": 1234,
        "delivery_content_sha256": content_sha.decode("ascii"),
    },
    "layout": fields,
    "lengths": {"prefix": 20, "body": len(body), "covered": len(covered), "checksum": 64, "record": len(record)},
    "hashes": {
        "body_sha256": sha256(body),
        "covered_prefix_sha256": sha256(covered),
        "record_sha256": sha256(record),
    },
}

(OUT / "root-delivery.hex").write_text(record.hex() + "\n", encoding="ascii")
(OUT / "root-delivery-manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")
print("body bytes:", len(body))
print("covered prefix bytes:", len(covered))
print("record bytes:", len(record))
print("body SHA256:", sha256(body))
print("covered prefix SHA256:", sha256(covered))
print("record SHA256:", sha256(record))
