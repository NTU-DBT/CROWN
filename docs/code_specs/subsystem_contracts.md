# Subsystem usage contracts

These contracts describe module boundaries and intended use. Source maps link this context separately; they do not assign it to every declaration or prove all branches or paper bounds. A block-specific reviewed contract has its own explicit scope.

## difference

| Field | Contract |
| --- | --- |
| purpose | Admit explicit set EXCEPT or bag EXCEPT ALL between two positive classical CQs and maintain exact compressed residual counts. |
| inputs / outputs | Two non-null public-IR operands over one full catalog produce one independent source owner, owning tuple/multiplicity snapshots and exact nonnegative endpoint replacements. |
| invariants | Set mode keeps left presence and right absence; bag mode counts complete physical-row assignments before projection and keeps max(left-right,0). Physical inputs stay sets. Positional output types match without coercing right Decimal keys into the left result layout. Positive operands cannot encode recursive negation cycles. |
| ownership | One original query account funds both frozen native operands, one deep source image, private consolidated counts, retained compressed answers and owning output. Cold pair admission copies/lowers both operands separately; compiler DTOs and explicit diagnostic exports keep caller ownership. |
| failure | One cumulative wrapper grant spans metadata or capture/both operand evaluations/residual and endpoint work. Prepare every fallible result before the existing physical source commit and nonthrowing answer swap. Native RAII/token rollback preserves prior state on work, count, row or allocation refusal. |
| cost | Full physical source capture, nested-loop prefixes and witnesses, scalar widths, ordered key consolidation, compressed materialization, endpoint merging and cleanup are real costs. Per-operand distinct caps and W01 checked uint64 multiplicities are separate. Advisory row/multiplicity bounds are not peak bytes or speed claims; no P11 or constant-delay CROWN bound is implied. |
| Design | [docs/difference.md](../difference.md), [docs/source_images.md](../source_images.md), [docs/annotations.md](../annotations.md), [Refactor.md](../../Refactor.md) |

## cq_recompute

| Field | Contract |
| --- | --- |
| purpose | Share funded positive-CQ metadata freezing and iterative complete-witness traversal between conservative recomputation owners. |
| inputs / outputs | A validated original query and native source schema freeze account-backed spans; a funded physical image and caller callback visit complete ordered-head assignments. |
| invariants | Original positive terms, aliases, constants, ignored fields and repeated variables survive. A binding trail restores ancestor assignments. The caller selects Boolean early termination versus full bag-witness traversal and performs projection consolidation; this primitive supplies no DISTINCT or difference semantics by itself. |
| ownership | Native metadata and iterative frames/bindings/projected views use the supplied original account. Callback views borrow private scratch and must not escape; the caller retains owning values explicitly. |
| failure | The caller supplies one cumulative budget and private callback. Exceptions unwind private scratch before publication; the helper adds no source owner, transaction journal, catch/retry loop or executable authority. |
| cost | Frozen metadata/bytes, iterative row/term/scalar work and each complete projection are charged through the caller. Templates add no virtual dispatch or allocated callback. Prefix/witness count, payload width, caller consolidation and cleanup remain explicit real costs. |
| Design | [docs/fallback.md](../fallback.md), [docs/difference.md](../difference.md), [docs/query_memory.md](../query_memory.md), [Refactor.md](../../Refactor.md) |

## fallback

| Field | Contract |
| --- | --- |
| purpose | Admit an explicit general classical CQ and maintain exact projected set answers through conservative full recomputation. |
| inputs / outputs | Non-null exact-set public query IR and its full original catalog produce an immutable classified plan, independent owner, owning snapshots and exact endpoint deltas. |
| invariants | Keep the actual cyclic, acyclic non-free-connex or free-connex classification and explicit fallback reason. The source-only lowering validates original physical sources; it is not a CROWN or GHD certificate for the original query. Complete assignments precede ordered/repeated head projection and DISTINCT; aliases, constants, ignored terms, Boolean and contradictory bodies keep classical meanings. |
| ownership | One original query account funds frozen native metadata, iterative binding/trail scratch, deep source images, private distinct candidates, retained native answers and owning outputs. Cold admission DTOs and explicit diagnostic source exports have separate caller ownership. |
| failure | Prepare the complete private result and endpoint differences before source commit. Existing source-token rollback and native RAII preserve the prior epoch on refusal; one busy guard spans source/result publication and old-state retirement. Pending captures reuse the original indexed lease without refilling it. |
| cost | One cumulative recomputation grant charges source capture, row/term/scalar work, full assignment evaluation, ordered deduplication, materialization and endpoint merging. Estimates are advisory row bounds with explicit overflow, not peak-byte bounds. Constructor import, allocation, owning snapshots and cleanup remain real costs; no constant-delay CROWN, GHD algorithm, shared-query or parallel bound is claimed. |
| Design | [docs/fallback.md](../fallback.md), [docs/source_images.md](../source_images.md), [docs/query_memory.md](../query_memory.md), [Refactor.md](../../Refactor.md) |

## comparisons

| Field | Contract |
| --- | --- |
| purpose | Admit an explicit typed comparison conjunction and maintain exact projected set answers over ordinary CQ propagation. |
| inputs / outputs | A genuine non-null direct-CQ plan plus six variable/constant comparison operators produces an opt-in owner, owning snapshots and exact endpoint added/removed sets. |
| invariants | Comparisons remain outside the equality query. Evaluate complete assignments, including hidden operands, before original ordered/repeated head projection and DISTINCT. All source aliases drain before answer recomputation. Empty conjunction and Boolean/constant/contradictory plans retain their exact meanings. |
| ownership | One original query account funds frozen comparison literals, metadata, private deduplication, retained native tuples and owning output. Compiler predicate DTOs and explicit source exports retain their external ownership boundary. |
| failure | Prepare comparison outputs and endpoint differences before source commit; private RAII work and the existing source token unwind refusal. One busy guard covers source/result publication and old-state retirement. No second journal or source clone is added. |
| cost | Ordinary source/equality maintenance plus full-assignment enumeration, predicate/field/byte work, ordered deduplication, output materialization and endpoint merging are explicit. Constructor import and initial results share one wrapper grant; each cursor uses one cumulative producer grant. Cleanup and retained snapshots remain separate real costs; no specialized P9 or dynamic comparison bound is claimed. |
| Design | [docs/comparisons.md](../comparisons.md), [docs/query_memory.md](../query_memory.md), [docs/code_review.md](../code_review.md) |

## star

| Field | Contract |
| --- | --- |
| purpose | Admit and maintain exact center-plus-unary star queries through light-filter groups, counted head projections and heavy group predicates. |
| inputs / outputs | A genuine non-null direct-CQ plan and chosen center produce opt-in shape metadata; initially empty serial source updates produce committed epochs and exact distinct snapshot cursors. |
| invariants | Distinct center variables and physical tables, unique unary satellite coordinates and a satellite for every hidden coordinate. Center degrees determine exact generalized H. Each light-eligible fact has one group; group liveness depends only on heavy satellite predicates. Head order/repetitions survive; j counts distinct head variables. |
| ownership | One original source-runtime account funds imported comparison metadata, coordinate/fact/group indices, detached inverse records, histogram tokens, cursor scratch and owning output. Compiler admission DTOs and explicit source exports have separate caller ownership. |
| failure | One private inverse journal plus the existing source token unwind failed input maintenance. Fund records before mutation; valid publication is allocation-free. Iterator invalidation is handled by stable inserted keys and fresh reverse lookups. Cursor failure closes its lease and preserves committed state. |
| cost | Heavy satellite updates visit reverse groups; light satellite updates visit only their center bucket. Exact H threshold spans and affected-key-only resets avoid whole-source star rebuilds. Candidate pacing uses product_hidden(1+heavy_keys), capped by center rows. Ordered traversal/comparisons, scalar widths, source constraints, allocation, startup and cleanup remain additional costs; no full P2 or wall-clock bound is claimed. |
| Design | [docs/star.md](../star.md), [docs/query_memory.md](../query_memory.md), [docs/code_review.md](../code_review.md) |

## weighted

| Field | Contract |
| --- | --- |
| purpose | Maintain exact full-subtree messages and local visible factors, then enumerate projected core tuples with multiplicities. |
| inputs / outputs | A checked direct-CQ shape, separate weighted binding and expected-value replacements produce numeric state, epochs, explicit snapshots and committed tuple/multiplicity cursors. |
| invariants | Generalized local weight is one. Missing support makes the full product and local contribution zero. Enumerated C* children are excluded from parent local factors; their weights enter once through cursor prefix products. Set identity alone does not authorize weighted execution; normalized SQL is rejected. |
| ownership | One admitted account owns inline scalars, one child cache per row, distinct message/factor maps, compact undo and opt-in captures. Active cursors retain the owner, borrowed table entries and one original grant; returned rows own funded payloads. |
| failure | Prepare inverses before private mutation; one stage failure aborts its whole logical epoch. Commit/rollback allocate nothing. Cursor construction publishes a reader only after startup succeeds; failed next closes its reader and propagates the original failure without changing committed state. |
| cost | Charge actual events, affected rows, precompiled outside-slot scans, numerical products, projections and native work. Inside positive child changes reuse cached local contributions. Cursors use O(C*) frames/prefixes and emit compressed records without result history or hidden witness materialization; explicit captures copy arrays. No Boolean numeric bound or constant public delay is claimed. |
| Design | [docs/weighted_messages.md](../weighted_messages.md), [docs/weighted_enumeration.md](../weighted_enumeration.md), [docs/annotations.md](../annotations.md), [docs/code_review.md](../code_review.md) |

## api

| Field | Contract |
| --- | --- |
| purpose | Present an owning code/message exception at public compiler, tool and runtime presentation boundaries. |
| inputs / outputs | Error receives owning code/message strings; code() borrows the stored code and what() comes from std::runtime_error. |
| invariants | A code identifies the diagnostic category; no query validity, compiled-program identity or runtime rollback guarantee is established by this type. |
| ownership | Error owns its strings. References from code() remain valid only while that exception object remains alive and unchanged. |
| failure | Constructing formatted Error may allocate; native exhausted-account primitives use fixed diagnostic types and translate at the documented boundary. |
| cost | Exception construction copies/moves owning strings and invokes standard exception storage; reading code() is a borrowed reference. Do not use formatted Error as a routine hot-path status conversion. |
| Design | [docs/query_memory.md](../query_memory.md), [docs/code_review.md](../code_review.md) |

## memory

| Field | Contract |
| --- | --- |
| purpose | Fund native owners and nested storage from one finite requested-byte account. |
| inputs / outputs | A MemoryAccount, byte count/alignment, purpose and immutable attribution produce a funded block or allocator-backed owner. Counts describe actual upstream requests; they are not RSS. |
| invariants | Retained state, scratch, undo and output keep the receiving account. Lifetime reclassification does not free bytes or refill a limit. Nonpropagating maintained allocators cannot adopt a foreign account. |
| ownership | Account copies retain the controller. MemoryBlock owns one allocation; MemoryAllocator funds container storage but does not inject itself into nested members. OwnerAllocator moves returned storage together with its original account. |
| failure | Reject capacity/size/history overflow before publication. Resource failures carry fixed diagnostics; standard exception-runtime storage is outside operator-new accounting. Destroy/deallocate/rollback paths cannot depend on another allocation. Accounts require one mutating thread and external synchronization for shared access. |
| cost | Ordinary block admission/release and exact-allocation reclassification perform fixed ledger/counter work plus upstream allocation. statistics_for, copy_attributions and set_lifetime_containing scan outstanding allocations; call them as explicit diagnostics or documented reference costs. |
| Design | [docs/query_memory.md](../query_memory.md), [docs/memory_accounts.md](../memory_accounts.md), [docs/memory_reports.md](../memory_reports.md) |

## values

| Field | Contract |
| --- | --- |
| purpose | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| inputs / outputs | Typed fields and positional layout/projection descriptors produce validated tuples or borrowed scalar/row views. Preserve exact integer/decimal/date/timestamp/string values and field order. |
| invariants | Layout identity, scalar type/scale and field positions must agree. Equality/hashing/order use exact values; a nonzero numerical annotation is not a membership predicate. |
| ownership | Views borrow their source and must not outlive it. Accounted tuples/rows retain native funded payloads; public export creates explicit owning DTO values. Shared layout identity does not imply shared mutable tables. |
| failure | Validation precedes retaining a malformed tuple. Native validation uses typed fixed failures where implemented; public presentation may allocate a message. Declared noexcept access requires valid positions and owners. |
| cost | Projection/copy touches selected fields and deep payload bytes. Hash/order may inspect complete values. Native/public conversion can allocate; borrowed comparison/probe paths do not require an owning Row. |
| Design | [docs/scalars.md](../scalars.md), [docs/storage.md](../storage.md), [docs/tuple_arenas.md](../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../verification/s05-public-tuples-2026-11-09.md) |

## arena

| Field | Contract |
| --- | --- |
| purpose | Keep stable tuple handles and retained deleted payloads for live readers and inverse operations. |
| inputs / outputs | A typed tuple produces an owner/slot/generation handle; get/pin validates that identity and returns a borrowed row or retaining pin. |
| invariants | Foreign owners and stale generations are rejected. Erasing membership does not recycle a pinned payload. Slot generation cannot silently wrap into a previously valid handle. |
| ownership | The arena state owns slots and values. A pin retains state and its generation until reset/destruction; moved-from handles have no ownership. Accounted arenas fund state, directory, slots and payloads from the layout account. |
| failure | Allocate/import before exposing a new handle. Owner-only revive is a prepaid inverse operation. Destruction and pin release do not allocate; invalid internal lifetime states are contract failures. |
| cost | Handle lookup addresses a slot and checks identity; insertion may grow the directory and allocate a slot/deep row. Whole-arena diagnostics scan allocated/high-water state, not merely live rows. |
| Design | [docs/tuple_arenas.md](../tuple_arenas.md), [docs/storage_journal.md](../storage_journal.md), [docs/query_memory.md](../query_memory.md) |

## storage

| Field | Contract |
| --- | --- |
| purpose | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| inputs / outputs | A relation/layout and backend options create a table. Insert/erase/find operate on complete typed tuples or handles; secondary probes use compiled projection keys; cursors expose current live members. |
| invariants | Primary rows, ID lookup, arena liveness and every secondary membership agree. A prepared journal may retain deleted nodes, but private empty keys and stale history are not public live membership. |
| ownership | Tables own arena and index nodes; directory/list hooks borrow those nodes. Cursors borrow rows under the documented mutation lease. Journals own inverses/pins until commit/rollback/destruction. Accounted facades retain the layout account and supplied finite work grant. |
| failure | Reserve node/growth/undo capacity before mutation. Roll back in reverse order using retained nodes and saved neighbors. Prepaid publication/undo is nonallocating; its terminate checks protect internal invariants and are not user-input validation. |
| cost | Reference maps use ordered lookups and may allocate per node. Indexed lookup assumes distributed hashes, with exact collision checks and linear collision worst cases. Rehash/growth, payload hashing, cursor startup and retained undo are charged separately. A live-link step does not scan hash capacity. |
| Design | [docs/indexed_storage.md](../indexed_storage.md), [docs/storage_journal.md](../storage_journal.md), [docs/storage.md](../storage.md), [docs/query_memory.md](../query_memory.md) |

## ir

| Field | Contract |
| --- | --- |
| purpose | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| inputs / outputs | Catalog/query/tree/physical descriptors produce value objects or an admitted CompiledProgram. Numeric IDs index their declared owner; output mapping is distinct from the core free-variable set. |
| invariants | Atom occurrences preserve aliases even when scopes repeat. Checked tree validity and minimum-height evidence are separate. Immutable program bindings retain exact source/plan/backend identity. |
| ownership | Compiler DTOs own ordinary values before query admission. CompiledProgram imports executable metadata and native bindings into the receiving account; returned spans borrow that retained program. |
| failure | Reject malformed identity, layouts, tree proof or backend options at construction/admission. Import failure leaves no partially published executable program. |
| cost | Construction, deep copy, canonical identity and native import visit metadata/fields and may allocate. Immutable views/ID access borrow established state; they do not re-run the planner. |
| Design | [docs/semantics.md](../semantics.md), [docs/physical_plans.md](../physical_plans.md), [docs/physical_runtime.md](../physical_runtime.md), [docs/query_identity.md](../query_identity.md) |

## frontend

| Field | Contract |
| --- | --- |
| purpose | Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics. |
| inputs / outputs | SQL text, a validated catalog and explicit limits produce parser/admission/binding/normalization results. Unsupported syntax has a specific diagnostic; parser recognition alone does not admit runtime support. |
| invariants | Resolve names/aliases against the catalog; preserve atom occurrences and exact constants; retain repeated-variable/local filters and contradiction/Boolean/EXISTS semantics. Do not infer bag/weighted support from parsed syntax. |
| ownership | The parser adapter owns/freezes the foreign AST at the boundary. Compiler/binder/normalizer outputs own their values; borrowed spans/pointers remain bounded by their documented owner. |
| failure | Bound syntax/expression/recursion/work and reject unsupported/type-invalid input before producing a usable core query. Parser cleanup must release its foreign allocation on success and error. |
| cost | Parsing, binding and normalization traverse syntax/metadata, create symbols/typed values and may allocate. These are compile-time costs before native query admission; recursive work remains bounded by supplied limits. |
| Design | [docs/sql_support.md](../sql_support.md), [docs/sql_parser.md](../sql_parser.md), [docs/sql_binding.md](../sql_binding.md), [docs/sql_normalization.md](../sql_normalization.md), [docs/sql_admission.md](../sql_admission.md) |

## catalog

| Field | Contract |
| --- | --- |
| purpose | Validate schema, table/column identity and declared integrity constraints before query or data admission. |
| inputs / outputs | Catalog definitions and typed database snapshots yield checked schema/data or explicit validation errors. |
| invariants | IDs/names and column types must agree; constraints apply according to declared trust/enforcement. Source identity uses the complete physical row, including unused columns/tables. |
| ownership | Catalog DTOs own metadata; callers retain input snapshots until validation returns. Native validation uses funded compact snapshots when invoked inside runtime admission. |
| failure | Reject invalid schema/row/unique/FK conditions before publishing the proposed database. Cyclic/self FK checks require the complete proposed after-state, not arbitrary insertion prefixes. |
| cost | Full validation scans rows and constructs projected key sets when constraints require them. It is deliberately not an incremental indexed-constraint theorem. |
| Design | [docs/catalog.md](../catalog.md), [docs/schema_evolution.md](../schema_evolution.md), [docs/physical_runtime.md](../physical_runtime.md) |

## planner

| Field | Contract |
| --- | --- |
| purpose | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| inputs / outputs | Catalog/query, a proposed tree and explicit work limits produce recognition/verifier reports or physical plans. Classification alone supplies no minimum-height certificate. |
| invariants | Cover each occurrence exactly once; enforce guard/connect/connex and exact separators. Height counts native relation nodes, with generalized nodes contributing zero. Corrected P1 permits hidden root variables. |
| ownership | The planner owns immutable result descriptors. Returned program views borrow their owning artifacts; native lowering retains receiving-account metadata. |
| failure | Malformed structure and exhausted work yield explicit invalid/limited outcomes; never label an unproved candidate as a minimum-height plan. |
| cost | Structural checks/lowering traverse metadata and construct sets/layouts/index requirements. Exact search is a separate potentially exponential operation, not the cost of a validity check. |
| Design | [docs/planner_proofs.md](../planner_proofs.md), [docs/tree_plans.md](../tree_plans.md), [docs/physical_plans.md](../physical_plans.md), [docs/code_review.md](../code_review.md) |

## search

| Field | Contract |
| --- | --- |
| purpose | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| inputs / outputs | A checked CQ, explicit work/depth/time/content limits and optional continuation produce progress, valid candidates, or a terminal proof-backed minimum. |
| invariants | A valid upper witness and independently replayed lower bound are both required for optimality. Stopped/exhausted search preserves honest progress and cannot masquerade as proven minimum. |
| ownership | Continuation owners retain their exact query binding, frontier, memo and counters. Snapshots/candidates keep immutable authority; shared artifacts are not mutable search state. |
| failure | Prepare transition storage before committing a resumable unit. Allocation/content/counter stops preserve the documented continuation boundary; internal failure remains distinct from an ordinary resource stop. |
| cost | Partition/subset/tree enumeration can be exponential in query size. Explicit counters bound admitted units, keys and retained content; they do not imply constant wall-clock delay or bounded total search. |
| Design | [docs/planner_proofs.md](../planner_proofs.md), [docs/tree_oracle.md](../tree_oracle.md), [docs/planner_continuations.md](../planner_continuations.md), [docs/candidate_alternatives.md](../candidate_alternatives.md) |

## residual

| Field | Contract |
| --- | --- |
| purpose | Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner. |
| inputs / outputs | A bound CQ and residual options produce reduction traces, a checked reconstruction or an explicit limited/unsupported result. |
| invariants | Every trace edit must replay against its source. Reconstruction is checked as a CROWN tree. The inspected P2 residual-height shortcut is not unconditional optimality authority; exact repair/certification remains separate. |
| ownership | Residual machines own frontier/trace values; retained handles preserve query binding and completion status. |
| failure | Stop at an admitted transition on work/allocation limits. Invalid trace/reconstruction is distinct from resource exhaustion; no partially repaired tree becomes a certified answer. |
| cost | Reduction/replay/reconstruction walk scopes, occurrences and trace steps and may allocate. Exact repair inherits search costs; no P2 bound is claimed for every local engineering path. |
| Design | [docs/residual_candidates.md](../residual_candidates.md), [docs/planner_proofs.md](../planner_proofs.md), [docs/code_review.md](../code_review.md) |

## ranking

| Field | Contract |
| --- | --- |
| purpose | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| inputs / outputs | Candidate snapshots, compatible statistics/evidence, policy and resource constraints produce scores, selection/cache outcomes or explicit fallback/stop diagnostics. |
| invariants | Only admitted candidates and exactly matching source/backend/evidence identities can be compared or installed. Height authority remains the certificate. Unitless modeled cost and actual requested bytes stay distinct. |
| ownership | Retained scores, assessments, evidence and newly lowered programs use the originating/receiving account. Cache entries retain their allocating owner; splicing cannot grant fresh budget. |
| failure | Prepare assessment, lowering and cache publication before committing a chosen result. Resource stops/fallback reasons must be retained; corruption/binding mismatch is not a successful fallback. |
| cost | Exact arithmetic, key encoding, candidate census and native lowering are explicit costs. Selection can scan the candidate family and allocate metadata; modeled scores are neither nanoseconds nor a global physical optimum proof. |
| Design | [docs/ranking.md](../ranking.md), [docs/selection.md](../selection.md), [docs/selection_binding.md](../selection_binding.md), [docs/ranking_accounting.md](../ranking_accounting.md), [docs/selection_accounting.md](../selection_accounting.md) |

## keys

| Field | Contract |
| --- | --- |
| purpose | Compile a guarded FK/UNIQUE parent-occurrence elimination while retaining the original comparison plan and all physical constraint state. |
| inputs / outputs | A genuine non-null direct-CQ physical plan and finite cold grants produce immutable original/reduced plans, sequential original-ID premises, compact ID maps and reduced-query proof evidence. |
| invariants | Only enforced FK and target UNIQUE metadata authorize a rule. All paired key terms match exactly; non-key fields are ignored or private once-used variables. Each removal has a distinct live witness. The full source catalog survives; a reduced certificate is not an original-query minimum. |
| ownership | New wrapper/vector metadata is compiler-owned. Existing immutable plan/layout handles retain their original ownership. A runtime freezes only its selected program and full source state into its normal receiving account; no second runtime owner is added. |
| failure | Guard/search/lowering/account refusals return no partial specialization and preserve the caller's original plan. Normalized SQL, constant operators and no-match plans remain general. Existing runtime enforcement still rejects invalid referenced-table updates. |
| cost | Cold occurrence/constraint/term scans, ID compaction, exact search/replay and lowering have separate real costs. Eliminated native routes/state disappear; complete source storage and full reference constraint scans remain. No new update hook or P5 dynamic bound is claimed. |
| Design | [docs/key_specialization.md](../key_specialization.md), [Refactor.md](../../Refactor.md), [docs/catalog.md](../catalog.md), [docs/physical_runtime.md](../physical_runtime.md), [docs/planner_proofs.md](../planner_proofs.md) |

## topk

| Field | Contract |
| --- | --- |
| purpose | Select an exact ranked prefix of a genuine SQL row or aggregate snapshot by ordinary recomputation and sorting. |
| inputs / outputs | A quiescent SQL runtime, output-field ordering, k and finite grants produce an owning compressed ranked snapshot with program, sequence and phase metrics. |
| invariants | NULL placement is independent of direction. Ties use full output-tuple identity for rows or complete group-key identity for aggregates. Ranking uses rendered SQL values; multiplicities never expand and selected totals never exceed k. |
| ownership | Candidate, tuple and compact result storage use the original receiving account. Immutable Tuple/program handles survive owner teardown; the scan lease closes before sorting. Ordinary diagnostics remain outside that account. |
| failure | Invalid order, busy owners, work/candidate excess and original producer/account failures propagate before a result escapes. Private RAII cleanup preserves committed rows and sequence without another undo or catch framework. |
| cost | Full collection and ordinary comparison sorting use O(N) candidate space and field/string-dependent comparisons. Producer and top-k grants are separate; retained entry capacity is O(M) selected identities. No update hook, specialized P10 bound or SQL ORDER BY admission is added. |
| Design | [docs/topk.md](../topk.md), [Refactor.md](../../Refactor.md), [docs/sql_rows_runtime.md](../sql_rows_runtime.md), [docs/aggregates.md](../aggregates.md) |

## support

| Field | Contract |
| --- | --- |
| purpose | Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations. |
| inputs / outputs | A compiled program and exact native set-membership updates produce committed support state, local membership transitions, or current/epoch cursors. |
| invariants | Child flags count child-key presence. Native S contains rows supported by every child. Generalized candidates are the child-key union and survivors its intersection. P/E counts count projected S witnesses; only zero crossings change membership. |
| ownership | Pending epochs own metadata inverses, per-table journals and retained pins. Committed/current cursor leases keep factor state alive and block writers. Views borrow rows under their lease; captured reports/output own funded values. |
| failure | Prepare/undo must preserve the previous committed sequence on any throwing step. Commit, rollback and final release cannot allocate. Public busy/owner/sequence validation remains distinct from internal prepaid invariant checks. |
| cost | Work includes reverse-bucket visits, fan-out flags, projected-key hashing/copies, journals and chosen enumeration policy. Reference ordered maps and diagnostics can add nonconstant costs; local theory provenance is not a measured/public API delay bound. |
| Design | [docs/support_invariants.md](../support_invariants.md), [docs/runtime_support.md](../runtime_support.md), [docs/prepared_epochs.md](../prepared_epochs.md), [docs/result_cursors.md](../result_cursors.md), [docs/epoch_views.md](../epoch_views.md), [docs/code_review.md](../code_review.md) |

## physical

| Field | Contract |
| --- | --- |
| purpose | Compose one full physical source update across all its aliases into one atomic logical support epoch. |
| inputs / outputs | Sequence, table, insert/erase and complete typed source row produce a private PendingUpdate and then one committed physical result, including exact no-op sequence advancement. |
| invariants | Source identity uses complete rows. Each occurrence has an independent exact derivation count for its accepted projection. Only zero crossings change logical membership; later aliases see earlier private prefixes, including self-join new-new terms. |
| ownership | The pending owner retains source journal, derivation inverses, logical pending epoch and imported tuples. Input views are borrowed only during admission. All native state/scratch uses the original query account and operation grant. |
| failure | Reject malformed inputs/sequence/constraints before commit; reverse logical changes, derivation metadata and source state on failure. Complete after-state constraint snapshots are validation scratch, not rollback authority. |
| cost | Routing visits aliases and copied/hashed fields. Constraint enforcement may snapshot/scan the complete source database. Ordered derivation maps and lifetime lookup can exceed the support recurrence cost; direct initialization/rebuild has separate cumulative work. |
| Design | [docs/physical_runtime.md](../physical_runtime.md), [docs/runtime_initialization.md](../runtime_initialization.md), [docs/support_invariants.md](../support_invariants.md), [docs/query_memory.md](../query_memory.md) |

## delta

| Field | Contract |
| --- | --- |
| purpose | Turn private physical/support prefixes into exact duplicate-free query answer additions/deletions with explicit producer and delivery policies. |
| inputs / outputs | A physical update and delta options create a pending epoch, private producer/spool and signed result stream. Before/after membership and SQL output mapping determine public deltas. |
| invariants | Answer membership changes differ from witness count changes. Same-sign alias prefixes telescope while private; canonical witness/factor partitions prevent duplicates. Boolean/EXISTS output follows its declared semantics. Eager spool startup is distinct from producer delay. |
| ownership | The delta owner retains live-factor indexes, before/after views, producer cursors and funded output. Epochs/leases keep required state alive; callbacks may retain a row only according to the result-owner contract. |
| failure | Finish all throwing discovery/output preparation before native publication. Failure rolls private state back; sink/callback failures preserve retryable delivery state and defer discard until callback ownership is safe. |
| cost | Live-index construction, changed-factor discovery, ordering/replay, materialization and delivery are separate charged phases. Full answers can be large. No constant public startup/delay claim follows from factorized internal enumeration. |
| Design | [docs/delta_transition_spec.md](../delta_transition_spec.md), [docs/delta_runtime.md](../delta_runtime.md), [docs/ordered_delta.md](../ordered_delta.md), [docs/delta_lifecycle.md](../delta_lifecycle.md), [docs/anchored_delta.md](../anchored_delta.md) |

## session

| Field | Contract |
| --- | --- |
| purpose | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| inputs / outputs | A compiled program plus stream/typed queue and options produce a creator-thread session; step/prepare/commit/deliver/checkpoint/recovery advance explicit input/runtime/output positions. Optional source-bound declarations are admitted once; committed status reports actual enforcement origin/through counters and first violation. |
| invariants | One mutation is active at a time. Native publication follows all required throwing preparation and durable commit decision. Uncertain durable authority latches recovery_required. Pattern guards precede journal/native preparation; fresh and trusted-restored history are explicit, with no paper CPU/delay theorem inferred. |
| ownership | The session owns stream/queue, window controller, runtime, pending tokens and durable lock/file owners. Window Prepared borrows its controller and must die before that controller. Selected-generation locks remain held across reconstruction and installation. |
| failure | Before durable authority changes, unwind private preparation to the prior epoch. After uncertain publication/decision, retain authority and require recovery. Preallocate final receiving owners before any durable tail repair; install using nonthrowing moves. |
| cost | Ingestion, expiration, native maintenance, output and durability have separate costs. Optional plain erase checks use O(log R) borrowed rule lookup; scoped windows have explicit live-count/scratch costs. Status copies fixed data and a declaration handle. Checkpoint/recovery may traverse full state; no constant CPU update bound is asserted. |
| Design | [docs/session_lifecycle.md](../session_lifecycle.md), [docs/session-journal.md](../session-journal.md), [docs/generations.md](../generations.md), [docs/local-sink.md](../local-sink.md), [docs/reoptimization.md](../reoptimization.md), [docs/native-replay.md](../native-replay.md), [docs/update_patterns.md](../update_patterns.md) |

## window

| Field | Contract |
| --- | --- |
| purpose | Translate typed batch/window controls into ordered physical membership changes while retaining exact source positions and expiration state. |
| inputs / outputs | Timestamped inserts, withdrawals, watermarks and explicit FIFO/window policy yield prepared physical changes and committed controller state. |
| invariants | Operational ordering/sequence and duplicate identity follow the window contract. Session declarations reject final insertion-only erases and enforce explicit disjoint joint FIFO scopes over physical birth lifetimes. Whole watermarks preflight before any effect; metadata-only reference removal preserves a live birth. Local enforcement does not imply a paper maintenance theorem. |
| ownership | Prepared tokens borrow their WindowController; destroy/close them before the controller or stop. Window buffers and retained rows use the session/query account. |
| failure | Preparation may allocate/validate but cannot publish controller progress until the associated native update succeeds. Abort returns pending expiration/input state to its prior boundary. |
| cost | Expiration can touch many events. Declared whole-watermark checks use O(D) funded integer scratch with charged rule/search work; sorting is needed only for grouped FIFO order outside global physical order. Explicit scoped withdrawal can scan D existing counts. No extra retained row graph is added; work limits and memory caps bound distinct resources. |
| Design | [docs/batches_windows.md](../batches_windows.md), [docs/session_lifecycle.md](../session_lifecycle.md), [docs/query_memory.md](../query_memory.md), [docs/update_patterns.md](../update_patterns.md) |

## statistics

| Field | Contract |
| --- | --- |
| purpose | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| inputs / outputs | A committed owner stamp, scope/projection and limits produce a retained report with availability/completion/freshness and explicit work/bytes/counters. |
| invariants | Unknown/partial differs from zero. Preserve earlier exact components when a later scope exhausts its grant. No-op committed inputs advance relevant sampling/observation sequence. Reports do not create a fresh runtime operation allowance. |
| ownership | Retained native reports/evidence use the existing account and survive owner changes as stamped snapshots. JSON/text export is an explicit presentation boundary with separate temporary ownership. |
| failure | Only documented exhaustion becomes incomplete/unknown distribution. Foreign handles, corruption and allocation failure must retain their distinct boundary. Observation off/counters modes do not evaluate timing clocks. |
| cost | Census, projection, histograms, owner-ledger scans and exports are explicit work; diagnostics are not maintenance or cursor primitives. Account statistics measure requests rather than process RSS. |
| Design | [docs/statistics.md](../statistics.md), [docs/observability.md](../observability.md), [docs/memory_reports.md](../memory_reports.md), [docs/ranking_evaluation.md](../ranking_evaluation.md) |

## recovery

| Field | Contract |
| --- | --- |
| purpose | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| inputs / outputs | Versioned records/paths/options and expected identity yield checked images, valid-prefix readers, locked durable owners or replay inputs. |
| invariants | Validate lengths, versions, identity, sequence and checksums before admission. Truncated tails differ from corrupt committed history. Undeclared Session images preserve state version 1; declared version 2 carries source/rules/origin/violation metadata. Restored pattern history assumes a trusted checkpoint; checksums do not authenticate prior enforcement. |
| ownership | File objects own descriptors/locks; temporary paths belong to the creating publication attempt. Receiving native state uses its original finite account; retain locks through whole reconstruction and admission. |
| failure | Partial/uncertain writes can require recovery. Do not remove locks, poison states, fsync/order checks or tail-repair admission because another layer also handles errors. Failure cleanup does not pretend an uncertain durable decision was undone. |
| cost | Codec work scales with bytes; checksums/canonicalization scan payloads. Pattern inspection allocates no rule storage; decode funds rule scratch and retained import from the receiving account under separate grants. Durable I/O blocks; process-crash tests do not establish every hardware power-loss behavior. |
| Design | [docs/checkpoints.md](../checkpoints.md), [docs/journal.md](../journal.md), [docs/journal-files.md](../journal-files.md), [docs/generations.md](../generations.md), [docs/local-sink.md](../local-sink.md), [docs/history-retirement.md](../history-retirement.md), [docs/update_patterns.md](../update_patterns.md) |

## io

| Field | Contract |
| --- | --- |
| purpose | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| inputs / outputs | Versioned JSON/binary/text, input options, limits and expected metadata produce typed DTO/native records or canonical reports. |
| invariants | Validate syntax, schema version, exact IDs/types/byte lengths and supported options. A transport format does not change source identity or query semantics; unknown enum values are not silently accepted. |
| ownership | Caller streams remain caller/component resources unless transferred to a session. Native EventReader/queue decode retains funded compact fields. Exported JSON/text/DTO copies are explicit presentation objects. |
| failure | Reject malformed/over-limit input before publishing typed state or consuming a committed sequence. Translate internal fixed failures at a deliberate external presentation boundary, not repeatedly inside the hot primitive. |
| cost | Parsing/encoding/canonical binding touches bytes/fields and may allocate. Byte/output limits constrain their declared encoding domain, not every temporary parser allocation. |
| Design | [docs/ingestion.md](../ingestion.md), [docs/query_identity.md](../query_identity.md), [docs/schema_evolution.md](../schema_evolution.md), [docs/cli.md](../cli.md), [docs/query_memory.md](../query_memory.md) |

## annotations

| Field | Contract |
| --- | --- |
| purpose | Define exact bounded annotation domains and explicit arithmetic/support semantics for W01. |
| inputs / outputs | Admitted bag/count/sum/average policy and typed values produce exact bounded arithmetic results or a fixed domain/overflow failure. |
| invariants | Group presence follows support, not SUM value; cancellation cannot erase a live group. NULL/scale/type/domain policy is explicit. W01 arithmetic alone does not implement weighted runtime or SQL aggregation. |
| ownership | Policies and scalar arithmetic use their declared value representation. Returned values own their digits/payload as specified; runtime row ownership remains a separate W02 concern. |
| failure | Validate supported policy/type, count bounds and arithmetic overflow before exposing a result. Do not silently approximate or use epsilon-zero tests. |
| cost | Fixed-width domain operations are bounded by that domain; textual/admission conversions inspect their input. No end-to-end weighted update bound is inherited from these primitives. |
| Design | [docs/annotations.md](../annotations.md), [docs/code_review.md](../code_review.md) |

## tools

| Field | Contract |
| --- | --- |
| purpose | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| inputs / outputs | CLI paths, manifests, executable locations and options produce generated fixtures/reports/logs or validation exit status. Run the script with --help or read its argparse/main block for invocation. |
| invariants | Keep source/input/output hashes and semantic statuses honest. An artifact generator is not itself independent evidence that engine answers are correct. Fresh-source/build evidence applies only to its captured inputs. |
| ownership | The script owns newly created temporary/output paths and subprocess handles. Preserve original/pinned evidence. JSON fixtures and data are input/output artifacts, not maintained native state. |
| failure | Argument/validation/subprocess errors cause an explicit failing command. Cleanup may use finally/context-manager ownership; ignoring a cleanup failure cannot imply successful validation. |
| cost | Python allocation, process launch, full-file hashing/JSON and benchmark execution are offline costs. They do not enter the native query complexity contract. |
| Design | [docs/native_build.md](../native_build.md), [docs/measurement.md](../measurement.md), [docs/reference_fuzz.md](../reference_fuzz.md), [docs/workloads.md](../workloads.md) |

## tests

| Field | Contract |
| --- | --- |
| purpose | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| inputs / outputs | Fixture builders, input traces, candidate programs or fault cut points feed the test body; assertions and process exit/report record observed pass/failure. |
| invariants | Expected answers and oracle independence must remain explicit. Exception tests must assert state/ownership after failure and successful retry, not only that an exception exists. A finite fixture is not a universal proof. |
| ownership | Fixture-local owners, allocations, files and hooks must unwind/reset before another case. Deliberate new/delete/failure overrides belong only to the testing build. Borrowed rows obey the same owner lifetimes as production. |
| failure | Assertion/require failures or unexpected exceptions fail the test. Expected failure catches must check the advertised code/state. A skipped or not-run test is not passing evidence. |
| cost | Reference enumeration, repeated fault sweeps and full snapshots are deliberate test costs. Do not copy their whole-state operations into a production update primitive. |
| Design | [docs/code_review.md](../code_review.md), [docs/reference_fuzz.md](../reference_fuzz.md), [docs/task_ledger.md](../task_ledger.md) |

## build

| Field | Contract |
| --- | --- |
| purpose | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| inputs / outputs | CMake configuration/options and known source paths produce generated build/install/test rules; examples consume exported CROWN targets. |
| invariants | Keep reference, pure planner/ranking/selection, native runtime and report dependencies separated. Verify pinned dependency bytes; exported targets must carry their actual required interfaces. |
| ownership | CMake owns its binary directory/generated rules; dependency/source bytes and installed artifacts have separate destinations. Do not write generated state into preserved baseline sources. |
| failure | Configuration rejects unsupported prerequisites/hash mismatches. Build/test failure remains visible to the caller; target existence does not certify its correctness. |
| cost | Configuration, compilation, linking and installation are offline work. Comments/spec generation introduce no native runtime instrumentation. |
| Design | [docs/native_build.md](../native_build.md), [docs/source_baselines.md](../source_baselines.md) |

## examples

| Field | Contract |
| --- | --- |
| purpose | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| inputs / outputs | Example CLI inputs and local fixture/program construction produce results, measurements, ranking exports or reoptimization decisions. |
| invariants | Respect admitted query semantics, explicit sequence/lifecycle and account ownership; demonstration output is not automatically a release or performance claim. |
| ownership | Example main owns its engine/session, input/output streams and artifacts. Borrowed views remain within those owners; installed examples should depend on public exported interfaces. |
| failure | Expose argument, engine and I/O failures as command failure. Example-level diagnostics may format errors at the process boundary. |
| cost | Setup, planning, file I/O, captures and measurement overhead are distinct from timed maintenance. Inspect the exact measured interval before comparing results. |
| Design | [docs/cli.md](../cli.md), [docs/native_build.md](../native_build.md), [docs/measurement.md](../measurement.md), [docs/ranking_evaluation.md](../ranking_evaluation.md), [docs/reoptimization.md](../reoptimization.md) |
