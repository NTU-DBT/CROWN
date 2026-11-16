#!/usr/bin/env python3
"""Independent CROWNPL1 v1 packet, using the pinned legacy intent's bindings."""
import argparse
import hashlib
from pathlib import Path
import struct


def digest(value):
    return hashlib.sha256(value).hexdigest().encode("ascii")


def packet(seed):
    assert len(seed) == 724 and seed[:8] == b"CROWNRT1"
    assert hashlib.sha256(seed).hexdigest() == "54e9f4216cb183cc3f55dc84d218586dfc25c87a12d6b69591d9afec775d4ace"
    assert struct.unpack_from("<HHQ", seed, 8) == (1, 0, 640)
    assert struct.unpack_from("<Q", seed, 140)[0] == 13
    parent = seed[20:148]  # query, generation/floor, checkpoint hash, two frontiers
    origin = seed[148:644]  # exact immutable sink header, 496 bytes
    source = origin[64:408]  # ImageBinding: physical/source/catalog/26 policy words
    target = digest(b"selected physical plan") + source[64:]
    artifact = b'{"compiler_input":"golden-test-only"}'
    body = (parent + digest(b"predecessor descriptor") + source + target
            + struct.pack("<QQQ", 8, 11, 14) + origin
            + struct.pack("<Q", len(artifact)) + artifact)
    prefix = b"CROWNPL1" + struct.pack("<HHQ", 1, 5, len(body)) + body
    result = prefix + digest(prefix)
    assert len(result) == 1529
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true", help="replace the golden; default checks it")
    args = parser.parse_args()
    directory = Path(__file__).resolve().parent
    expected = packet(bytes.fromhex((directory.parent / "retirement/intent.hex").read_text()))
    target = directory / "descriptor-v1.hex"
    if args.write:
        target.write_text(expected.hex() + "\n")
    else:
        assert bytes.fromhex(target.read_text()) == expected, "descriptor golden differs from independent packet"
    print("CROWNPL1 v1 independent 1529-byte golden PASS")


if __name__ == "__main__":
    main()
