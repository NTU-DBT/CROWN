#!/usr/bin/env python3
"""Independent maintained CROWNWAL/version1 golden-frame generator.

The wire constants and field order follow the local format.json. Frames protect
the original 84-byte prefix with an additional SHA256 before the unchanged body.
This generator uses Python struct/hashlib only and does not call a C++ codec.
"""

from __future__ import annotations

import hashlib
import json
import struct
from pathlib import Path


HERE = Path(__file__).resolve().parent
OUTPUT = HERE
SPEC_PATH = HERE / "format.json"
SPEC_BYTES = SPEC_PATH.read_bytes()
SPEC = json.loads(SPEC_BYTES.decode("utf-8"))
EXPECTED_INPUT_BODY_SHA256 = (
    "7dc08dba65898efde205ca8008e3b4b102e79c13f7fcdee0b52af9edfe3c9779"
)


def u8(value: int) -> bytes:
    return struct.pack("<B", value)


def u16(value: int) -> bytes:
    return struct.pack("<H", value)


def u32(value: int) -> bytes:
    return struct.pack("<I", value)


def u64(value: int) -> bytes:
    return struct.pack("<Q", value)


def i64_bits(value: int) -> bytes:
    return struct.pack("<Q", value & ((1 << 64) - 1))


def body_prefix(kind: int, ordinal: int) -> bytes:
    return u8(kind) + u64(ordinal)


def frame(body: bytes) -> bytes:
    digest = hashlib.sha256(body).hexdigest().encode("ascii")
    prefix = (
        SPEC["magic"].encode("ascii")
        + u16(SPEC["version"])
        + u16(0)  # flags
        + u64(len(body))
        + digest
    )
    if len(prefix) != 84:
        raise ValueError("CROWNWAL prefix must remain exactly 84 bytes")
    prefix_checksum = hashlib.sha256(prefix).hexdigest().encode("ascii")
    return prefix + prefix_checksum + body


def row(cells: list[tuple[int, bytes]]) -> bytes:
    return u64(len(cells)) + b"".join(tagged for _, tagged in cells)


def int64_cell(value: int) -> tuple[int, bytes]:
    return 0, u8(0) + i64_bits(value)


def raw_cell(value: bytes) -> tuple[int, bytes]:
    return 1, u8(1) + u64(len(value)) + value


def bool_cell(value: bool) -> tuple[int, bytes]:
    return 2, u8(2) + u8(1 if value else 0)


def epoch_day_cell(days: int) -> tuple[int, bytes]:
    return 3, u8(3) + u32(days & 0xFFFFFFFF)


def decimal_cell(text: str) -> tuple[int, bytes]:
    encoded = text.encode("ascii")
    if len(encoded) > 0xFF:
        raise ValueError("decimal text exceeds the one-byte wire length")
    return 4, u8(4) + u8(len(encoded)) + encoded


def source(present: bool, name: str = "", offset: int = 0) -> bytes:
    if not present:
        return u8(0)
    encoded = name.encode("utf-8")
    if not encoded or b"\0" in encoded:
        raise ValueError("source name must be nonempty UTF-8 without NUL")
    return u8(1) + u64(len(encoded)) + encoded + u64(offset)


def reader_progress(
    present: bool,
    *,
    byte_count: int = 0,
    records: int = 0,
    header_read: bool = False,
    permutation: tuple[int, ...] = (),
) -> bytes:
    if not present:
        return u8(0)
    return (
        u8(1)
        + u64(byte_count)
        + u64(records)
        + u8(1 if header_read else 0)
        + u64(len(permutation))
        + b"".join(u64(field) for field in permutation)
    )


def input_body(
    ordinal: int,
    sequence: int,
    item_tag: int,
    payload: bytes,
    source_bytes: bytes,
    reader_bytes: bytes,
) -> bytes:
    return (
        body_prefix(1, ordinal)
        + u8(item_tag)
        + u64(sequence)
        + payload
        + source_bytes
        + reader_bytes
    )


def named_row() -> bytes:
    cells = [
        int64_cell(-(1 << 63)),
        raw_cell(b"A\0\xff"),
        bool_cell(True),
        epoch_day_cell(0),  # 1970-01-01
        decimal_cell("-123.45"),
    ]
    return row(cells)


def build_frames() -> tuple[dict[str, tuple[bytes, bytes]], bytes]:
    magic = SPEC["magic"].encode("ascii")
    policy = SPEC["default_policy"]
    if magic != b"CROWNWAL" or SPEC["version"] != 1:
        raise ValueError("format.json must describe maintained CROWNWAL/version1")
    if len(magic) != 8 or len(policy) != 26:
        raise ValueError("format.json has an unexpected magic or runtime policy width")
    if any(value < 0 or value > 0xFFFFFFFFFFFFFFFF for value in policy):
        raise ValueError("default policy word is outside u64")

    query_id = b"0123456789abcdef0123456789abcdef"
    physical_sha = b"a" * 64
    source_sha = b"b" * 64
    base_checkpoint_sha = b"c" * 64
    final_checkpoint_sha = b"d" * 64

    header_body = (
        body_prefix(0, 0)
        + query_id
        + u64(1)  # generation
        + physical_sha
        + source_sha
        + u64(7)  # catalog version
        + u16(1)  # arithmetic identity: exact-nonnull-v1
        + b"".join(u64(word) for word in policy)
        + base_checkpoint_sha
        + u64(0)  # base physical sequence
        + u64(0)  # base command sequence
        + u8(0)  # stream input kind
    )

    physical_payload = (
        u64(0)  # table
        + u8(0)  # insert
        + named_row()
    )
    physical_body = input_body(
        1,
        1,
        0,  # physical item
        physical_payload,
        source(True, "alpha", 0),
        reader_progress(
            True,
            byte_count=123,
            records=1,
            header_read=True,
            permutation=(1, 0),
        ),
    )

    input_body_sha = hashlib.sha256(physical_body).hexdigest().encode("ascii")
    commit_body = (
        body_prefix(2, 2)
        + u64(1)  # input ordinal
        + input_body_sha
        + u8(0)  # physical commit
        + u64(1)  # physical sequence
        + u64(1)  # completed command sequence
        + u64(0)  # substep
        + u8(1)  # completes input
    )

    checkpoint_body = (
        body_prefix(3, 3)
        + u64(1)  # physical sequence
        + u64(1)  # command sequence
        + final_checkpoint_sha
    )

    empty_row = row([])
    window_insert_body = input_body(
        4,
        2,
        1,  # window item
        u8(0) + u64(9) + u64(0) + empty_row + u64(100),  # insert
        source(False),
        reader_progress(False),
    )
    window_withdraw_body = input_body(
        5,
        3,
        1,  # window item
        u8(1) + u64(9),  # withdraw
        source(False),
        reader_progress(False),
    )
    window_watermark_body = input_body(
        6,
        4,
        1,  # window item
        u8(2) + u64(120),  # watermark
        source(False),
        reader_progress(False),
    )

    bodies = {
        "header": header_body,
        "physical-input": physical_body,
        "physical-commit": commit_body,
        "checkpoint": checkpoint_body,
        "window-insert-input": window_insert_body,
        "window-withdraw-input": window_withdraw_body,
        "window-watermark-input": window_watermark_body,
    }
    frames = {name: (body, frame(body)) for name, body in bodies.items()}
    return frames, physical_body


def main() -> None:
    OUTPUT.mkdir(exist_ok=True)
    frames, physical_body = build_frames()
    manifest_frames: dict[str, dict[str, object]] = {}
    for name, (body, framed) in frames.items():
        hex_name = f"{name}.hex"
        hex_text = framed.hex() + "\n"
        (OUTPUT / hex_name).write_text(hex_text, encoding="ascii", newline="")
        manifest_frames[name] = {
            "hex_file": hex_name,
            "body_bytes": len(body),
            "body_sha256": hashlib.sha256(body).hexdigest(),
            "frame_bytes": len(framed),
            "frame_sha256": hashlib.sha256(framed).hexdigest(),
            "prefix84_sha256": hashlib.sha256(framed[:84]).hexdigest(),
            "hex_file_bytes": len(hex_text.encode("ascii")),
        }

    generator_bytes = Path(__file__).read_bytes()
    input_body_sha = hashlib.sha256(physical_body).hexdigest()
    if input_body_sha != EXPECTED_INPUT_BODY_SHA256:
        raise ValueError("maintained frame changed the original input body")
    manifest = {
        "format": SPEC["magic"],
        "version": SPEC["version"],
        "integer_byte_order": "little",
        "header_layout": {
            "original_prefix_bytes": 84,
            "prefix_checksum_bytes": 64,
            "total_header_bytes": 148,
            "prefix_checksum": "lowercase ASCII SHA256 of the original 84-byte prefix",
        },
        "format_spec": {
            "file": "format.json",
            "bytes": len(SPEC_BYTES),
            "sha256": hashlib.sha256(SPEC_BYTES).hexdigest(),
        },
        "generator_source": {
            "file": Path(__file__).name,
            "bytes": len(generator_bytes),
            "sha256": hashlib.sha256(generator_bytes).hexdigest(),
        },
        "fixture_fields": {
            "query_id": "0123456789abcdef0123456789abcdef",
            "generation": 1,
            "physical_sha256": "a" * 64,
            "source_sha256": "b" * 64,
            "catalog_version": 7,
            "arithmetic_identity": 1,
            "checkpoint_sha256": "c" * 64,
            "final_checkpoint_sha256": "d" * 64,
            "base_physical_sequence": 0,
            "base_command_sequence": 0,
            "input_kind": 0,
            "default_policy": SPEC["default_policy"],
        },
        "commit_binding": {
            "input_frame": "physical-input",
            "input_body_bytes": len(physical_body),
            "input_body_sha256": input_body_sha,
        },
        "frames": manifest_frames,
    }
    manifest_bytes = (
        json.dumps(manifest, indent=2, sort_keys=True) + "\n"
    ).encode("utf-8")
    (OUTPUT / "fixture-manifest.json").write_bytes(manifest_bytes)

    print(
        f"generator bytes={len(generator_bytes)} "
        f"sha256={hashlib.sha256(generator_bytes).hexdigest()}"
    )
    print(
        f"format bytes={len(SPEC_BYTES)} "
        f"sha256={hashlib.sha256(SPEC_BYTES).hexdigest()}"
    )
    print(f"input body bytes={len(physical_body)} sha256={input_body_sha}")
    for name, entry in manifest_frames.items():
        print(
            f"{name}: frame_bytes={entry['frame_bytes']} "
            f"sha256={entry['frame_sha256']} "
            f"prefix84_sha256={entry['prefix84_sha256']} "
            f"hex={entry['hex_file']}"
        )
    print(
        "fixture-manifest.json: "
        f"bytes={len(manifest_bytes)} "
        f"sha256={hashlib.sha256(manifest_bytes).hexdigest()}"
    )


if __name__ == "__main__":
    main()
