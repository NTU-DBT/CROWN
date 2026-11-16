#!/usr/bin/env python3
"""Independent corrected CROWNWAL/version-1 partial-window fixture.

Wire order follows tests/recovery/journal/format.json. The identity and policy
come from its golden header. Version 1 stores query_id as 32 ASCII hex bytes;
the base sequences and input kind below are the only header-payload changes.
"""

from __future__ import annotations

import hashlib
import json
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parent
HEX_PATH = ROOT / "window-partial-metadata-prefix.hex"
MANIFEST_PATH = ROOT / "window-partial-metadata-prefix.manifest.json"
GOLDEN_HEADER_PATH = ROOT / "header.hex"

MAGIC = b"CROWNWAL"
VERSION = 1
FLAGS = 0
FRAME_PREFIX_BYTES = 84
FRAME_HEADER_BYTES = 148

QUERY_ID = "0123456789abcdef0123456789abcdef"
PHYSICAL_SHA256 = "a" * 64
SOURCE_SHA256 = "b" * 64
CHECKPOINT_SHA256 = "c" * 64
CATALOG_VERSION = 7
GENERATION = 1

# The 26 policy words from the maintained format.json default_policy.
DEFAULT_POLICY = [
    1, 1000000, 18446744073709551615, 0, 0, 2, 256, 1, 0, 1, 0, 1,
    1000000, 18446744073709551615, 1, 1, 0, 0, 1, 1000000, 1, 1000000,
    1, 1000000, 65536, 67108864,
]


def u8(value: int) -> bytes:
    return struct.pack("<B", value)


def u16(value: int) -> bytes:
    return struct.pack("<H", value)


def u64(value: int) -> bytes:
    return struct.pack("<Q", value)


def digest_hex(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def make_frame(kind: int, ordinal: int, payload: bytes) -> tuple[bytes, str, str]:
    body = u8(kind) + u64(ordinal) + payload
    prefix = (
        MAGIC
        + u16(VERSION)
        + u16(FLAGS)
        + u64(len(body))
        + digest_hex(body).encode("ascii")
    )
    assert len(prefix) == FRAME_PREFIX_BYTES
    frame = prefix + digest_hex(prefix).encode("ascii") + body
    assert len(frame) == FRAME_HEADER_BYTES + len(body)
    return frame, digest_hex(body), digest_hex(frame)


def main() -> None:
    assert len(DEFAULT_POLICY) == 26
    golden_header = bytes.fromhex(GOLDEN_HEADER_PATH.read_text(encoding="ascii").strip())
    assert golden_header[:8] == MAGIC
    golden_payload_start = FRAME_HEADER_BYTES + 9
    golden_payload = golden_header[golden_payload_start:]
    assert len(golden_payload) == 467
    assert golden_payload[:32] == QUERY_ID.encode("ascii")

    header_payload = (
        QUERY_ID.encode("ascii")
        + u64(GENERATION)
        + PHYSICAL_SHA256.encode("ascii")
        + SOURCE_SHA256.encode("ascii")
        + u64(CATALOG_VERSION)
        + u16(1)
        + b"".join(u64(word) for word in DEFAULT_POLICY)
        + CHECKPOINT_SHA256.encode("ascii")
        + u64(2)
        + u64(5)
        + u8(2)
    )
    assert len(header_payload) == 467

    # Confirm the golden header payload matches byte-for-byte apart from the
    # requested base physical, base command, and input-kind fields.
    expected_payload = bytearray(golden_payload)
    expected_payload[450:458] = u64(2)
    expected_payload[458:466] = u64(5)
    expected_payload[466:467] = u8(2)
    assert header_payload == bytes(expected_payload)

    frames = []
    frame, body_sha, frame_sha = make_frame(0, 0, header_payload)
    assert len(frame) == 624
    assert frame[golden_payload_start:golden_payload_start + 32] == golden_header[
        golden_payload_start:golden_payload_start + 32
    ]
    frames.append(("header", 0, frame, body_sha, frame_sha))

    input_payload = u8(1) + u64(6) + u8(2) + u64(30) + u8(0) + u8(0)
    frame, input_body_sha, frame_sha = make_frame(1, 1, input_payload)
    frames.append(("watermark_input", 1, frame, input_body_sha, frame_sha))

    # A non-final metadata-only expiration keeps both sequences and advances
    # only the input's substep. This is the corrected version-1 rule.
    metadata_payload = (
        u64(1)
        + input_body_sha.encode("ascii")
        + u8(1)
        + u64(2)
        + u64(5)
        + u64(0)
        + u8(0)
    )
    frame, body_sha, frame_sha = make_frame(2, 2, metadata_payload)
    frames.append(("incomplete_metadata_commit", 2, frame, body_sha, frame_sha))

    physical_payload = (
        u64(1)
        + input_body_sha.encode("ascii")
        + u8(0)
        + u64(3)
        + u64(6)
        + u64(1)
        + u8(1)
    )
    frame, body_sha, frame_sha = make_frame(2, 3, physical_payload)
    frames.append(("completing_physical_commit", 3, frame, body_sha, frame_sha))

    stream = b"".join(item[2] for item in frames)
    HEX_PATH.write_text(stream.hex() + "\n", encoding="ascii")

    offset = 0
    frame_manifest = []
    for name, ordinal, data, body_hash, frame_hash in frames:
        end = offset + len(data)
        frame_manifest.append(
            {
                "name": name,
                "ordinal": ordinal,
                "offset": offset,
                "end_offset": end,
                "length": len(data),
                "body_sha256": body_hash,
                "frame_sha256": frame_hash,
            }
        )
        offset = end

    manifest = {
        "format": "CROWNWAL/version1",
        "generator_source": {"file": Path(__file__).name, "sha256": digest_hex(Path(__file__).read_bytes())},
        "format_spec_sha256": digest_hex((ROOT / "format.json").read_bytes()),
        "wire_version": VERSION,
        "flags": FLAGS,
        "frame_prefix_bytes": FRAME_PREFIX_BYTES,
        "frame_header_bytes": FRAME_HEADER_BYTES,
        "query_id": QUERY_ID,
        "query_id_wire_encoding": "32 lowercase ASCII hex bytes",
        "generation": GENERATION,
        "physical_sha256": PHYSICAL_SHA256,
        "source_sha256": SOURCE_SHA256,
        "catalog_version": CATALOG_VERSION,
        "checkpoint_sha256": CHECKPOINT_SHA256,
        "default_policy_words": DEFAULT_POLICY,
        "base_physical_sequence": 2,
        "base_command_sequence": 5,
        "input_kind": "window",
        "watermark_input_sequence": 6,
        "watermark": 30,
        "input_body_sha256": input_body_sha,
        "stream_hex_file": HEX_PATH.name,
        "stream_bytes": len(stream),
        "stream_sha256": digest_hex(stream),
        "final_physical_sequence": 3,
        "final_command_sequence": 6,
        "pending_input": None,
        "frames": frame_manifest,
    }
    MANIFEST_PATH.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")

    print(f"stream bytes={len(stream)} sha256={digest_hex(stream)}")
    for item in frame_manifest:
        print(
            f"{item['name']}: offset={item['offset']} end={item['end_offset']} "
            f"bytes={item['length']} body_sha256={item['body_sha256']} "
            f"frame_sha256={item['frame_sha256']}"
        )


if __name__ == "__main__":
    main()
