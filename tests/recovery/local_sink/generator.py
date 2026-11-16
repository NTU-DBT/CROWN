#!/usr/bin/env python3
"""Independent golden generator for the CROWNSK1 local sink epoch frame."""

from datetime import date
import hashlib
import json
from pathlib import Path
import struct


OUT = Path(__file__).resolve().parent
MAGIC = b"CROWNSK1"
VERSION = 1
FLAGS = 0


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def span(start, length):
    return {"offset": start, "length": length, "end_exclusive": start + length}


def encode_scalar(kind, value):
    if kind == "int64":
        payload = struct.pack("<q", value)
        tag = 0
    elif kind == "string":
        payload = value.encode("utf-8")
        tag = 1
        payload = struct.pack("<Q", len(payload)) + payload
    elif kind == "bool":
        payload = struct.pack("<B", 1 if value else 0)
        tag = 2
    elif kind == "date":
        days = (value - date(1970, 1, 1)).days
        payload = struct.pack("<i", days)
        tag = 3
    elif kind == "decimal":
        payload = value.encode("ascii")
        if len(payload) > 255:
            raise ValueError("decimal fixture exceeds u8 length")
        payload = struct.pack("<B", len(payload)) + payload
        tag = 4
    else:
        raise ValueError("unknown scalar kind: " + kind)
    wire = struct.pack("<B", tag) + payload
    return wire, {"kind": kind, "tag": tag, "wire_length": len(wire)}


def encode_row(operation, values):
    parts = [struct.pack("<B", operation), struct.pack("<Q", len(values))]
    scalar_metadata = []
    row_offset = 0
    scalar_offset = 9
    for kind, value in values:
        wire, metadata = encode_scalar(kind, value)
        metadata["row_relative_span"] = span(scalar_offset, len(wire))
        parts.append(wire)
        scalar_metadata.append(metadata)
        scalar_offset += len(wire)
    encoded = b"".join(parts)
    return encoded, {
        "operation": operation,
        "arity": len(values),
        "length": len(encoded),
        "sha256": sha256(encoded),
        "scalars": scalar_metadata,
    }


insert, insert_metadata = encode_row(
    0,
    [
        ("int64", -7),
        ("string", "a\x00b"),
        ("bool", True),
        ("date", date(2024, 2, 29)),
        ("decimal", "-12.5"),
    ],
)
erase, erase_metadata = encode_row(
    1,
    [
        ("int64", 3),
        ("string", "中"),
        ("bool", False),
        ("date", date(1, 1, 1)),
        ("decimal", "0"),
    ],
)

rows = sorted(
    [(insert, insert_metadata, "insert"), (erase, erase_metadata, "erase")],
    key=lambda item: item[0],
)
if [item[2] for item in rows] != ["insert", "erase"]:
    raise AssertionError("fixture row sort order changed")

body_fields = [
    ("kind", struct.pack("<B", 1)),
    ("ordinal", struct.pack("<Q", 1)),
    ("generation", struct.pack("<Q", 7)),
    ("physical_sequence", struct.pack("<Q", 11)),
    ("row_count", struct.pack("<Q", 2)),
]
body_prefix = b"".join(value for _, value in body_fields)
row_wire = b"".join(item[0] for item in rows)
body = body_prefix + row_wire
body_sha = sha256(body).encode("ascii")
prefix = (
    MAGIC
    + struct.pack("<H", VERSION)
    + struct.pack("<H", FLAGS)
    + struct.pack("<Q", len(body))
    + body_sha
)
if len(prefix) != 84:
    raise AssertionError("protected prefix must be 84 bytes")
header_sha = sha256(prefix).encode("ascii")
header = prefix + header_sha
if len(header) != 148:
    raise AssertionError("complete header must be 148 bytes")
record = header + body

record_body_offset = len(header)
body_offset = record_body_offset
field_offsets = {}
cursor = body_offset
for name, value in body_fields:
    field_offsets[name] = span(cursor, len(value))
    cursor += len(value)

row_metadata = []
for encoded, metadata, name in rows:
    item = dict(metadata)
    item["name"] = name
    item["record_span"] = span(cursor, len(encoded))
    item["sha256"] = sha256(encoded)
    for scalar in item["scalars"]:
        relative = scalar.pop("row_relative_span")
        scalar["record_span"] = span(
            item["record_span"]["offset"] + relative["offset"],
            relative["length"],
        )
    row_metadata.append(item)
    cursor += len(encoded)
if cursor != len(record):
    raise AssertionError("row boundaries do not end at record boundary")

manifest = {
    "format": "CROWNSK1",
    "version": VERSION,
    "flags": FLAGS,
    "fields": {
        "magic": {"span": span(0, 8), "ascii": MAGIC.decode("ascii")},
        "version": {"span": span(8, 2), "value": VERSION, "encoding": "u16le"},
        "flags": {"span": span(10, 2), "value": FLAGS, "encoding": "u16le"},
        "body_size": {
            "span": span(12, 8),
            "value": len(body),
            "encoding": "u64le",
        },
        "body_sha256_ascii": {
            "span": span(20, 64),
            "value": body_sha.decode("ascii"),
        },
        "header_sha256_ascii": {
            "span": span(84, 64),
            "value": header_sha.decode("ascii"),
            "covers_span": span(0, 84),
        },
        "body": {"span": span(body_offset, len(body)), "sha256": sha256(body)},
        "body_fields": field_offsets,
    },
    "body_values": {
        "kind": 1,
        "ordinal": 1,
        "generation": 7,
        "physical_sequence": 11,
        "row_count": 2,
    },
    "rows_sorted_by_encoded_bytes": row_metadata,
    "lengths": {
        "header": len(header),
        "body": len(body),
        "record": len(record),
    },
    "hashes": {
        "body_sha256": sha256(body),
        "header_prefix_sha256": sha256(prefix),
        "record_sha256": sha256(record),
    },
}

(OUT / "epoch.hex").write_text(record.hex() + "\n", encoding="ascii")
(OUT / "manifest.json").write_text(
    json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8"
)
print("header bytes:", len(header))
print("body bytes:", len(body))
print("record bytes:", len(record))
print("body SHA256:", sha256(body))
print("header-prefix SHA256:", sha256(prefix))
print("record SHA256:", sha256(record))
