#!/usr/bin/env python3
"""Independent CROWNSI1/CROWNRI1 golden fixture generator.

This intentionally uses only Python's struct/hashlib implementation of the
documented wire layout. It does not call the C++ encoder or inspect a C++ image.
The synthetic binding is codec-only; it is not an admitted Program fixture.
"""

from hashlib import sha256
from pathlib import Path
import struct


U64_MAX = (1 << 64) - 1
MIB = 1024 * 1024


def u8(value: int) -> bytes:
    return struct.pack("<B", value)


def u16(value: int) -> bytes:
    return struct.pack("<H", value)


def u32(value: int) -> bytes:
    return struct.pack("<I", value)


def u64(value: int) -> bytes:
    return struct.pack("<Q", value)


def optional_u64(value: int | None) -> bytes:
    return u8(value is not None) + (u64(value) if value is not None else b"")


def text_u64(value: bytes) -> bytes:
    return u64(len(value)) + value


def scalar(tag: int, payload: bytes = b"") -> bytes:
    return u8(tag) + payload


def row(values: list[bytes]) -> bytes:
    return u64(len(values)) + b"".join(values)


def frame(magic: bytes, payload: bytes) -> bytes:
    assert len(magic) == 8
    header = magic + u16(1) + u16(0) + u64(len(payload)) + sha256(payload).hexdigest().encode("ascii")
    assert len(header) == 84
    return header + payload


# runtime/checkpoint_policy.hpp field order. Optional values are represented
# as (present, value), with absent values required to use a zero value word.
DEFAULT_DELTA_POLICY = (
    1, 1_000_000, U64_MAX,  # support work limit, support limit
    0, 0,                   # FIFO propagation, no transition capture
    2, 256, 1, 0, 1, 0,    # timed observation, capacity/sample/timing, reserved
    1, 1_000_000, U64_MAX,  # physical work limit, derivation limit
    1, 1, 0, 0,             # actual delta mode, SQL view, on-output, automatic
    1, 1_000_000,           # Delta work limit
    1, 1_000_000,           # cursor work limit
    1, 1_000_000,           # epoch-view work limit
    65_536, 64 * MIB,       # spool row and byte limits
)
assert len(DEFAULT_DELTA_POLICY) == 26


def runtime_image() -> bytes:
    # Exact native scalar tags from recovery/binary_detail.hpp:
    # 0=int64 bits, 1=raw bytes/u64 length, 2=bool, 3=signed epoch-day i32,
    # 4=canonical InlineDecimal text/u8 length.
    values = [
        scalar(0, u64(1 << 63)),
        scalar(1, text_u64(b"A\x00\xff")),
        scalar(2, u8(1)),
        scalar(3, u32(0)),
        scalar(4, u8(7) + b"-123.45"),
    ]

    payload = bytearray()
    payload += b"a" * 64
    payload += b"b" * 64
    payload += u64(7)  # catalog version
    payload += u64(99)  # committed epoch
    payload += u16(1)  # exact-nonnull-v1 arithmetic
    payload += b"".join(u64(word) for word in DEFAULT_DELTA_POLICY)
    payload += u64(2)  # tables
    payload += u64(0) + u64(2)  # table 0, two rows
    payload += row(values)
    payload += row([])  # retain an empty row
    payload += u64(1) + u64(0)  # table 1, empty
    return frame(b"CROWNRI1", bytes(payload))


def session_image(inner: bytes) -> bytes:
    body = bytearray()
    body += u32(1)  # native SessionCheckpoint version
    body += u8(3)  # stopped
    body += u8(1)  # typed_physical
    body += u8(0)  # input_failed
    body += u8(1)  # end_of_input
    body += u64(99)  # committed sequence
    body += b"".join(u64(word) for word in DEFAULT_DELTA_POLICY)
    body += u64(256 * MIB)  # captured receiving-account ceiling

    # Default SnapshotLimits.
    body += u64(65_536) + u64(64 * MIB) + optional_u64(1_000_000)

    # Default workload::Options: off, 4096 cells, period 1, offset 0,
    # detail budget 65536.
    body += u8(0) + u64(4096) + u64(1) + u64(0) + u64(65_536)

    # Default native InputOptions and InputLimits.
    body += u8(0)  # jsonl
    body += u64(MIB) + u64(MIB) + u64(4096) + u64(1024) + u64(1024)
    body += optional_u64(None) + optional_u64(1_000_000)  # total bytes, records
    body += u8(0)  # no table
    body += u8(ord(",")) + u8(1) + u8(0)  # delimiter, header, insert
    body += u64(0)  # relation-token map
    body += u8(0) + u8(0)  # no null token, no source ID
    body += u64(0)  # byte offset

    # Typed sessions retain default queue limits. The stopped source variant
    # stores only accepted progress (tag 2), not the closed queue checkpoint.
    body += u8(1)  # queue limits present
    body += u64(64) + u64(65_536) + u64(64 * MIB)
    body += u8(2)  # AccountedInputProgress source alternative
    body += u64(99) + u64(2)  # sequence, source-position count
    body += text_u64(b"alpha") + u64(0)
    body += text_u64(b"z") + u64(U64_MAX)
    body += u8(0)  # no window
    body += u64(len(inner)) + inner
    return frame(b"CROWNSI1", bytes(body))


def main() -> None:
    inner = runtime_image()
    outer = session_image(inner)
    fixture = Path(__file__).with_name("session-image-v1.hex")
    fixture.write_text(outer.hex() + "\n", encoding="ascii")
    print(f"runtime bytes={len(inner)} sha256={sha256(inner).hexdigest()}")
    print(f"session bytes={len(outer)} sha256={sha256(outer).hexdigest()}")
    print(f"fixture={fixture}")


if __name__ == "__main__":
    main()
