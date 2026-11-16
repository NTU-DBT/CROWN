#!/usr/bin/env python3
"""Independently reconstruct a complete CROWNAC2 fixture using Python stdlib.

The native descriptor is hashed as opaque bytes, not interpreted as authority.
Every physical scalar/row, frontier, source offset and framing byte is specified
here independently of native codec code. This verifies transport, not fsync.
"""
import argparse
import datetime
import hashlib
import pathlib
import struct
import subprocess
import tempfile


def word(value):
    return struct.pack("<Q", value)


def integer(value):
    return b"\x01\x00" + struct.pack("<q", value)


def text(value):
    data = value.encode("utf8")
    return b"\x01\x01" + word(len(data)) + data


def date(value):
    days = (datetime.date.fromisoformat(value) - datetime.date(1970, 1, 1)).days
    return b"\x01\x03" + struct.pack("<i", days)


def decimal(value):
    data = value.encode("ascii")
    return b"\x01\x04" + bytes([len(data)]) + data


def expected(descriptor):
    body = b"0" * 32 + hashlib.sha256(descriptor).hexdigest().encode("ascii")
    body += word(7) + word(1) + word(4)
    body += b"2" * 32 + word(1) + word(1234) + b"c" * 64
    body += b"\x01" + word(200) + word(3) + word(2)
    for source, offset in (("feed α", 9), ("feed-z", 20)):
        data = source.encode("utf8")
        body += word(len(data)) + data + word(offset)
    body += word(2) + word(3)
    # Numeric TableId, then exact nullable row-wire order. Weight is not a key.
    a = word(5) + integer(-7) + text("µ") + b"\x01\x02\x01" + date("2024-02-29") + decimal("-1.25")
    b = word(5) + integer(8) + b"\x00" + b"\x01\x02\x00" + date("2000-01-01") + decimal("0")
    for row, weight in sorted(((a, 2), (b, 1))):
        body += word(0) + row + word(weight)
    body += word(1) + word(1) + integer(-1) + word(3)
    prefix = b"CROWNAC2" + struct.pack("<HHQ", 1, 0, len(body))
    prefix += hashlib.sha256(body).hexdigest().encode("ascii")
    return prefix + hashlib.sha256(prefix).hexdigest().encode("ascii") + body


def main():
    if not __debug__:
        raise RuntimeError("wire verifier requires Python assertions")
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True)
    args = parser.parse_args()
    with tempfile.TemporaryDirectory(prefix="crown-r2-wire-") as directory:
        run = subprocess.run([args.driver, directory], text=True, capture_output=True, timeout=300)
        assert run.returncode == 0, (run.stdout, run.stderr)
        path = pathlib.Path(directory)
        actual = (path / "checkpoint.bin").read_bytes()
        reference = expected((path / "descriptor.bin").read_bytes())
        assert actual == reference, (len(actual), len(reference))
        print(f"independent complete physical checkpoint: {len(actual)} exact bytes, SHA256 {hashlib.sha256(actual).hexdigest()}")


if __name__ == "__main__":
    main()
