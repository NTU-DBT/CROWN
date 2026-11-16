"""Reviewed subsystem and primitive contracts used by generate_code_specs.py.

These are usage contracts, not proof claims. Narrow block facts augment them.
"""

CONTRACTS = {
    'difference': {
        'purpose': 'Admit explicit set EXCEPT or bag EXCEPT ALL between two positive classical CQs and maintain exact compressed residual counts.',
        'inputs_outputs': 'Two non-null public-IR operands over one full catalog produce one independent source owner, owning tuple/multiplicity snapshots and exact nonnegative endpoint replacements.',
        'invariants': 'Set mode keeps left presence and right absence; bag mode counts complete physical-row assignments before projection and keeps max(left-right,0). Physical inputs stay sets. Positional output types match without coercing right Decimal keys into the left result layout. Positive operands cannot encode recursive negation cycles.',
        'ownership': 'One original query account funds both frozen native operands, one deep source image, private consolidated counts, retained compressed answers and owning output. Cold pair admission copies/lowers both operands separately; compiler DTOs and explicit diagnostic exports keep caller ownership.',
        'failure': 'One cumulative wrapper grant spans metadata or capture/both operand evaluations/residual and endpoint work. Prepare every fallible result before the existing physical source commit and nonthrowing answer swap. Native RAII/token rollback preserves prior state on work, count, row or allocation refusal.',
        'cost': 'Full physical source capture, nested-loop prefixes and witnesses, scalar widths, ordered key consolidation, compressed materialization, endpoint merging and cleanup are real costs. Per-operand distinct caps and W01 checked uint64 multiplicities are separate. Advisory row/multiplicity bounds are not peak bytes or speed claims; no P11 or constant-delay CROWN bound is implied.',
        'references': ['docs/difference.md', 'docs/source_images.md', 'docs/annotations.md', 'Refactor.md'],
    },
    'cq_recompute': {
        'purpose': 'Share funded positive-CQ metadata freezing and iterative complete-witness traversal between conservative recomputation owners.',
        'inputs_outputs': 'A validated original query and native source schema freeze account-backed spans; a funded physical image and caller callback visit complete ordered-head assignments.',
        'invariants': 'Original positive terms, aliases, constants, ignored fields and repeated variables survive. A binding trail restores ancestor assignments. The caller selects Boolean early termination versus full bag-witness traversal and performs projection consolidation; this primitive supplies no DISTINCT or difference semantics by itself.',
        'ownership': 'Native metadata and iterative frames/bindings/projected views use the supplied original account. Callback views borrow private scratch and must not escape; the caller retains owning values explicitly.',
        'failure': 'The caller supplies one cumulative budget and private callback. Exceptions unwind private scratch before publication; the helper adds no source owner, transaction journal, catch/retry loop or executable authority.',
        'cost': 'Frozen metadata/bytes, iterative row/term/scalar work and each complete projection are charged through the caller. Templates add no virtual dispatch or allocated callback. Prefix/witness count, payload width, caller consolidation and cleanup remain explicit real costs.',
        'references': ['docs/fallback.md', 'docs/difference.md', 'docs/query_memory.md', 'Refactor.md'],
    },
    'fallback': {
        'purpose': 'Admit an explicit general classical CQ and maintain exact projected set answers through conservative full recomputation.',
        'inputs_outputs': 'Non-null exact-set public query IR and its full original catalog produce an immutable classified plan, independent owner, owning snapshots and exact endpoint deltas.',
        'invariants': 'Keep the actual cyclic, acyclic non-free-connex or free-connex classification and explicit fallback reason. The source-only lowering validates original physical sources; it is not a CROWN or GHD certificate for the original query. Complete assignments precede ordered/repeated head projection and DISTINCT; aliases, constants, ignored terms, Boolean and contradictory bodies keep classical meanings.',
        'ownership': 'One original query account funds frozen native metadata, iterative binding/trail scratch, deep source images, private distinct candidates, retained native answers and owning outputs. Cold admission DTOs and explicit diagnostic source exports have separate caller ownership.',
        'failure': 'Prepare the complete private result and endpoint differences before source commit. Existing source-token rollback and native RAII preserve the prior epoch on refusal; one busy guard spans source/result publication and old-state retirement. Pending captures reuse the original indexed lease without refilling it.',
        'cost': 'One cumulative recomputation grant charges source capture, row/term/scalar work, full assignment evaluation, ordered deduplication, materialization and endpoint merging. Estimates are advisory row bounds with explicit overflow, not peak-byte bounds. Constructor import, allocation, owning snapshots and cleanup remain real costs; no constant-delay CROWN, GHD algorithm, shared-query or parallel bound is claimed.',
        'references': ['docs/fallback.md', 'docs/source_images.md', 'docs/query_memory.md', 'Refactor.md'],
    },
    'comparisons': {
        'purpose': 'Admit an explicit typed comparison conjunction and maintain exact projected set answers over ordinary CQ propagation.',
        'inputs_outputs': 'A genuine non-null direct-CQ plan plus six variable/constant comparison operators produces an opt-in owner, owning snapshots and exact endpoint added/removed sets.',
        'invariants': 'Comparisons remain outside the equality query. Evaluate complete assignments, including hidden operands, before original ordered/repeated head projection and DISTINCT. All source aliases drain before answer recomputation. Empty conjunction and Boolean/constant/contradictory plans retain their exact meanings.',
        'ownership': 'One original query account funds frozen comparison literals, metadata, private deduplication, retained native tuples and owning output. Compiler predicate DTOs and explicit source exports retain their external ownership boundary.',
        'failure': 'Prepare comparison outputs and endpoint differences before source commit; private RAII work and the existing source token unwind refusal. One busy guard covers source/result publication and old-state retirement. No second journal or source clone is added.',
        'cost': 'Ordinary source/equality maintenance plus full-assignment enumeration, predicate/field/byte work, ordered deduplication, output materialization and endpoint merging are explicit. Constructor import and initial results share one wrapper grant; each cursor uses one cumulative producer grant. Cleanup and retained snapshots remain separate real costs; no specialized P9 or dynamic comparison bound is claimed.',
        'references': ['docs/comparisons.md', 'docs/query_memory.md', 'docs/code_review.md'],
    },
    'star': {
        'purpose': 'Admit and maintain exact center-plus-unary star queries through light-filter groups, counted head projections and heavy group predicates.',
        'inputs_outputs': 'A genuine non-null direct-CQ plan and chosen center produce opt-in shape metadata; initially empty serial source updates produce committed epochs and exact distinct snapshot cursors.',
        'invariants': 'Distinct center variables and physical tables, unique unary satellite coordinates and a satellite for every hidden coordinate. Center degrees determine exact generalized H. Each light-eligible fact has one group; group liveness depends only on heavy satellite predicates. Head order/repetitions survive; j counts distinct head variables.',
        'ownership': 'One original source-runtime account funds imported comparison metadata, coordinate/fact/group indices, detached inverse records, histogram tokens, cursor scratch and owning output. Compiler admission DTOs and explicit source exports have separate caller ownership.',
        'failure': 'One private inverse journal plus the existing source token unwind failed input maintenance. Fund records before mutation; valid publication is allocation-free. Iterator invalidation is handled by stable inserted keys and fresh reverse lookups. Cursor failure closes its lease and preserves committed state.',
        'cost': 'Heavy satellite updates visit reverse groups; light satellite updates visit only their center bucket. Exact H threshold spans and affected-key-only resets avoid whole-source star rebuilds. Candidate pacing uses product_hidden(1+heavy_keys), capped by center rows. Ordered traversal/comparisons, scalar widths, source constraints, allocation, startup and cleanup remain additional costs; no full P2 or wall-clock bound is claimed.',
        'references': ['docs/star.md', 'docs/query_memory.md', 'docs/code_review.md'],
    },
    'weighted': {
        'purpose': 'Maintain exact full-subtree messages and local visible factors, then enumerate projected core tuples with multiplicities.',
        'inputs_outputs': 'A checked direct-CQ shape, separate weighted binding and expected-value replacements produce numeric state, epochs, explicit snapshots and committed tuple/multiplicity cursors.',
        'invariants': 'Generalized local weight is one. Missing support makes the full product and local contribution zero. Enumerated C* children are excluded from parent local factors; their weights enter once through cursor prefix products. Set identity alone does not authorize weighted execution; normalized SQL is rejected.',
        'ownership': 'One admitted account owns inline scalars, one child cache per row, distinct message/factor maps, compact undo and opt-in captures. Active cursors retain the owner, borrowed table entries and one original grant; returned rows own funded payloads.',
        'failure': 'Prepare inverses before private mutation; one stage failure aborts its whole logical epoch. Commit/rollback allocate nothing. Cursor construction publishes a reader only after startup succeeds; failed next closes its reader and propagates the original failure without changing committed state.',
        'cost': 'Charge actual events, affected rows, precompiled outside-slot scans, numerical products, projections and native work. Inside positive child changes reuse cached local contributions. Cursors use O(C*) frames/prefixes and emit compressed records without result history or hidden witness materialization; explicit captures copy arrays. No Boolean numeric bound or constant public delay is claimed.',
        'references': ['docs/weighted_messages.md', 'docs/weighted_enumeration.md', 'docs/annotations.md', 'docs/code_review.md'],
    },
    'api': {
        'purpose': 'Present an owning code/message exception at public compiler, tool and runtime presentation boundaries.',
        'inputs_outputs': 'Error receives owning code/message strings; code() borrows the stored code and what() comes from std::runtime_error.',
        'invariants': 'A code identifies the diagnostic category; no query validity, compiled-program identity or runtime rollback guarantee is established by this type.',
        'ownership': 'Error owns its strings. References from code() remain valid only while that exception object remains alive and unchanged.',
        'failure': 'Constructing formatted Error may allocate; native exhausted-account primitives use fixed diagnostic types and translate at the documented boundary.',
        'cost': 'Exception construction copies/moves owning strings and invokes standard exception storage; reading code() is a borrowed reference. Do not use formatted Error as a routine hot-path status conversion.',
        'references': ['docs/query_memory.md', 'docs/code_review.md'],
    },
    'memory': {
        'purpose': 'Fund native owners and nested storage from one finite requested-byte account.',
        'inputs_outputs': 'A MemoryAccount, byte count/alignment, purpose and immutable attribution produce a funded block or allocator-backed owner. Counts describe actual upstream requests; they are not RSS.',
        'invariants': 'Retained state, scratch, undo and output keep the receiving account. Lifetime reclassification does not free bytes or refill a limit. Nonpropagating maintained allocators cannot adopt a foreign account.',
        'ownership': 'Account copies retain the controller. MemoryBlock owns one allocation; MemoryAllocator funds container storage but does not inject itself into nested members. OwnerAllocator moves returned storage together with its original account.',
        'failure': 'Reject capacity/size/history overflow before publication. Resource failures carry fixed diagnostics; standard exception-runtime storage is outside operator-new accounting. Destroy/deallocate/rollback paths cannot depend on another allocation. Accounts require one mutating thread and external synchronization for shared access.',
        'cost': 'Ordinary block admission/release and exact-allocation reclassification perform fixed ledger/counter work plus upstream allocation. statistics_for, copy_attributions and set_lifetime_containing scan outstanding allocations; call them as explicit diagnostics or documented reference costs.',
        'references': ['docs/query_memory.md', 'docs/memory_accounts.md', 'docs/memory_reports.md'],
    },
    'values': {
        'purpose': 'Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.',
        'inputs_outputs': 'Typed fields and positional layout/projection descriptors produce validated tuples or borrowed scalar/row views. Preserve exact integer/decimal/date/timestamp/string values and field order.',
        'invariants': 'Layout identity, scalar type/scale and field positions must agree. Equality/hashing/order use exact values; a nonzero numerical annotation is not a membership predicate.',
        'ownership': 'Views borrow their source and must not outlive it. Accounted tuples/rows retain native funded payloads; public export creates explicit owning DTO values. Shared layout identity does not imply shared mutable tables.',
        'failure': 'Validation precedes retaining a malformed tuple. Native validation uses typed fixed failures where implemented; public presentation may allocate a message. Declared noexcept access requires valid positions and owners.',
        'cost': 'Projection/copy touches selected fields and deep payload bytes. Hash/order may inspect complete values. Native/public conversion can allocate; borrowed comparison/probe paths do not require an owning Row.',
        'references': ['docs/scalars.md', 'docs/storage.md', 'docs/tuple_arenas.md', 'docs/verification/s05-public-tuples-2026-11-09.md'],
    },
    'arena': {
        'purpose': 'Keep stable tuple handles and retained deleted payloads for live readers and inverse operations.',
        'inputs_outputs': 'A typed tuple produces an owner/slot/generation handle; get/pin validates that identity and returns a borrowed row or retaining pin.',
        'invariants': 'Foreign owners and stale generations are rejected. Erasing membership does not recycle a pinned payload. Slot generation cannot silently wrap into a previously valid handle.',
        'ownership': 'The arena state owns slots and values. A pin retains state and its generation until reset/destruction; moved-from handles have no ownership. Accounted arenas fund state, directory, slots and payloads from the layout account.',
        'failure': 'Allocate/import before exposing a new handle. Owner-only revive is a prepaid inverse operation. Destruction and pin release do not allocate; invalid internal lifetime states are contract failures.',
        'cost': 'Handle lookup addresses a slot and checks identity; insertion may grow the directory and allocate a slot/deep row. Whole-arena diagnostics scan allocated/high-water state, not merely live rows.',
        'references': ['docs/tuple_arenas.md', 'docs/storage_journal.md', 'docs/query_memory.md'],
    },
    'storage': {
        'purpose': 'Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.',
        'inputs_outputs': 'A relation/layout and backend options create a table. Insert/erase/find operate on complete typed tuples or handles; secondary probes use compiled projection keys; cursors expose current live members.',
        'invariants': 'Primary rows, ID lookup, arena liveness and every secondary membership agree. A prepared journal may retain deleted nodes, but private empty keys and stale history are not public live membership.',
        'ownership': 'Tables own arena and index nodes; directory/list hooks borrow those nodes. Cursors borrow rows under the documented mutation lease. Journals own inverses/pins until commit/rollback/destruction. Accounted facades retain the layout account and supplied finite work grant.',
        'failure': 'Reserve node/growth/undo capacity before mutation. Roll back in reverse order using retained nodes and saved neighbors. Prepaid publication/undo is nonallocating; its terminate checks protect internal invariants and are not user-input validation.',
        'cost': 'Reference maps use ordered lookups and may allocate per node. Indexed lookup assumes distributed hashes, with exact collision checks and linear collision worst cases. Rehash/growth, payload hashing, cursor startup and retained undo are charged separately. A live-link step does not scan hash capacity.',
        'references': ['docs/indexed_storage.md', 'docs/storage_journal.md', 'docs/storage.md', 'docs/query_memory.md'],
    },
    'ir': {
        'purpose': 'Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.',
        'inputs_outputs': 'Catalog/query/tree/physical descriptors produce value objects or an admitted CompiledProgram. Numeric IDs index their declared owner; output mapping is distinct from the core free-variable set.',
        'invariants': 'Atom occurrences preserve aliases even when scopes repeat. Checked tree validity and minimum-height evidence are separate. Immutable program bindings retain exact source/plan/backend identity.',
        'ownership': 'Compiler DTOs own ordinary values before query admission. CompiledProgram imports executable metadata and native bindings into the receiving account; returned spans borrow that retained program.',
        'failure': 'Reject malformed identity, layouts, tree proof or backend options at construction/admission. Import failure leaves no partially published executable program.',
        'cost': 'Construction, deep copy, canonical identity and native import visit metadata/fields and may allocate. Immutable views/ID access borrow established state; they do not re-run the planner.',
        'references': ['docs/semantics.md', 'docs/physical_plans.md', 'docs/physical_runtime.md', 'docs/query_identity.md'],
    },
    'frontend': {
        'purpose': 'Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics.',
        'inputs_outputs': 'SQL text, a validated catalog and explicit limits produce parser/admission/binding/normalization results. Unsupported syntax has a specific diagnostic; parser recognition alone does not admit runtime support.',
        'invariants': 'Resolve names/aliases against the catalog; preserve atom occurrences and exact constants; retain repeated-variable/local filters and contradiction/Boolean/EXISTS semantics. Do not infer bag/weighted support from parsed syntax.',
        'ownership': 'The parser adapter owns/freezes the foreign AST at the boundary. Compiler/binder/normalizer outputs own their values; borrowed spans/pointers remain bounded by their documented owner.',
        'failure': 'Bound syntax/expression/recursion/work and reject unsupported/type-invalid input before producing a usable core query. Parser cleanup must release its foreign allocation on success and error.',
        'cost': 'Parsing, binding and normalization traverse syntax/metadata, create symbols/typed values and may allocate. These are compile-time costs before native query admission; recursive work remains bounded by supplied limits.',
        'references': ['docs/sql_support.md', 'docs/sql_parser.md', 'docs/sql_binding.md', 'docs/sql_normalization.md', 'docs/sql_admission.md'],
    },
    'catalog': {
        'purpose': 'Validate schema, table/column identity and declared integrity constraints before query or data admission.',
        'inputs_outputs': 'Catalog definitions and typed database snapshots yield checked schema/data or explicit validation errors.',
        'invariants': 'IDs/names and column types must agree; constraints apply according to declared trust/enforcement. Source identity uses the complete physical row, including unused columns/tables.',
        'ownership': 'Catalog DTOs own metadata; callers retain input snapshots until validation returns. Native validation uses funded compact snapshots when invoked inside runtime admission.',
        'failure': 'Reject invalid schema/row/unique/FK conditions before publishing the proposed database. Cyclic/self FK checks require the complete proposed after-state, not arbitrary insertion prefixes.',
        'cost': 'Full validation scans rows and constructs projected key sets when constraints require them. It is deliberately not an incremental indexed-constraint theorem.',
        'references': ['docs/catalog.md', 'docs/schema_evolution.md', 'docs/physical_runtime.md'],
    },
    'planner': {
        'purpose': 'Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.',
        'inputs_outputs': 'Catalog/query, a proposed tree and explicit work limits produce recognition/verifier reports or physical plans. Classification alone supplies no minimum-height certificate.',
        'invariants': 'Cover each occurrence exactly once; enforce guard/connect/connex and exact separators. Height counts native relation nodes, with generalized nodes contributing zero. Corrected P1 permits hidden root variables.',
        'ownership': 'The planner owns immutable result descriptors. Returned program views borrow their owning artifacts; native lowering retains receiving-account metadata.',
        'failure': 'Malformed structure and exhausted work yield explicit invalid/limited outcomes; never label an unproved candidate as a minimum-height plan.',
        'cost': 'Structural checks/lowering traverse metadata and construct sets/layouts/index requirements. Exact search is a separate potentially exponential operation, not the cost of a validity check.',
        'references': ['docs/planner_proofs.md', 'docs/tree_plans.md', 'docs/physical_plans.md', 'docs/code_review.md'],
    },
    'search': {
        'purpose': 'Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.',
        'inputs_outputs': 'A checked CQ, explicit work/depth/time/content limits and optional continuation produce progress, valid candidates, or a terminal proof-backed minimum.',
        'invariants': 'A valid upper witness and independently replayed lower bound are both required for optimality. Stopped/exhausted search preserves honest progress and cannot masquerade as proven minimum.',
        'ownership': 'Continuation owners retain their exact query binding, frontier, memo and counters. Snapshots/candidates keep immutable authority; shared artifacts are not mutable search state.',
        'failure': 'Prepare transition storage before committing a resumable unit. Allocation/content/counter stops preserve the documented continuation boundary; internal failure remains distinct from an ordinary resource stop.',
        'cost': 'Partition/subset/tree enumeration can be exponential in query size. Explicit counters bound admitted units, keys and retained content; they do not imply constant wall-clock delay or bounded total search.',
        'references': ['docs/planner_proofs.md', 'docs/tree_oracle.md', 'docs/planner_continuations.md', 'docs/candidate_alternatives.md'],
    },
    'residual': {
        'purpose': 'Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner.',
        'inputs_outputs': 'A bound CQ and residual options produce reduction traces, a checked reconstruction or an explicit limited/unsupported result.',
        'invariants': 'Every trace edit must replay against its source. Reconstruction is checked as a CROWN tree. The inspected P2 residual-height shortcut is not unconditional optimality authority; exact repair/certification remains separate.',
        'ownership': 'Residual machines own frontier/trace values; retained handles preserve query binding and completion status.',
        'failure': 'Stop at an admitted transition on work/allocation limits. Invalid trace/reconstruction is distinct from resource exhaustion; no partially repaired tree becomes a certified answer.',
        'cost': 'Reduction/replay/reconstruction walk scopes, occurrences and trace steps and may allocate. Exact repair inherits search costs; no P2 bound is claimed for every local engineering path.',
        'references': ['docs/residual_candidates.md', 'docs/planner_proofs.md', 'docs/code_review.md'],
    },
    'ranking': {
        'purpose': 'Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.',
        'inputs_outputs': 'Candidate snapshots, compatible statistics/evidence, policy and resource constraints produce scores, selection/cache outcomes or explicit fallback/stop diagnostics.',
        'invariants': 'Only admitted candidates and exactly matching source/backend/evidence identities can be compared or installed. Height authority remains the certificate. Unitless modeled cost and actual requested bytes stay distinct.',
        'ownership': 'Retained scores, assessments, evidence and newly lowered programs use the originating/receiving account. Cache entries retain their allocating owner; splicing cannot grant fresh budget.',
        'failure': 'Prepare assessment, lowering and cache publication before committing a chosen result. Resource stops/fallback reasons must be retained; corruption/binding mismatch is not a successful fallback.',
        'cost': 'Exact arithmetic, key encoding, candidate census and native lowering are explicit costs. Selection can scan the candidate family and allocate metadata; modeled scores are neither nanoseconds nor a global physical optimum proof.',
        'references': ['docs/ranking.md', 'docs/selection.md', 'docs/selection_binding.md', 'docs/ranking_accounting.md', 'docs/selection_accounting.md'],
    },
    'keys': {
        'purpose': 'Compile a guarded FK/UNIQUE parent-occurrence elimination while retaining the original comparison plan and all physical constraint state.',
        'inputs_outputs': 'A genuine non-null direct-CQ physical plan and finite cold grants produce immutable original/reduced plans, sequential original-ID premises, compact ID maps and reduced-query proof evidence.',
        'invariants': 'Only enforced FK and target UNIQUE metadata authorize a rule. All paired key terms match exactly; non-key fields are ignored or private once-used variables. Each removal has a distinct live witness. The full source catalog survives; a reduced certificate is not an original-query minimum.',
        'ownership': 'New wrapper/vector metadata is compiler-owned. Existing immutable plan/layout handles retain their original ownership. A runtime freezes only its selected program and full source state into its normal receiving account; no second runtime owner is added.',
        'failure': 'Guard/search/lowering/account refusals return no partial specialization and preserve the caller\'s original plan. Normalized SQL, constant operators and no-match plans remain general. Existing runtime enforcement still rejects invalid referenced-table updates.',
        'cost': 'Cold occurrence/constraint/term scans, ID compaction, exact search/replay and lowering have separate real costs. Eliminated native routes/state disappear; complete source storage and full reference constraint scans remain. No new update hook or P5 dynamic bound is claimed.',
        'references': ['docs/key_specialization.md', 'Refactor.md', 'docs/catalog.md', 'docs/physical_runtime.md', 'docs/planner_proofs.md'],
    },
    'topk': {
        'purpose': 'Select an exact ranked prefix of a genuine SQL row or aggregate snapshot by ordinary recomputation and sorting.',
        'inputs_outputs': 'A quiescent SQL runtime, output-field ordering, k and finite grants produce an owning compressed ranked snapshot with program, sequence and phase metrics.',
        'invariants': 'NULL placement is independent of direction. Ties use full output-tuple identity for rows or complete group-key identity for aggregates. Ranking uses rendered SQL values; multiplicities never expand and selected totals never exceed k.',
        'ownership': 'Candidate, tuple and compact result storage use the original receiving account. Immutable Tuple/program handles survive owner teardown; the scan lease closes before sorting. Ordinary diagnostics remain outside that account.',
        'failure': 'Invalid order, busy owners, work/candidate excess and original producer/account failures propagate before a result escapes. Private RAII cleanup preserves committed rows and sequence without another undo or catch framework.',
        'cost': 'Full collection and ordinary comparison sorting use O(N) candidate space and field/string-dependent comparisons. Producer and top-k grants are separate; retained entry capacity is O(M) selected identities. No update hook, specialized P10 bound or SQL ORDER BY admission is added.',
        'references': ['docs/topk.md', 'Refactor.md', 'docs/sql_rows_runtime.md', 'docs/aggregates.md'],
    },
    'support': {
        'purpose': 'Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations.',
        'inputs_outputs': 'A compiled program and exact native set-membership updates produce committed support state, local membership transitions, or current/epoch cursors.',
        'invariants': 'Child flags count child-key presence. Native S contains rows supported by every child. Generalized candidates are the child-key union and survivors its intersection. P/E counts count projected S witnesses; only zero crossings change membership.',
        'ownership': 'Pending epochs own metadata inverses, per-table journals and retained pins. Committed/current cursor leases keep factor state alive and block writers. Views borrow rows under their lease; captured reports/output own funded values.',
        'failure': 'Prepare/undo must preserve the previous committed sequence on any throwing step. Commit, rollback and final release cannot allocate. Public busy/owner/sequence validation remains distinct from internal prepaid invariant checks.',
        'cost': 'Work includes reverse-bucket visits, fan-out flags, projected-key hashing/copies, journals and chosen enumeration policy. Reference ordered maps and diagnostics can add nonconstant costs; local theory provenance is not a measured/public API delay bound.',
        'references': ['docs/support_invariants.md', 'docs/runtime_support.md', 'docs/prepared_epochs.md', 'docs/result_cursors.md', 'docs/epoch_views.md', 'docs/code_review.md'],
    },
    'physical': {
        'purpose': 'Compose one full physical source update across all its aliases into one atomic logical support epoch.',
        'inputs_outputs': 'Sequence, table, insert/erase and complete typed source row produce a private PendingUpdate and then one committed physical result, including exact no-op sequence advancement.',
        'invariants': 'Source identity uses complete rows. Each occurrence has an independent exact derivation count for its accepted projection. Only zero crossings change logical membership; later aliases see earlier private prefixes, including self-join new-new terms.',
        'ownership': 'The pending owner retains source journal, derivation inverses, logical pending epoch and imported tuples. Input views are borrowed only during admission. All native state/scratch uses the original query account and operation grant.',
        'failure': 'Reject malformed inputs/sequence/constraints before commit; reverse logical changes, derivation metadata and source state on failure. Complete after-state constraint snapshots are validation scratch, not rollback authority.',
        'cost': 'Routing visits aliases and copied/hashed fields. Constraint enforcement may snapshot/scan the complete source database. Ordered derivation maps and lifetime lookup can exceed the support recurrence cost; direct initialization/rebuild has separate cumulative work.',
        'references': ['docs/physical_runtime.md', 'docs/runtime_initialization.md', 'docs/support_invariants.md', 'docs/query_memory.md'],
    },
    'delta': {
        'purpose': 'Turn private physical/support prefixes into exact duplicate-free query answer additions/deletions with explicit producer and delivery policies.',
        'inputs_outputs': 'A physical update and delta options create a pending epoch, private producer/spool and signed result stream. Before/after membership and SQL output mapping determine public deltas.',
        'invariants': 'Answer membership changes differ from witness count changes. Same-sign alias prefixes telescope while private; canonical witness/factor partitions prevent duplicates. Boolean/EXISTS output follows its declared semantics. Eager spool startup is distinct from producer delay.',
        'ownership': 'The delta owner retains live-factor indexes, before/after views, producer cursors and funded output. Epochs/leases keep required state alive; callbacks may retain a row only according to the result-owner contract.',
        'failure': 'Finish all throwing discovery/output preparation before native publication. Failure rolls private state back; sink/callback failures preserve retryable delivery state and defer discard until callback ownership is safe.',
        'cost': 'Live-index construction, changed-factor discovery, ordering/replay, materialization and delivery are separate charged phases. Full answers can be large. No constant public startup/delay claim follows from factorized internal enumeration.',
        'references': ['docs/delta_transition_spec.md', 'docs/delta_runtime.md', 'docs/ordered_delta.md', 'docs/delta_lifecycle.md', 'docs/anchored_delta.md'],
    },
    'session': {
        'purpose': 'Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.',
        'inputs_outputs': 'A compiled program plus stream/typed queue and options produce a creator-thread session; step/prepare/commit/deliver/checkpoint/recovery advance explicit input/runtime/output positions. Optional source-bound declarations are admitted once; committed status reports actual enforcement origin/through counters and first violation.',
        'invariants': 'One mutation is active at a time. Native publication follows all required throwing preparation and durable commit decision. Uncertain durable authority latches recovery_required. Pattern guards precede journal/native preparation; fresh and trusted-restored history are explicit, with no paper CPU/delay theorem inferred.',
        'ownership': 'The session owns stream/queue, window controller, runtime, pending tokens and durable lock/file owners. Window Prepared borrows its controller and must die before that controller. Selected-generation locks remain held across reconstruction and installation.',
        'failure': 'Before durable authority changes, unwind private preparation to the prior epoch. After uncertain publication/decision, retain authority and require recovery. Preallocate final receiving owners before any durable tail repair; install using nonthrowing moves.',
        'cost': 'Ingestion, expiration, native maintenance, output and durability have separate costs. Optional plain erase checks use O(log R) borrowed rule lookup; scoped windows have explicit live-count/scratch costs. Status copies fixed data and a declaration handle. Checkpoint/recovery may traverse full state; no constant CPU update bound is asserted.',
        'references': ['docs/session_lifecycle.md', 'docs/session-journal.md', 'docs/generations.md', 'docs/local-sink.md', 'docs/reoptimization.md', 'docs/native-replay.md', 'docs/update_patterns.md'],
    },
    'window': {
        'purpose': 'Translate typed batch/window controls into ordered physical membership changes while retaining exact source positions and expiration state.',
        'inputs_outputs': 'Timestamped inserts, withdrawals, watermarks and explicit FIFO/window policy yield prepared physical changes and committed controller state.',
        'invariants': 'Operational ordering/sequence and duplicate identity follow the window contract. Session declarations reject final insertion-only erases and enforce explicit disjoint joint FIFO scopes over physical birth lifetimes. Whole watermarks preflight before any effect; metadata-only reference removal preserves a live birth. Local enforcement does not imply a paper maintenance theorem.',
        'ownership': 'Prepared tokens borrow their WindowController; destroy/close them before the controller or stop. Window buffers and retained rows use the session/query account.',
        'failure': 'Preparation may allocate/validate but cannot publish controller progress until the associated native update succeeds. Abort returns pending expiration/input state to its prior boundary.',
        'cost': 'Expiration can touch many events. Declared whole-watermark checks use O(D) funded integer scratch with charged rule/search work; sorting is needed only for grouped FIFO order outside global physical order. Explicit scoped withdrawal can scan D existing counts. No extra retained row graph is added; work limits and memory caps bound distinct resources.',
        'references': ['docs/batches_windows.md', 'docs/session_lifecycle.md', 'docs/query_memory.md', 'docs/update_patterns.md'],
    },
    'statistics': {
        'purpose': 'Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.',
        'inputs_outputs': 'A committed owner stamp, scope/projection and limits produce a retained report with availability/completion/freshness and explicit work/bytes/counters.',
        'invariants': 'Unknown/partial differs from zero. Preserve earlier exact components when a later scope exhausts its grant. No-op committed inputs advance relevant sampling/observation sequence. Reports do not create a fresh runtime operation allowance.',
        'ownership': 'Retained native reports/evidence use the existing account and survive owner changes as stamped snapshots. JSON/text export is an explicit presentation boundary with separate temporary ownership.',
        'failure': 'Only documented exhaustion becomes incomplete/unknown distribution. Foreign handles, corruption and allocation failure must retain their distinct boundary. Observation off/counters modes do not evaluate timing clocks.',
        'cost': 'Census, projection, histograms, owner-ledger scans and exports are explicit work; diagnostics are not maintenance or cursor primitives. Account statistics measure requests rather than process RSS.',
        'references': ['docs/statistics.md', 'docs/observability.md', 'docs/memory_reports.md', 'docs/ranking_evaluation.md'],
    },
    'recovery': {
        'purpose': 'Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.',
        'inputs_outputs': 'Versioned records/paths/options and expected identity yield checked images, valid-prefix readers, locked durable owners or replay inputs.',
        'invariants': 'Validate lengths, versions, identity, sequence and checksums before admission. Truncated tails differ from corrupt committed history. Undeclared Session images preserve state version 1; declared version 2 carries source/rules/origin/violation metadata. Restored pattern history assumes a trusted checkpoint; checksums do not authenticate prior enforcement.',
        'ownership': 'File objects own descriptors/locks; temporary paths belong to the creating publication attempt. Receiving native state uses its original finite account; retain locks through whole reconstruction and admission.',
        'failure': 'Partial/uncertain writes can require recovery. Do not remove locks, poison states, fsync/order checks or tail-repair admission because another layer also handles errors. Failure cleanup does not pretend an uncertain durable decision was undone.',
        'cost': 'Codec work scales with bytes; checksums/canonicalization scan payloads. Pattern inspection allocates no rule storage; decode funds rule scratch and retained import from the receiving account under separate grants. Durable I/O blocks; process-crash tests do not establish every hardware power-loss behavior.',
        'references': ['docs/checkpoints.md', 'docs/journal.md', 'docs/journal-files.md', 'docs/generations.md', 'docs/local-sink.md', 'docs/history-retirement.md', 'docs/update_patterns.md'],
    },
    'io': {
        'purpose': 'Admit bounded external documents/records and serialize explicit public representations at the engine boundary.',
        'inputs_outputs': 'Versioned JSON/binary/text, input options, limits and expected metadata produce typed DTO/native records or canonical reports.',
        'invariants': 'Validate syntax, schema version, exact IDs/types/byte lengths and supported options. A transport format does not change source identity or query semantics; unknown enum values are not silently accepted.',
        'ownership': 'Caller streams remain caller/component resources unless transferred to a session. Native EventReader/queue decode retains funded compact fields. Exported JSON/text/DTO copies are explicit presentation objects.',
        'failure': 'Reject malformed/over-limit input before publishing typed state or consuming a committed sequence. Translate internal fixed failures at a deliberate external presentation boundary, not repeatedly inside the hot primitive.',
        'cost': 'Parsing/encoding/canonical binding touches bytes/fields and may allocate. Byte/output limits constrain their declared encoding domain, not every temporary parser allocation.',
        'references': ['docs/ingestion.md', 'docs/query_identity.md', 'docs/schema_evolution.md', 'docs/cli.md', 'docs/query_memory.md'],
    },
    'annotations': {
        'purpose': 'Define exact bounded annotation domains and explicit arithmetic/support semantics for W01.',
        'inputs_outputs': 'Admitted bag/count/sum/average policy and typed values produce exact bounded arithmetic results or a fixed domain/overflow failure.',
        'invariants': 'Group presence follows support, not SUM value; cancellation cannot erase a live group. NULL/scale/type/domain policy is explicit. W01 arithmetic alone does not implement weighted runtime or SQL aggregation.',
        'ownership': 'Policies and scalar arithmetic use their declared value representation. Returned values own their digits/payload as specified; runtime row ownership remains a separate W02 concern.',
        'failure': 'Validate supported policy/type, count bounds and arithmetic overflow before exposing a result. Do not silently approximate or use epsilon-zero tests.',
        'cost': 'Fixed-width domain operations are bounded by that domain; textual/admission conversions inspect their input. No end-to-end weighted update bound is inherited from these primitives.',
        'references': ['docs/annotations.md', 'docs/code_review.md'],
    },
    'tools': {
        'purpose': 'Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.',
        'inputs_outputs': 'CLI paths, manifests, executable locations and options produce generated fixtures/reports/logs or validation exit status. Run the script with --help or read its argparse/main block for invocation.',
        'invariants': 'Keep source/input/output hashes and semantic statuses honest. An artifact generator is not itself independent evidence that engine answers are correct. Fresh-source/build evidence applies only to its captured inputs.',
        'ownership': 'The script owns newly created temporary/output paths and subprocess handles. Preserve original/pinned evidence. JSON fixtures and data are input/output artifacts, not maintained native state.',
        'failure': 'Argument/validation/subprocess errors cause an explicit failing command. Cleanup may use finally/context-manager ownership; ignoring a cleanup failure cannot imply successful validation.',
        'cost': 'Python allocation, process launch, full-file hashing/JSON and benchmark execution are offline costs. They do not enter the native query complexity contract.',
        'references': ['docs/native_build.md', 'docs/measurement.md', 'docs/reference_fuzz.md', 'docs/workloads.md'],
    },
    'tests': {
        'purpose': 'Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.',
        'inputs_outputs': 'Fixture builders, input traces, candidate programs or fault cut points feed the test body; assertions and process exit/report record observed pass/failure.',
        'invariants': 'Expected answers and oracle independence must remain explicit. Exception tests must assert state/ownership after failure and successful retry, not only that an exception exists. A finite fixture is not a universal proof.',
        'ownership': 'Fixture-local owners, allocations, files and hooks must unwind/reset before another case. Deliberate new/delete/failure overrides belong only to the testing build. Borrowed rows obey the same owner lifetimes as production.',
        'failure': 'Assertion/require failures or unexpected exceptions fail the test. Expected failure catches must check the advertised code/state. A skipped or not-run test is not passing evidence.',
        'cost': 'Reference enumeration, repeated fault sweeps and full snapshots are deliberate test costs. Do not copy their whole-state operations into a production update primitive.',
        'references': ['docs/code_review.md', 'docs/reference_fuzz.md', 'docs/task_ledger.md'],
    },
    'build': {
        'purpose': 'Define native target boundaries, pinned dependencies, compilation options, installation and test registration.',
        'inputs_outputs': 'CMake configuration/options and known source paths produce generated build/install/test rules; examples consume exported CROWN targets.',
        'invariants': 'Keep reference, pure planner/ranking/selection, native runtime and report dependencies separated. Verify pinned dependency bytes; exported targets must carry their actual required interfaces.',
        'ownership': 'CMake owns its binary directory/generated rules; dependency/source bytes and installed artifacts have separate destinations. Do not write generated state into preserved baseline sources.',
        'failure': 'Configuration rejects unsupported prerequisites/hash mismatches. Build/test failure remains visible to the caller; target existence does not certify its correctness.',
        'cost': 'Configuration, compilation, linking and installation are offline work. Comments/spec generation introduce no native runtime instrumentation.',
        'references': ['docs/native_build.md', 'docs/source_baselines.md'],
    },
    'examples': {
        'purpose': 'Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.',
        'inputs_outputs': 'Example CLI inputs and local fixture/program construction produce results, measurements, ranking exports or reoptimization decisions.',
        'invariants': 'Respect admitted query semantics, explicit sequence/lifecycle and account ownership; demonstration output is not automatically a release or performance claim.',
        'ownership': 'Example main owns its engine/session, input/output streams and artifacts. Borrowed views remain within those owners; installed examples should depend on public exported interfaces.',
        'failure': 'Expose argument, engine and I/O failures as command failure. Example-level diagnostics may format errors at the process boundary.',
        'cost': 'Setup, planning, file I/O, captures and measurement overhead are distinct from timed maintenance. Inspect the exact measured interval before comparing results.',
        'references': ['docs/cli.md', 'docs/native_build.md', 'docs/measurement.md', 'docs/ranking_evaluation.md', 'docs/reoptimization.md'],
    },
}

# File-stem display labels are context, not proof that every matching path has this role.
ROLES = {
    'include/crown/planner/difference.hpp': 'Declare explicit set/bag difference admission, immutable positive operands, actual structural profiles and advisory residual bounds.',
    'src/planner/difference.cpp': 'Admit both original operands over the same catalog and check ordered output types without subtracting unrelated upper bounds.',
    'include/crown/runtime/difference.hpp': 'Declare independent exact difference ownership, compressed checked counts and exact endpoint replacements distinct from aggregate payloads.',
    'src/runtime/difference.cpp': 'Recompute both positive operands from one funded source image, consolidate set/bag residuals and publish prepared endpoint counts atomically.',
    'src/runtime/cq_recompute.hpp': 'Share original-account native query freezing and iterative witness traversal with borrowed callbacks and caller-selected consolidation.',
    'include/crown/planner/fallback.hpp': 'Declare immutable explicit classical-CQ fallback admission, actual structural class, guarantee profile and advisory row estimates.',
    'src/planner/fallback.cpp': 'Bound cold metadata work, recognize the original query and lower a full-catalog source-only coordinator without claiming a CROWN or GHD certificate.',
    'include/crown/runtime/fallback.hpp': 'Declare finite independent exact fallback ownership, owning snapshots, atomic endpoint deltas and explicit materialization costs.',
    'src/runtime/fallback.cpp': 'Capture funded physical source images, enumerate complete assignments iteratively, project and deduplicate privately, then publish prepaid source/result state.',
    'include/crown/runtime/source_image.hpp': 'Declare deep accounted current or prepared physical source images with explicit row and work grants and no checkpoint authority.',
    'include/crown/planner/comparisons.hpp': 'Declare immutable opt-in exact comparison predicates and typed cold admission over genuine equality-CQ plans.',
    'src/planner/comparisons.cpp': 'Check operator/variable/type and literal-byte admission while preserving the original equality query and plan authority.',
    'include/crown/runtime/comparisons.hpp': 'Declare exact comparison binding, finite recomputation grants, owning snapshots and atomic endpoint set deltas.',
    'src/runtime/comparisons.cpp': 'Reuse ordinary propagation and full hidden-variable assignments, filter before projection, deduplicate and publish prepaid source/result state.',
    'include/crown/planner/star.hpp': 'Declare cold opt-in literal star admission and original/source-only provenance without supplying a new minimum proof.',
    'src/planner/star.cpp': 'Check center/satellite/head structure and lower a full-catalog source coordinator with no generic occurrence routes.',
    'include/crown/runtime/star.hpp': 'Declare finite star ownership, atomic maintenance, exact snapshot cursors and honest work/degree/label gauges.',
    'src/runtime/star_detail.hpp': 'Own accounted star records, sparse degree links, per-group projections and touched-record inverse journal primitives.',
    'src/runtime/star_hindex.hpp': 'Track exact generalized H using occupied degree frequencies, two suffix counts and private allocation-free publication.',
    'src/runtime/star.cpp': 'Maintain light-filtered groups, heavy predicates, exact degrees and sparse hysteretic migrations beside full original source validation.',
    'src/runtime/star_cursor.cpp': 'Pace live-group projection candidates, deduplicate borrowed keys and return original-account owning outputs under a read lease.',
    'include/crown/runtime/topk.hpp': 'Declare exact snapshot rank keys, compressed result identity, finite grants and SQL runtime overloads.',
    'src/runtime/topk.cpp': 'Collect genuine SQL outputs, sort by explicit keys and identity, and return a compact exact prefix without query-update state.',
    'include/crown/planner/keys.hpp': 'Declare immutable guarded key-specialization plans, source/reduced provenance, finite cold grants and safe borrowed metadata.',
    'src/planner/keys.cpp': 'Prove sequential enforced-FK parent elimination, compact query IDs and lower a separately certified reduced plan without changing the source constraint owner.',
    'include/crown/frontend/aggregate.hpp': 'Declare immutable aggregate input/group/measure/output descriptors and checked integer-column guards.',
    'src/frontend/aggregate.cpp': 'Bind admitted aggregate SQL into exact typed grouping, COUNT/SUM/AVG measures and immutable cast guards.',
    'include/crown/runtime/aggregate.hpp': 'Declare nullable owning aggregate tuples, grouped state, atomic prepared batches and owning output.',
    'src/runtime/aggregate.cpp': 'Maintain accounted logical input-row multiplicities and exact COUNT/SUM/AVG group proposals through one prepared aggregate batch.',
    'src/runtime/aggregate_tuple.cpp': 'Own nullable aggregate tuple cells and copied text with accounted payloads and borrowed read-only views.',
    'src/runtime/aggregate_integer.hpp': 'Provide fixed-width exact integer products, signed accumulators and decimal rounding for aggregate arithmetic.',
    'include/crown/frontend/sql_aggregate.hpp': 'Declare immutable original-SQL/source/kernel binding with physical-origin decoding; no executable plan or recovery authority.',
    'src/frontend/sql_aggregate.cpp': 'Derive admitted source/kernel SQL through genuine binders, preserving physical grouping identity and checked foreign-AST lifetimes.',
    'src/frontend/parser_detail.hpp': 'Share one internal parser/deparser mutex across cold JSON/protobuf frontend calls.',
    'tests/unit/sql_aggregate_binding_test.cpp': 'Check genuine composed admission, origin/NULL decoding, identities, static-bootstrap metadata and explicit limits.',
    'include/crown/io/memory_report.hpp': 'Declare explicit caller-owned memory-report JSON export; this header does not collect native memory.',
    'src/io/memory_report.cpp': 'Serialize a retained native memory report into ordinary JSON without rescanning live accounts/tables.',
    'include/crown/io/support.hpp': 'Declare logical-support diagnostic trace import and snapshot/epoch JSON export.',
    'src/io/support.cpp': 'Parse logical-support diagnostic Rows and serialize retained support state/journals without applying updates.',
    'tests/integration/support.py': 'Exercise support CLI diagnostics against independent manual state and transition expectations.',
    'error': 'Own a public diagnostic code/message using std::runtime_error; this header carries no planner/runtime validity guarantee.',
    'weighted': 'Execute weighted logical replacements and projected tuple/multiplicity enumeration with separate full messages, local visible factors and compact undo.',
    'digest': 'Compute and encode canonical SHA-256 digests used for artifact identity.',
    'scalar': 'Parse, compare, hash and format exact scalar DTO values.',
    'model': 'Define/validate query variables, atom occurrences, scopes and output metadata.',
    'ids': 'Give numeric IDs distinct types so owner/component domains are not interchanged accidentally.',
    'program_span': 'Expose borrowed spans into immutable native program storage.',
    'program_model': 'Define account-funded native equivalents of compiler metadata.',
    'program_native_types': 'Import/export native compiler metadata using the receiving account.',
    'program_replan': 'Rebind and lower checked candidates into native metadata without retaining an ordinary DTO graph.',
    'parser': 'Own the libpg_query parse result and expose the admitted parser representation.',
    'bind': 'Resolve table/column aliases, expressions and exact typed literals against catalog metadata.',
    'normalize': 'Normalize bound equality predicates, contradictions and SQL output semantics into a typed CQ.',
    'adapter': 'Apply occurrence-local constants/repeated-variable tests and positional projection.',
    'recognize': 'Run GYO reduction for body and augmented-head hypergraphs; distinguish free-connex, acyclic non-free-connex and cyclic cases.',
    'verify': 'Independently validate CROWN tree coverage, guard, connected-variable paths, connex output structure and height claims.',
    'exact': 'Implement the local finite partition recurrence/search machine for exact native-height optimization.',
    'certificate': 'Replay retained lower-bound evidence independently of search continuation state.',
    'fast_paths': 'Retain source-list compatibility while fast-path continuation implementation is owned by search_session.cpp.',
    'search_session': 'Advance a resumable exact/fast-path planner session under explicit transition/depth/time limits.',
    'candidate_generator': 'Enumerate candidate tree structures with an explicit generator frontier.',
    'candidate_key': 'Compute canonical candidate identity through a bounded resumable key machine.',
    'candidates': 'Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets.',
    'residual_reduce': 'Build residual reduction traces from query scopes and output structure.',
    'residual_trace': 'Replay and validate each claimed reduction step against the source query.',
    'residual_reconstruct': 'Reconstruct and check candidate trees, retaining the exact-repair boundary for counterexamples.',
    'ranking_integer': 'Perform bounded exact integer score arithmetic without floating-point ordering changes.',
    'selection_budget': 'Account selection work/resources/timing and translate component stop reasons.',
    'selection_cache': 'Manage bounded FIFO plan entries while retaining each entry\'s allocating account.',
    'selection_binding': 'Require exact source/query/backend binding before admitting cached or candidate plan authority.',
    'hash_directory': 'Provide separately chained stable-node hash lookup and prepared bucket-array growth.',
    'live_list': 'Provide intrusive nonowning membership and O(1) prepaid link/unlink for live traversal.',
    'indexed_nodes': 'Define separately owned row/key/member nodes and their directory/live-list hooks.',
    'accounted_indexed_nodes': 'Own native indexed nodes using the exact allocator embedded before destruction.',
    'indexed_journal': 'Record/reverse standalone indexed mutations using prepaid growth, pinned nodes and saved neighbors.',
    'accounted_indexed_journal': 'Record/reverse native indexed mutations using the original account/work grant.',
    'index_work': 'Admit every work dimension atomically from one noncopyable operation balance.',
    'index_work_alias': 'Expose different diagnostic policies over the same canonical work balance.',
    'accounted_ordered_rows': 'Own ordered row-set/map nodes with exact allocation ownership and nonallocating extraction/reinsertion.',
    'storage_work': 'Create a finite grant only for an outer indexed operation; retain/rebind it across nested and resumed work.',
    'constraint_validation': 'Validate complete native proposed source snapshots and enforced constraints under the query account.',
    'support': 'Maintain record/S/P/E support state and current/epoch cursor leases.',
    'delta': 'Maintain live visible-factor indexes, canonical delta producers and retained delivery epochs.',
    'session': 'Own input-to-output and durable lifecycle transitions for one creator-thread query session.',
    'window': 'Maintain operational event-time/FIFO membership and prepared expiration transitions.',
    'native_statistics': 'Build bounded native distributions using borrowed compact rows and shared storage work.',
    'owner_statistics': 'Capture selected table/index distributions with owner/sequence stamps and partial-completion status.',
    'memory_report': 'Capture/reconcile account allocation partitions with logical runtime ownership.',
    'observation': 'Collect optional counters/traces/clocks while preserving measured-zero versus unavailable fields.',
    'event_reader': 'Decode bounded stream records into funded native updates while retaining input progress.',
    'native_decode': 'Parse exact scalar fields directly into compact native values.',
    'input_progress': 'Track exact resumable record/source position independently of runtime/output sequence.',
    'compiler_plan_artifact': 'Read/write explicit compiler-owned plan artifacts at the native admission boundary.',
    'binary_detail': 'Encode/decode bounded fixed-width/versioned recovery fields and exact scalar payloads.',
    'journal_file': 'Own locked WAL descriptors, validate prefix state and poison uncertain append attempts.',
    'generation': 'Read/publish durable generation roots with exact identity and selection outcome.',
    'generation_retirement': 'Retire only history authorized by durable root/delivery state.',
    'local_sink': 'Persist canonical complete epoch output and return authority-bearing delivery receipts.',
    'plan_descriptor': 'Encode/decode exact selected-plan descriptor identity for generation recovery.',
    'policy': 'Admit W01 annotation policies and implement exact bounded support/aggregate arithmetic.',
    'include/crown/runtime/sql_aggregate.hpp': 'Declare genuine physical-source aggregate ownership, prepared batches and owning output.',
    'src/runtime/sql_aggregate.cpp': 'Maintain touched group statistics from one private authentic source batch.',
    'src/runtime/aggregate_detail.hpp': 'Share exact aggregate validation, arithmetic and rendering between runtimes.',
    'tests/unit/sql_aggregate_runtime_test.cpp': 'Exercise original-SQL source/group atomicity, arithmetic, grants and lifetimes.',
    'tests/reference/sql_aggregate_runtime_driver.cpp': 'Drive authentic physical aggregate batches and export full keys and epochs.',
    'tests/integration/sql_aggregate_runtime_oracle.py': 'Compare physical aggregate epochs with independent mature SQL recomputation.',
    'tests/unit/sql_source_snapshot_test.cpp': 'Verify complete physical-source images, actual bindings, limits and retained ownership.',
    'src/runtime/sql_cold_rebuild.hpp': 'Declare the concrete private bridge for unpublished genuine SQL cold reconstruction.',
    'tests/unit/sql_aggregate_rebuild_test.cpp': 'Verify whole-image reconstruction, sequences, cumulative grants, constraints and retained ownership.',
}

def family(path):
    # Ordered path/name heuristics select context; they do not certify file behavior.
    if path.endswith('CMakeLists.txt') or '/cmake/' in '/' + path or path.endswith('.cmake'): return 'build'
    if path.startswith('tests/'): return 'tests'
    if path.startswith('tools/'): return 'tools'
    if path.startswith('examples/'): return 'examples'
    if path.startswith('apps/'): return 'examples'
    if '/api/' in path: return 'api'
    stem = path.rsplit('/', 1)[-1].rsplit('.', 1)[0]
    if '/annotations/' in path: return 'annotations'
    if '/resource/' in path: return 'memory'
    if '/catalog/' in path: return 'catalog'
    if '/frontend/' in path: return 'frontend'
    if '/recovery/' in path: return 'recovery'
    if '/observability/' in path: return 'statistics'
    if '/io/' in path: return 'io'
    if '/planner/' in path:
        if stem=='difference':return 'difference'
        if stem=='fallback':return 'fallback'
        if stem=='comparisons':return 'comparisons'
        if stem=='star':return 'star'
        if stem=='keys':return 'keys'
        if 'residual' in stem:return 'residual'
        if any(v in stem for v in ('rank','select','binding','compiled_source')):return 'ranking'
        if any(v in stem for v in ('exact','search','certificate','candidate','continuation','producer','oracle','fast_path')):return 'search'
        return 'planner'
    if '/storage/' in path:
        if 'arena' in stem:return 'arena'
        if any(v in stem for v in ('layout','row','tuple','projection')):return 'values'
        return 'storage'
    if '/ir/' in path:
        return 'values' if stem=='scalar' else 'ir'
    if '/runtime/' in path:
        if stem=='difference':return 'difference'
        if stem=='cq_recompute':return 'cq_recompute'
        if stem=='fallback':return 'fallback'
        if stem=='source_image':return 'physical'
        if stem=='comparisons':return 'comparisons'
        if stem=='star' or stem.startswith('star_'):return 'star'
        if stem=='topk':return 'topk'
        if stem.startswith('weighted'):return 'weighted'
        if stem in {'program','program_model','program_json','program_span','program_aliases'}:return 'ir'
        if any(v in stem for v in ('statistics','observation','inspection','memory_report','maintenance_cost','ranking_evidence')):return 'statistics'
        if stem in {'window'}:return 'window'
        if 'session' in stem or 'reoptim' in stem or stem in {'replay','update_pattern','update_pattern_detail'}:return 'session'
        if stem in {'physical','initialization','update_view','constraint_validation','validation_work'}:return 'physical'
        if stem in {'delta','checkpoint_policy','accounted_ordered_rows'}:return 'delta'
        if stem=='selection':return 'ranking'
        return 'support'
    return 'ir'
