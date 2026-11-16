#!/usr/bin/env python3
"""Write independent R2 record goldens with Python stdlib byte/hash rules.

Usage: pass an output directory. No CROWN executable or JSON binding is read.
This describes the local transport format in docs/sql_aggregate_records.md;
it supplies no durable/native admission authority.
"""
import datetime
import hashlib
import pathlib
import struct
import sys


def word(value, width=8):
    """Encode a fixed-width unsigned little-endian wire integer."""
    return value.to_bytes(width, "little")


def frame(kind, ordinal, payload):
    """Protect exact body bytes and its length-bearing 84-byte prefix."""
    body = word(kind, 1) + word(ordinal) + payload
    prefix = b"CROWNAG2" + word(1, 2) + word(0, 2) + word(len(body))
    prefix += hashlib.sha256(body).hexdigest().encode("ascii")
    return prefix + hashlib.sha256(prefix).hexdigest().encode("ascii") + body


def text(value):
    """Encode a present TEXT cell; length measures UTF8 bytes."""
    data = value.encode("utf8")
    return b"\x01\x01" + word(len(data)) + data


def integer(value):
    """Encode a present signed bigint cell with its two's-complement bits."""
    return b"\x01\x00" + struct.pack("<q", value)


def fixtures():
    """Construct one explicit example per kind, including NULL/empty output."""
    binding = b"0" * 32 + b"a" * 64
    header = frame(0, 0, binding + word(7) + b"b" * 64 + word(0) + word(0))
    days = (datetime.date(2024, 2, 29) - datetime.date(1970, 1, 1)).days
    cells = text("µ") + integer(-2) + b"\x01\x02\x01"
    cells += b"\x01\x03" + struct.pack("<i", days)
    cells += b"\x01\x04\x05-1.25" + b"\x00"
    edit = word(0) + word(6) + cells + word(0) + word(2)
    source = b"\x01" + word(4) + b"feed" + word(9)
    reader = b"\x01" + word(200) + word(1)
    command = frame(1, 1, word(1) + word(1) + edit + source + reader)
    input_hash = hashlib.sha256(command[148:]).hexdigest().encode("ascii")
    key = word(1) + text("µ")
    values = word(2) + text("µ") + integer(2)
    epoch = frame(5, 1, word(7) + word(1) + word(1) + input_hash
                  + b"\x01\x01" + word(1) + key + b"\x00\x01" + values)
    commit = frame(2, 2, word(1) + input_hash + word(1) + word(1) + word(len(epoch))
                   + hashlib.sha256(epoch).hexdigest().encode("ascii"))
    reject = frame(3, 2, word(1) + input_hash + word(1) + word(0) + b"\x02")
    sink = frame(4, 0, binding + b"c" * 32 + word(0))
    empty = frame(5, 2, word(7) + word(2) + word(2) + b"d" * 64 + b"\x00\x00" + word(0))
    return {"wal-header": header, "input": command, "commit": commit, "reject": reject,
            "sink-header": sink, "group-epoch": epoch, "empty-epoch": empty}


if __name__ == "__main__":
    destination = pathlib.Path(sys.argv[1])
    destination.mkdir(parents=True, exist_ok=True)
    for name, value in fixtures().items():
        (destination / (name + ".hex")).write_text(value.hex() + "\n", encoding="ascii")
