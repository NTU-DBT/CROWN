# C01 statistics report independent review

2026-11-07. Independent Astra Max source review of the excluded report proposal, finalized after the author's freeze and the identity checks below. **No blocking implementation defect established in the reviewed report/runtime-context scope.** This is not execution acceptance, native integration acceptance, or completion of C01; C01 remains `not_started`.

The review changed only this document. It did not execute any project binary, Python checker, CMake, CTest, `nm`, or benchmark, and did not modify native files, frozen proposals, or the report author's package. No additional diagnostic was compiled because source inspection did not identify a concrete failing case requiring one.

## Input identities

The reviewed package is `docs/verification/c01-statistics-report-proposal/`. All paths in the table are relative to that directory unless stated otherwise. Earlier draft source-manifest identities are superseded by these final pins.

| Input | SHA-256 |
| --- | --- |
| `PACKAGE_SHA256SUMS` — 68 entries | `730a7488e53a749b024b307dab27c09d58a324ae7603bccc8831364af289f947` |
| `source-files.sha256` — 48 overlay entries | `c8b5c3f43eb513e3fab9163bf4d3f8fb62662f73cd6cc0bd01667878a535216c` |
| `INPUT_SHA256SUMS` — 154 entries | `35f8ccd336d48f9b7c0258531f76097820af9072f7dd66a540afac444b0d9e50` |
| `README.md` | `1fa2c9f5a1ab38eb61b99c8ace4983f365c42d6261dedf9eb12c352123bbf519` |
| `BUILD_RESULTS.md` | `ea2dc9465c3ac0c5cce68c9a085206e7dec06bffe37327d710170535eeeb79c2` |
| `ROOT_REPRODUCTION.md` | `4b8079dc05ad9dbe8ab8a7e0f79b117dd1e76a341fc732a26a6c6ae53f9b8fa3` |
| `source-map.md` | `5d19970532e00f72ebcfaf96288f1a2f87cee3943301ec0dadb56f038b9355a2` |
| `check_reports.py` | `3c7a12c18c3e9b1eb1ff09e56ad620f966d02f6de41435aa3aa6d207fe9a426b` |
| `overlay/schemas/statistics-explain-v3.schema.json` | `0ede47d885bdd1d2b3c22077009521c38d9d4f6a055a42235c527ff576c919b2` |
| `overlay/src/runtime/session.cpp` | `c81162d5af55e2da6097335791086198a83c74226469326986c696040308efbe` |
| `overlay/src/observability/statistics_explain.cpp` | `c077a0ce6cdd64ad30c8a60de3716ce96b9723749f6ee82c6d29ce6e746c8cf8` |
| `overlay/src/io/statistics_explain.cpp` | `85e697da2c06c6bfe8e5eb92d5148168cecdf5179cb5adcf750b673ac4147697` |
| `build-evidence/production-artifacts.sha256` — 96 entries | `efbdffd768c4667f8981857e8061f924e338b8a226d4aec96785bc4e1b70f64e` |
| `build-evidence/testing-artifacts.sha256` — 101 entries | `4d60675f5a8fd260312dc39cab9560ff7cac3eda9bd7a94624a9ca8d3cb373f2` |
| `build-evidence/legacy-control-artifacts.sha256` — 14 entries | `170ee832043dad1dd36cb583364dfdcc7cc9a8b923f60f45d57363156e76b6d6` |
| Frozen combined predecessor `PACKAGE_SHA256SUMS` | `cb0ecb64935f80bf4915aa069de1bf01bcf1ea2f22a591f6f7408d405fcf4cfe` |
| Native O07 ordinary source seal, 691 entries | `f4acf6ea043859d350aa0dd2d56c86afca24535d7288eb5774f94b26ab0ea21e` |
| Repository `Refactor.md` | `bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce` |

From the repository root, `sha256sum --quiet -c` exited 0 independently for the package, source, input, production-artifact, testing-artifact, and legacy-control-artifact manifests. This checked 68/48/154/96/101/14 entries respectively; overlapping entries are not distinct inputs. The artifact checks include the actual recorded objects, executables, dependencies, and logs. Hashing an executable is not execution evidence.

The parent reported successful execution of the frozen combined and scalar proposals. Those are predecessor evidence; this review does not relabel them as report-proposal test results. `Refactor.md` C01 and Section 9.2 remain the acceptance context, including measured overhead and memory, exact small-data agreement, and explicit unknown/stale statistics.

## Findings and inspected invariants

**No unresolved blocking finding in this scope.** The following conclusions concern the inspected implementation, not an assertion that tests prove every requirement.

| Area | Inspection result |
| --- | --- |
| Runtime-only session seam | `SessionStatisticsContext` is factory-created, holds a private immutable owning payload, and keeps both handles usable after its copy-like move. `QuerySession::capture_statistics_context` takes one `Impl::Guard`, then obtains metadata, status, observation trace, optional joint statistics, fixed workload options, and cursor context from that same session boundary. Its implementation contains no observability dependency. Allocation failure unwinds the guard and publishes no handle. |
| Archive layering | The recorded runtime-only link uses the first 15 runtime/IO-support objects and the five foundation archives, with no observability or report IO object. The native CMake library dependencies keep those foundation archives below runtime/report layers. The separate all-object report link is therefore supplemented by a meaningful runtime-only link check. Native CMake registration is explicitly unfinished. |
| Owner, epoch, plan, modes, and pending state | The inherited private `CombinedCapture` constructor checks state/workload owner, committed epoch, physical plan identity, and pending agreement. The new report factory reconciles that pair with actual runtime/session metadata, workload options, requested/resolved modes, and the current observation configuration. Callers cannot supply arbitrary metadata, paired snapshots, or availability flags to these factories. The historical O07 summary retains its begin configuration when the current runtime changes mode. |
| Disabled, private, stopped, and released states | Absent state selection skips traversal and exports `not_requested`; C01-off workload data is null with `disabled`. Pending data remains private, including metadata-only window work whose underlying delta state can still be `ready`. Stopped sessions retain a readable committed owner. Dropped sessions export no joint state/workload value and retain options explicitly as the last configuration, rather than presenting released storage as a zero population. |
| Freshness and interval domains | Committed-data freshness uses owner/sequence identity and the supplied event lag. Configuration, reset, and segment comparisons are separate numeric domains; foreign-owner and saturated labels take precedence over equality. Mode changes and resets need not make committed data stale. These fields must be read together: reset/configuration can restart segment numbering at zero, so `segment=same` alone does not identify a shared collection interval. |
| Typed transport | Native strings, layout binding bytes, and declared label bytes are emitted as lowercase hexadecimal, preserving NUL and high bytes. Typed rows preserve scalar tags, signed integer values, Boolean values, and native canonical Date/Decimal text. No floating conversion is used for Decimal or integer serialization. Repeated and empty projections remain distinct from an absent projection request. |
| Complete-artifact export limits | The writer checks remaining encoded bytes before each append and JSON-value item count before each item. Human output uses the same JSON plus a charged fixed introduction and newline. Results are returned only after full rendering; an exception does not return partial output. These are encoded artifact limits, with string capacity/allocator overhead explicitly excluded. They do not replace state traversal or allocator/peak-memory accounting. |
| Unknown and lower-bound facts | Unavailable cardinalities and NDVs have null values and reasons; incomplete distributions do not export partial histograms as exact. Sampled ratios retain the complete-sample denominator scope. Global metadata or cell saturation suppresses derived numerator/denominator facts. Empty observed populations have unavailable extrema. Raw clipped counts remain labelled as lower bounds, and previous segments are explicitly raw observations without derived ratios. |
| Legacy v2 | Both live runtime and session legacy capture paths reject enabled C01 through `explain_statistics_version`, including retained enabled configuration after session release. C01-off capture keeps the original serializer path. The separate frozen-combined control uses original report objects and frozen headers, providing an independent target for the two proposed byte comparisons. Compile-only plan reporting remains available and carries no claim to current owner statistics. |

During draft review, the author identified and corrected one population-label defect before freeze: `generalized_probe` uses a degree-kind cell but records 0/1 pre-probe presence. The reviewed correction labels it `generalized_pre_probe_presence`, distinct from native directed child-event degrees. The added two-input fixture and independent child-set replay in the checker require exactly one absent and one present probe. The corrected writer, fixture, checker, and schema are included in the final pins above. This is a resolved pre-freeze correction, not an unresolved finding against final bytes.

## Evidence and limits

The author supplied strict production/testing compile/link records for 23 implementation/report translation units per variant, 5 production and 6 testing consumer executables, and a separate frozen-combined legacy control. The review inspected the commands/source closure and verified the recorded final artifact identities, including the corrected units and relinks. Both runtime-only link commands contain the 15 runtime objects and zero report/observability objects. Execution, schema/checker validation, allocation-sweep outcomes, sanitizer/leak checks, and final acceptance belong to root; no such report-proposal outcome is asserted here without a separate root record.

The proposed fixtures cover literal state populations, state/event differences, disabled collection, sampled and truncated detail, state budget exhaustion, historical begin/current mode separation, reset/configuration/segment changes, private/prepared/unread/aborted states, stale/within-lag/foreign ownership, retained immutable handles, stopped/dropped sessions, metadata-only windows, hidden visible support, typed byte transport, generalized probe populations, and exact/one-under/zero export limits. The C++ and Python assertions are inspected test intentions until executed by root.

The material coverage limits are:

- The two legacy byte comparisons cover one C01-off runtime and one session fixture, not every existing v2 report, CLI path, policy, or lifecycle.
- The new report producer uses O07 off/counters. Timed/trace combinations, dropped trace storage, and O07 metric saturation are not independently exercised by this producer. The shared native observation behavior was inspected; earlier O07 results are separate evidence.
- The testing saturation seam clips global metadata and every cell together, and seeds configuration/segment saturation together. It demonstrates the intended rendering path but does not isolate each clipping source, aggregate-denominator overflow, or reset-generation saturation.
- Configuration/reset/segment comparisons are not a single interval-identity predicate. The fixture does not exhaust every sequence of reconfiguration, reset, and mode changes that can reuse a segment number.
- The transport fixture contains integer/date endpoints, both Boolean values, canonical Decimal examples, raw NUL/high bytes, repeated fields, and an empty projection. It is not exhaustive Decimal boundary transport coverage; the separate scalar proposal's wider capture checks do not automatically establish JSON coverage.
- Mutation checks test schema/selected semantic rejection of edited exported documents. They do not establish general import validation, prove every cross-field invariant, or exercise private factory mismatch branches through a public constructor. Report JSON has no plan/proof/import authority.
- The four proposed allocation sweeps are targeted. The inherited workload comparison helper checks a subset of snapshot fields; immutable retained bytes and literal state checks add evidence but do not make the sweeps exhaustive.

The package explicitly leaves native source-list/CLI integration, the full policy and legacy matrices, and measured collection overhead open. Its preparation-only `c01_project_gate=open` must be reconciled with repository acceptance before the final native C01 matrix, as the frozen README states. Arrival Hz, timed C01 collection, cost ranking, global cost optimality, and total allocator/peak-state bytes remain unavailable or unimplemented. Those disclosed limits are not hidden defects and this review does not convert component-capacity accounting into S05 totals.
