#!/usr/bin/env python3
"""Independent CROWNGR1 v1 golden-record generator."""
from __future__ import annotations

import hashlib
import json
import struct
from pathlib import Path

OUT = Path(__file__).resolve().parent
MAGIC = b"CROWNGR1"
VERSION = 1
FLAGS = 0
QUERY_ID = b"0123456789abcdef0123456789abcdef"
GENERATION = 7
FIRST_GENERATION = 3
CHECKPOINT_SHA256 = hashlib.sha256(b"checkpoint-payload").hexdigest().encode("ascii")
PHYSICAL_SEQUENCE = 11
COMMAND_SEQUENCE = 13

# The fixed 20-byte envelope prefix precedes this 128-byte payload.
payload = b"".join(
    (
        QUERY_ID,
        struct.pack("<Q", GENERATION),
        struct.pack("<Q", FIRST_GENERATION),
        CHECKPOINT_SHA256,
        struct.pack("<Q", PHYSICAL_SEQUENCE),
        struct.pack("<Q", COMMAND_SEQUENCE),
    )
)
assert len(payload) == 128
prefix = b"".join(
    (
        MAGIC,
        struct.pack("<H", VERSION),
        struct.pack("<H", FLAGS),
        struct.pack("<Q", len(payload)),
        payload,
    )
)
assert len(prefix) == 148
checksum = hashlib.sha256(prefix).hexdigest().encode("ascii")
record = prefix + checksum
assert len(record) == 212

fields = {
    "magic": {"offset": 0, "length": 8, "ascii": MAGIC.decode("ascii")},
    "version": {"offset": 8, "length": 2, "value": VERSION, "encoding": "little-endian u16"},
    "flags": {"offset": 10, "length": 2, "value": FLAGS, "encoding": "little-endian u16"},
    "payload_length": {"offset": 12, "length": 8, "value": len(payload), "encoding": "little-endian u64"},
    "query_id": {"offset": 20, "length": 32, "ascii": QUERY_ID.decode("ascii")},
    "generation": {"offset": 52, "length": 8, "value": GENERATION, "encoding": "little-endian u64"},
    "first_generation": {"offset": 60, "length": 8, "value": FIRST_GENERATION, "encoding": "little-endian u64"},
    "checkpoint_sha256": {"offset": 68, "length": 64, "ascii": CHECKPOINT_SHA256.decode("ascii")},
    "physical_sequence": {"offset": 132, "length": 8, "value": PHYSICAL_SEQUENCE, "encoding": "little-endian u64"},
    "command_sequence": {"offset": 140, "length": 8, "value": COMMAND_SEQUENCE, "encoding": "little-endian u64"},
    "record_sha256": {"offset": 148, "length": 64, "ascii": checksum.decode("ascii")},
}
manifest = {
    "format": "CROWNGR1",
    "version": VERSION,
    "flags": FLAGS,
    "payload_length": len(payload),
    "total_length": len(record),
    "query_id": QUERY_ID.decode("ascii"),
    "generation": GENERATION,
    "first_generation": FIRST_GENERATION,
    "checkpoint_sha256": CHECKPOINT_SHA256.decode("ascii"),
    "physical_sequence": PHYSICAL_SEQUENCE,
    "command_sequence": COMMAND_SEQUENCE,
    "checksum_sha256": checksum.decode("ascii"),
    "record_sha256": hashlib.sha256(record).hexdigest(),
    "offsets": fields,
}

(OUT / "root.hex").write_text(record.hex() + "\n", encoding="ascii")
(OUT / "manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")
print(f"record_bytes={len(record)} payload_bytes={len(payload)}")
print(f"checkpoint_sha256={CHECKPOINT_SHA256.decode('ascii')}")
print(f"checksum_sha256={checksum.decode('ascii')}")
print(f"record_sha256={manifest['record_sha256']}")
