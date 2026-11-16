CROWN Next: complete native implementation plan

Prepared 5 November 2026
Status: research-grounded design and coding-agent work plan. No successor implementation, legacy build, benchmark run, or performance claim is asserted by this document.

0. Recommendation and intended result

Build a new, plan-driven CROWN engine in C++23, with a SQL frontend, a typed conjunctive-query representation, an independently checked minimum-height planner, generic native and generalized runtime nodes, and separate interfaces for current-result and change enumeration. Use the original CROWN implementation and DynaGox's C++ CROWN baseline as references and comparison systems. Reuse individual data-structure designs after checking arithmetic, ownership, and provenance. A new query must be admitted through SQL or the public query IR; it must not require a new query-specific C++ class.

The central deliverable is an executable path from SQL to a certified plan to maintained results:

flowchart TD
    SQL["SQL and catalog"] --> Frontend["Parser, binder, normalization"]
    Frontend --> CQ["Typed CQ and output semantics"]
    CQ --> Structure["Free-connex recognition and tree search"]
    Structure --> Check["Independent plan and height checks"]
    Stats["Update and data statistics"] --> Cost["Cost ranking within the chosen height"]
    Check --> Cost
    Cost --> Physical["Physical plan and index specification"]
    Physical --> Runtime["Native CROWN runtime"]
    Updates["Committed input updates"] --> Runtime
    Runtime --> Results["Snapshot and delta cursors"]
    Runtime --> Recovery["Checkpoints and replay"]
    Runtime --> Stats

The default planning objective is lexicographic: first minimize CROWN height, then select a practical plan within that minimum-height family. CROWN height counts input-relation nodes along a root-to-leaf path and gives generalized nodes weight zero. It is neither binary operator-tree height nor the radius of an ordinary join tree. The original CROWN paper supplies the runtime foundation; the 2026 parameterized-hardness paper proposes a recursive structural route; the 2026 meta-decomposition paper supplies the strongest connection to a compact cost-based search. The audit in Section 5.3 identifies a concrete obstruction to using the inspected residual-height recipe as an unconditional certificate. Therefore the complete exact planner and independent verifier are the authoritative initial implementation. P1, P2, P3

0.1 Release boundaries

Release

Meaning of completion

Main acceptance condition

R0: executable specification

Reference semantics, typed IR, structural verifier, exact tree oracle, and adversarial fixtures

A small query and update trace have independently computed answers, deltas, and minimum tree height

R1: complete free-connex set engine

Automatic compilation of every finite free-connex equality CQ in the documented SQL fragment, arbitrary relation arity/fan-out, projection, Boolean queries, disconnected queries, self-joins, insertion/deletion, snapshot and delta output, basic cost ranking, CLI, checkpoint/replay

The full SQL-to-result pipeline passes the structural, semantic, lifecycle, and recovery gates; minimum-height status is honest and independently checkable

R2: practical SQL analytics

SQL bag semantics, exact multiplicities, COUNT, SUM, AVG, declared NULL behavior, richer ingestion and cost estimates

Each feature has a separate semantic and complexity contract; set-mode tests continue to pass

R3: research extensions

Comparisons, heavy/light backends, snapshot top-k, non-free-connex/cyclic fallback, richer annotation domains, approximation, parallel execution

Each extension passes its own admissibility and guarantee checks before being selected automatically

R1 is a complete system for the stated free-connex set-query contract. R2 makes it useful for a broader SQL workload. Neither label means support for every SQL construct. The parser may understand syntax that the engine deliberately rejects with a precise diagnostic. Resource limits may stop compilation, but a timed-out heuristic result must never be presented as a proven minimum-height plan.

Do not build independent C++ and Rust engines in parallel. If the implementation team strongly prefers Rust, make that decision at task A01 and use the same plan schema, task dependencies, semantic fixtures, and audit gates. The Rust alternative is described in Section 3.1.

0.2 How to use this document

Sections 1–10 define evidence, contracts, algorithms, and architecture. Section 11 contains 78 coding-agent task cards. Sections 12–14 define 12 audit gates, 44 named regression cases, and experiments. Sections 15–17 give the execution order, handoff templates, and release checklist. Section 18 records sources and the scope of the source review.

Give a coding agent one task or one tightly connected group at a time. Require the task's artifacts and acceptance evidence before moving across a checkpoint. The agent should update a task ledger with not_started, in_progress, implemented, verified, or blocked; writing code is not equivalent to passing the gate.

1. What the papers and repositories contribute

1.1 Paper-to-component map

Source

Relevant contribution to this design

Planned use and boundary

Change Propagation Without Joins, corrected full version, arXiv v2, December 2023 P1

Join-free support maintenance and factorized enumeration

Foundation for the set runtime; translate definitions into explicit invariants and audit projection and deletion scheduling

Towards Parameterized Hardness on Maintaining Conjunctive Queries, PODS 2026 P2

Height, residual reduction, reconstruction, and a specialized star algorithm

Structural candidate generation and a focused proof audit; the inspected residual-height shortcut is not accepted as an unconditional certificate

Succinct Structure Representations for Efficient Query Optimization, SIGMOD 2026, v2 P3

Meta-decompositions and ordinary join-tree search

Candidate/search interface for CBO; mapping to generalized CROWN trees and a dynamic cost model requires additional work

Towards Update-Dependent Analysis of Query Maintenance, PODS 2025 P4

FIFO and mixed update-pattern analysis

Explicit workload contracts and later pattern-aware planning

Maintaining Acyclic Foreign-Key Joins under Updates, SIGMOD 2020 P5

Key-aware maintenance and update-sequence analysis

Trusted constraint metadata and optional specializations; foreign-key acyclicity is a different property from alpha-acyclicity

Yannakakis+, SIGMOD 2025 P6

Practical structural query processing through relational plans

Bootstrap/rebuild route, compiler separation, and a static comparison implementation

Quorion, VLDB 2025 demo P7

Parser/planner, optimizer, IR and SQL rewriting architecture

Optional SQL reference/export backend and inspectable plans

SparkSQL+, SIGMOD 2023 demo P8

SQL-to-hypergraph and generated execution actions

Typed frontend and backend boundaries; no JVM dependency in the native runtime

Conjunctive Queries with Comparisons, SIGMOD 2022 P9

Structural treatment of comparisons across relations

A later predicate-aware planner and runtime, separate from equality CQ recognition

Relational Algorithms for Top-k Query Evaluation, SIGMOD 2024 P10

Static relational top-k algorithms

A later snapshot operator; dynamic top-k is a separate problem

Computing the Difference of Conjunctive Queries Efficiently, SIGMOD 2023 P11

Structural evaluation of differences

Later difference/anti-join work; do not identify SQL difference with incremental delta maintenance

Approximate Query Processing under Updates, Dai and Yi, 2025/2026 P12

DynaGox and approximate aggregation

Optional approximation work; the exact C++ baseline and approximate algorithms must be separated

The first three papers should be mandatory reading for the planner owner. P1 and P4 should be mandatory reading for the runtime owner. P6–P8 are useful implementation precedents. P9–P12 define extension opportunities rather than prerequisites for R1. The recent aggregation preprint P13 was found, but its full text was not accessible during this review; no specific theorem from it is used as a release guarantee.

1.2 Pinned repository evidence

Repository

Reviewed snapshot

What is present

Main consequence

NTU-DBT/CROWN

master at e369a623517723b3be3ea3e9806779f3c591e7f9 R1

Scala/Flink runtime, handwritten query classes, experiment scripts

Preserve as a reproducible baseline and source of regression traces

hkustDB/DynaGox

main at c6811db68a34ab3b32722968c4e1e821f730c5ac R2

Native C++ infrastructure, specialized CROWN baselines, DynaGox, comparison workloads

Useful native reference; a generic compiler and executor still need to be built

The CROWN component README explicitly asks the developer to rewrite SQL into natural-join form, select a low-height generalized tree, and write a ProcessFunction and Job. It documents COUNT as the supported aggregation. The new system should eliminate that manual workflow. R3

The actual C++ CROWN source in DynaGox is under dynagox_cpp/implement/experiments/include/crown/ and dynagox_cpp/implement/experiments/src/crown/. The top-level crown_cpp/ directory contains experiment scripts. The entry point selects fixed query classes rather than compiling SQL. R6, R7

1.3 Concrete limitations to turn into acceptance tests

Source observation

Required successor behavior

CROWN Relation.scala rejects enumeration paths when connection.length >= 3 R4

N-ary operators and cursors; test three, four, eight and larger child counts without changing the height objective

The same source rejects multi-level non-output annotated propagation and contains a root-only-output annotation TODO R4

Deep hidden subtrees and a sole output root must be explicit test families

Legacy annotations use floating-point values; DynaGox's shared map uses epsilon-based zero R4, R8

Exact support transitions and exact count arithmetic, with declared overflow behavior

DynaGox query implementations differ in operation support; the inspected crown_line5cd.cpp only invokes insertion paths R9

Feature support must be verified per query/semantics/update mode

Legacy result verification converts values to doubles and uses tolerances R10

An independent exact oracle for the new engine

DynaGox's maps/pools use manual ownership and allocation R8

Ownership, destruction, stable handles, clearing, and iterator invalidation need an explicit audit before reuse

These are source-level observations, not claims that the published theoretical results have those restrictions. Neither repository was built or executed for this plan. Both complete path inventories were inspected, but not every specialization or vendored component was reviewed.

1.4 Reuse policy

Preserve legacy artifacts in separate baseline directories or pinned external checkouts. Use the CROWN state transitions as a behavioral reference. Consider adapting DynaGox's primary/secondary index design, but first replace numerical zero handling and establish ownership. Reuse workload definitions and trace formats where useful. Build the frontend, query IR, generic planner, certificate checker, plan-driven runtime, operational lifecycle, and independent oracle as new components.

The reviewed snapshots did not expose a root LICENSE, although vendored components have their own notices. Task A02 records component provenance and the intended license of the new project before code is copied into a distributable release. This is a setup task, not a blocker to design or independent implementation.

2. Exact product and semantic contract

2.1 Mathematical core

Represent a normalized query as

[
Q(F)=\pi_F\left(\Join_{a\in A}R_{b(a)}(\rho_a)\right),
]

where A is a set of atom occurrences, b(a) identifies a physical base table, rho_a maps its columns to query variables after binding and equality normalization, and F is the set of free variables. Different occurrences may read the same base table. Hyperedges are occurrence scopes, not just distinct sets of variable names. Two different mutable tables on the same scope remain two inputs.

R1 uses set semantics. A duplicate insertion into a set table and deletion of an absent tuple are no-ops, unless a configured strict ingestion policy reports an error. Every committed physical update has one sequence number and one visible before/after state. Initial loading is charged as input work; there is no unreported preloading phase in maintenance experiments.

For a committed update from D_before to D_after, define

[
\Delta^+=Q(D_{after})\setminus Q(D_{before}),\qquad
\Delta^-=Q(D_{before})\setminus Q(D_{after}).
]

Each delta set is duplicate-free. An existential witness changing does not imply an output tuple changes. Current-result enumeration, membership changes, bag multiplicity changes, aggregate-value changes, and SQL EXCEPT are different APIs and must have different types.

2.2 Meaning of all free-connex queries

R1 must admit every finite classical equality CQ whose body hypergraph H and augmented hypergraph H ∪ {F} are alpha-acyclic, expressed in the supported fragment. This includes arbitrary arity, nested overlaps, redundant/contained scopes, repeated scopes, proper projections, Boolean heads, disconnected components, and renamed self-join occurrences. The implementation must not limit the class to binary graph paths, stars, full joins, PK/FK joins, connected inputs, a fixed number of variables, or a maximum runtime fan-out.

Use dynamically sized variable sets and vectors. A 64-bit bit mask is an optimization for small queries, not a semantic cap. Resource limits are explicit operational limits. For a query outside the native fragment, return the unsupported construct and reason; a later fallback backend must advertise its own behavior and costs.

2.3 SQL support matrix

Construct

R1

R2 or later

Required handling

SELECT DISTINCT with column projections

Required

—

Set CQ semantics

FROM, aliases, INNER JOIN ... ON, comma joins with equalities

Required

—

Normalize to occurrence IDs and equality classes

Composite equality keys and repeated-variable equalities

Required

—

Preserve all key columns and intra-tuple checks

JOIN ... USING, NATURAL JOIN

Required frontend normalization

—

Expand against catalog schemas before structural analysis

CROSS JOIN / disconnected components

Required

—

Empty separators and a nullary combining interface

Constants, typed parameters, local predicates

Required bounded expression subset

More functions later

Evaluate before an occurrence enters the maintained CQ; preserve binding and NULL rules

Boolean CQ / EXISTS wrapper around the supported SPJ fragment

Required

—

Core: zero/one nullary tuples; SQL SELECT EXISTS wrapper: one FALSE/TRUE row, with corresponding wrapper deltas

Unused physical columns / local input projection

Required

—

Count supports when several physical rows map to one logical input tuple

Self-joins

Required

—

Atomic physical update fans out to all affected occurrences

Plain SELECT with SQL bag semantics

Parse and diagnose until implemented

Required R2

Never silently interpret as DISTINCT

COUNT, SUM, AVG, GROUP BY

Parse and diagnose until implemented

Required R2 for admitted structures

Separate group existence, multiplicity and value

NULL-bearing inputs

Non-null classical core; explicit SQL adapter policy

Required R2 SQL behavior

SQL equality does not match NULL; do not use ordinary value equality accidentally

Simple nonrecursive CTEs/subqueries

Optional R1 inlining

Broader R2

Inline only after scope, multiplicity and semantic checks

Cross-relation <, <=, <>, arbitrary theta predicates

Reject from equality guarantee

R3

Separate comparison admissibility and indexes

Outer join, negation, EXCEPT, union, recursion

Reject from native CQ guarantee

R3

Separate operators, contracts and tests

ORDER BY, ranking and LIMIT

Reject unless an exact wrapper is separately implemented and admitted

Snapshot top-k in R3

Never accept an ordering or limit clause and ignore it; account for ordering/selection work separately

The initial type set should cover signed integers, exact fixed-scale decimal values, strings with a fixed binary collation, dates, timestamps, and Boolean values where the relevant operators are implemented. Record the cost of variable-length hashing and serialization separately from fixed-word theoretical bounds. Unsupported implicit casts, collations, time-zone conversions, or functions must be rejected rather than approximated.

2.4 NULL, duplicate and identity decisions

Keep physical row identity separate from set-valued logical tuple identity. A source such as CDC may distinguish two physical rows with equal projected values; a logical occurrence therefore needs a derivation count before it emits a 0-to-1 or 1-to-0 set transition. An adapter may not discard an unused column and then treat deletion of one physical row as deletion of the whole projected tuple.

SQL NULL handling belongs in the SQL adapter and predicate evaluator. An equality class formed by a = b requires the participating values to satisfy SQL equality, including non-null checks. DISTINCT grouping of NULL output values is a different equivalence relation. IS NOT DISTINCT FROM is not rewritten to ordinary equality unless the engine explicitly implements its semantics.

Identifiers, output positions, repeated output columns and aliases are preserved independently of the unique variable set F. Optimizer rewrites require proof under the selected set/bag mode. In particular, a contained mutable atom is not removable merely because its scope is contained in another atom's scope.

2.5 What a performance guarantee includes

Every plan carries a GuaranteeProfile: semantics, query class, update contract, arithmetic model, state-space bound, maintenance bound, cursor startup/delay/termination bound, and the assumptions used. Query-size factors are explicit in engineering measurements, even when the paper uses fixed-query data complexity.

For the certified set implementation, the intended core bounds follow the CROWN contract: linear maintained state for fixed queries; update work governed by the chosen tree and update sequence; constant delay for supported cursors after the required maintenance. Arbitrary updates to all free-connex queries are not uniformly constant-time. Hash-based bounds use their stated expected/amortized assumptions. A bounded-latency adversarial hashing mode can use a different index with an explicitly different bound. P1

Output costs are charged. Producing k result tuples requires at least k output actions. Retained snapshots, queued deltas, a materialized client result, WAL, multiple queries, and allocator slack are separate accounting categories; they do not disappear inside an O(N) engine-state claim.

3. Language, modules and stable interfaces

3.1 C++ default and Rust alternative

Use C++23 with CMake, a pinned toolchain matrix, sanitizers, and a reproducible dependency lock. This matches the standard requested by the reviewed DynaGox build and gives the shortest path to native index reuse. Prefer RAII, non-owning spans with explicit lifetimes, arena-owned handles, and typed IDs over raw owning pointers. Generic interpretation comes before specialization or generated code.

Wrap a pinned release of libpg_query for PostgreSQL syntax. Immediately translate its result into owned frontend structures; free parser-owned memory within the wrapper. A parser does not provide a catalog, semantic binder, type checker, CQ recognizer, or CROWN plan. Those are engine components. T1

If Rust is selected instead, use sqlparser-rs, a Cargo workspace, arena/generational IDs, and equivalent IR boundaries. Its documentation explicitly separates syntax from semantics. C++ containers then serve as designs to reimplement, not components to embed automatically. Do not introduce a C++/Rust hot-path boundary merely to retain legacy code. T2

Choose exact dependency versions during the initial build spike, record checksums/commits, and update them through reviewed changes. Do not depend on main, master, or a moving *-latest branch in release builds.

3.2 Proposed repository structure

CMakeLists.txt
cmake/
include/crown/
  api/                 Public library interfaces and versioned types
  catalog/             Schemas, relation IDs and constraints
  frontend/            Parser wrapper, binder and expression typing
  ir/                  CQ, tree and physical-plan definitions
  planner/             Recognition, exact search, ear reduction and CBO
  storage/             Tuple arenas, dictionaries and indices
  runtime/             Operators, event scheduler and state invariants
  enumerate/           Snapshot, pinned-witness and delta cursors
  annotations/         Bag/aggregate policies and capability checks
  io/                  Input/output adapters and backpressure
  recovery/            WAL, checkpoints and replay
  observability/       Metrics, tracing and EXPLAIN
src/                   Implementations matching those modules
apps/crown/            CLI and optional local service
schemas/               Versioned catalog, CQ and plan JSON schemas
tests/
  reference/           Independent slow semantics and tree oracle
  unit/
  property/
  integration/
  regression/
  recovery/
benchmarks/
  queries/
  traces/
  generators/
  manifests/
  reports/
docs/
  semantics.md
  sql_support.md
  invariants.md
  planner_proofs.md
  guarantees.md
  task_ledger.md
  source_baselines.md
  decisions/
tools/                 Trace conversion, plan checking and result comparison

The diagram and directory layout are proposed interfaces, not existing files in either source repository. The implementation agent may refine filenames while preserving module ownership and test independence.

3.3 Data models

Representation

Essential fields

Must not contain

Catalog

Table/column IDs, types, nullability, enforced/trusted constraints, source schema versions

Guessed keys treated as constraints

Bound SQL

Resolved columns, typed expressions, output positions, explicit set/bag mode, source locations

Unresolved string-name lookup in runtime paths

NormalizedCQ

Physical base IDs, logical occurrence IDs, variable classes, scopes, head, local adapters, predicates, contradiction flag

Merged distinct mutable relations

FreeConnexTree

Root, native/generalized node kind, node scope, parent/children, separator, connex membership, occurrence mapping

Phantom materialized relation over all head variables

PlanCertificate

Structural witness, checked height, lower-bound/optimality evidence, source algorithm/version, normalized-query hash

A Boolean optimal=true unsupported by evidence

PhysicalPlan

Tuple layouts, compiled projections, indices, operator states, event routes, enumeration program, arithmetic policy

Source-language SQL expressions interpreted per tuple

GuaranteeProfile

Admitted semantics and operation modes, complexity assumptions, output accounting, limits

A single unqualified supports_query flag

Canonical query and plan serialization should be deterministic and versioned. Plan cache keys include the catalog version, normalized semantics, arithmetic policy, planner version, and optimization policy. Statistics changes invalidate cost decisions according to policy; schema or semantics changes invalidate the plan itself.

3.4 Library API sketch

CompileResult compile(SqlText sql, const Catalog&, const CompileOptions&);
ValidationReport validate(const NormalizedCQ&, const FreeConnexTree&);
Engine open(const PhysicalPlan&, const EngineOptions&);

ApplyResult apply_set_update(Engine&, const PhysicalSetUpdate&);
SnapshotCursor enumerate_current(Engine&, const SnapshotOptions&);
DeltaCursor enumerate_delta(Engine&, CommittedOrPendingEpoch);
DrainResult drain_or_discard(DeltaCursor&);

CheckpointResult checkpoint(Engine&, const CheckpointOptions&);
Engine restore(const CheckpointManifest&, const RestoreOptions&);
ExplainDocument explain(const CompileResult&, const ExplainOptions&);

This is an interface sketch, not compilable code. In the actual API, pending/committed epoch types and cursor ownership must make illegal sequencing difficult. Avoid a single bool enumerate flag that conflates maintenance-only, full enumeration, lazy delta enumeration, and counting output.

4. Frontend and normalization

Compile in the following order: parse; bind catalog names and scopes; type expressions; expand *, USING and NATURAL JOIN; identify local predicates; normalize equalities; construct occurrences; derive the output mapping; determine semantic mode; recognize the query class; plan. Keep source spans so a rejected construct can be explained at its original location.

Union-find is suitable for compatible equality classes. Before merging variables, establish type/collation compatibility and record non-null conditions implied by SQL equality. Constants may make the query contradictory; compile that case to a constant-empty operator. Repeated variables in one atom become intra-tuple constraints before projected tuple insertion. Non-equality predicates spanning different atoms remain explicit and do not enter the equality hypergraph as if they were equality edges.

Each atom has an input adapter that performs renaming, local filtering, required casts, and support-counted projection. Share physical scans/dictionaries where safe, but do not share logical state just because scopes look equal. In R1, relation elimination and constraint-based semantic simplification are disabled unless their exact preconditions are checked and recorded in the plan.

For acyclicity, implement standard GYO reduction with a replayable witness. Check both H and H ∪ {F}. The extra edge F is a recognition device; it is not permission to materialize the complete answer relation or to use an unguarded head node as a runtime generalized relation. Store the failed reduction core when recognition fails. Distinguish acyclic_non_free_connex, cyclic, unsupported_semantics, and resource_limit.

The reference path should also accept a compact CQ JSON format. This makes structural and runtime testing independent of the SQL parser. SQL-to-IR equivalence is tested separately against the same reference evaluator. The oracle must not call the production normalizer to decide what the input SQL means in tests intended to catch normalization errors.

5. Minimum-height free-connex planner

5.1 The admissible tree family

For a tree T, each native node is one atom occurrence with its complete normalized scope. A generalized node has a variable scope and no external input table. The independent verifier checks:

Every native occurrence appears exactly once; every leaf is native.

For every variable, the nodes containing it induce a connected subtree.

Every generalized node's scope is a subset of every child's scope.

No native node is an ancestor of a generalized node.

A root-containing connected connex subtree covers all head variables, and every parent separator of a node in that subtree is contained in the head.

These conditions follow the CROWN tree definition. Treat generalized-node guard and above conditions as explicit rules, not implicit properties of a heuristic constructor. P1, Section 3.2; P2, Section 2.1

Compute

[
h(T)=\max_{\ell\text{ leaf}}\sum_{v\in path(root,\ell)}[v\text{ is native}],
\qquad
h^*(Q)=\min_{T\text{ admissible}}h(T).
]

Store ordinary edge depth and execution-program depth as separate metrics. A native singleton has height one. A constant query without atoms is handled separately with height zero.

5.2 Connex verification without guessing a subtree

Engineering lemma. For a fixed rooted tree, let C* contain exactly the nodes reachable from the root by traversing only edges whose separator is contained in F. An admissible connex subtree exists exactly when the union of the scopes in C* covers F.

Reason. Every valid root-connected connex subtree can cross only those edges, so it lies inside C*. Conversely, C* is itself connected, contains the root, and satisfies the separator condition. Therefore coverage is the only remaining condition. This also handles an empty head and empty separators.

Implement this as an independent traversal. Record C* in the certificate, or record a smaller validated subtree if a physical optimization benefits from it. Do not infer connex membership from whether a relation contains any output variable: a node may contain an output variable but be separated from the root by a hidden-variable key.

5.3 Source-based candidate route: residual reduction and reconstruction

P2 gives a structural route in Definition 2.9, Algorithm 1, Lemma 3.8 and Appendix B. The implementation must preserve its round semantics. For the current residual query, let U be variables occurring in exactly one current atom. A native occurrence with scope e is an ear if an anchor a exists such that either

[
e\setminus U\subseteq a\quad\text{and}\quad e\cap U\subseteq V\setminus F,
]

or

[
e\setminus U\subseteq a\cap F.
]

At the start of a reduction round, freeze the set of eligible ears and its supporting information. Remove only a frozen ear that still has an anchor in the remaining relation set. Do not recompute ears after every deletion within that round. Preserve a representative when ears are mutual anchors. After the round, construct the induced residual query and induced head, then compute the next round. Stop at a q-hierarchical residual. Retain all removed occurrences and their source scopes; they must return in the final tree.

Construct a height-one tree for the q-hierarchical residual using the laminar family of variable-occurrence sets, with native occurrences as leaves and appropriate generalized scopes. Reconstruct earlier layers while respecting running intersection, guards, above, the restored head, and connex connectivity. P2 states a minimum-height relation, but the examples below show why its inspected formulation cannot simply become an implementation certificate. Use this route to generate candidate trees until a corrected complete construction and height proof are available.

Anchor selection is a real algorithmic task. Choosing an arbitrary surviving anchor is not sufficient. Consider

[
Q(x,w)(x,a),A(x,a,b),B(x,b,c),C(x,c,d),U(x,d),E(x,w).
]

After removing L, U, and E in one frozen round, a residual tree can have B as root and A,C as children. Its connex subtree for head {x} contains B. Reattaching E below A crosses separator {x,b}, which contains hidden variable b, so the restored head variable w is not connex. Attaching E below B works. This is a counterexample to a naive anchor-choice implementation, not a refutation of the existence theorem.

Task P05 must either implement and justify a complete compatible-anchor/restructuring procedure or invoke the complete search below whenever reconstruction is not certified. Handle a generalized connex anchor carefully: inserting a native child whose scope does not contain the generalized parent's scope violates the guard rule. A post hoc validity check detects such an error but does not by itself repair the construction or prove minimum height.

Generalized-node augmentation is sometimes necessary. For

[
Q(a,c)(a,z,x),R(a,z,y),L(x),U(y),S(a,c),
]

the residual P,R has a height-one tree rooted at generalized scope {a,z}. Attaching S directly under either native anchor fails the output-connectivity condition. A valid height-two tree instead uses a new generalized root {a}, with children S and generalized {a,z}; the latter has children P,R, with their respective unary guards below them. This repairs that example, but does not establish a general reconstruction algorithm.

A stronger residual-height counterexample under the inspected definitions. Consider distinct mutable occurrences

[
\begin{aligned}
Q(x,y,w):;&R(x,y,z,r),\ S(x,y,z,s),\ L(r),\ V(s),\
&T(y,a,b),\ U(y,a,c),\ B(b),\ C(c),\ E(x,w),
\end{aligned}
]

with head {x,y,w}. Its body is acyclic: an ordinary join tree has R adjacent to S,L,E,T, S adjacent to V, T adjacent to U,B, and U adjacent to C. Adding the head edge also preserves acyclicity: attach the head edge to R and move E below that edge. Thus this is a free-connex query.

The first frozen-ear round removes exactly L,V,B,C,E. The residual contains R,S,T,U, has head {x,y}, and is q-hierarchical. In particular, the occurrence sets of x,z are {R,S}, those of a are {T,U}, and that of y is {R,S,T,U}; the remaining private variables occur once. It therefore has a height-one tree. The literal one-round height-drop rule would predict height two for the original query.

The original query has a valid height-three tree: a generalized {y} root has children R and generalized {y,a}; R has children S,L,E; S has child V; generalized {y,a} has children T,U; T has child B; and U has child C. A connex subtree containing {y}, R, and E covers the head with output-only separators. All guard and running-intersection conditions hold.

It cannot have height at most two. Each of the four main atoms R,S,T,U has a private variable shared only with its unary guard. If a main atom were the second native node on its root path, its guard could not be below it. Running intersection for the private variable would then force its first native ancestor to be that unary guard. That ancestor lacks y, disconnecting this main atom from the other main atoms containing y; placing another main below it instead would create a third native node. Therefore all four mains must be first native nodes on their root paths.

The generalized least common ancestor of R,S contains hidden variable z. Consequently the incoming generalized separators of R,S contain z, and neither native node can lie in the root-connected output subtree. The occurrence E must be reachable in the maximal such subtree to supply w: if a generalized node supplies w, the guard condition confines its descendant path to E to subsets of {x,w}, so that path has output-only separators. If E were a second native node, connectivity for x would force its first native ancestor to be R or S, which is impossible for the output subtree. Hence E must also be a first native node.

Restrict the generalized skeleton to these five first native nodes. A height-one guarded tree requires the variable-occurrence sets of its leaves to be laminar: the least common ancestor of all leaves containing a variable contains that variable, and the guard condition forces every descendant leaf to contain it. Here x occurs in {R,S,E} and y in {R,S,T,U}. These sets overlap and neither contains the other, a contradiction. Thus the minimum native-node height is three, despite the height-one residual.

This is an analytical finding about the definitions and residual recipe in the inspected arXiv v1 P2, Definition 2.9, Algorithm 1 and Appendix B. It is not a claim about an unexamined later revision, nor a rejection of the CROWN maintenance framework. Preserve this query as a mandatory planner fixture. A coding agent must not report the number of ear rounds plus one as the exact minimum without resolving this obstruction. The finite exact construction in Section 5.4 remains valid independently of this issue.

The same issue affects direct certification from the inspected Trim reconstruction in P4, Lemma 3.7. It does not by itself settle the validity of every FIFO or mixed-update result in that paper. Any pattern-specific guarantee depending on that structural route needs a separate audit. The current arXiv metadata for P2 listed v1 as its available version when checked on the preparation date.

A smaller regression uses seven atoms:

[
Q(x,y,w)(x,y,z,r),S(x,y,z,s),L(r),V(s),T(y,b),B(b),E(x,w).
]

Its frozen ears are L,V,B,E; the residual R,S,T is height one, while the original is height three by the same argument. A valid height-three tree has generalized root {y} with native children R,T; R has children S,L,E; S has child V; T has child B. Use this smaller form in quick CI and the nine-atom form in the full structural suite.

5.4 Complete exact oracle and fallback

Build an independent finite search over the actual admissible CROWN family. This provides a correctness baseline without assuming the optimized reconstruction is already complete.

Normal-form lemma. For a query with m >= 1 native occurrences, some minimum-height tree has at most m−1 generalized nodes, each with at least two children. Every generalized scope is a subset of some native scope.

Proof sketch. A generalized node with one child can be contracted. Its scope is contained in the child's scope; its parent, if present, is generalized and has scope contained in it. The contraction preserves running intersection, guards and the above condition. If the contracted node belongs to a connex subtree, replace it there by its child; the new parent separator is still an output-only separator and head coverage is preserved. Native path counts are unchanged. Repeat until no generalized node is unary. There are no generalized leaves. In a rooted tree, branching nodes of at least two children number at most the number of leaves minus one, and every leaf is native, giving at most m−1 generalized nodes. Repeated application of the guard condition down a path puts every generalized scope inside a native descendant's scope.

This proof is an original design argument in this plan, independently checked during preparation. It is not attributed to a cited paper, and its formal statement belongs in planner_proofs.md with the implementation's conventions.

The exhaustive algorithm is then concrete:

for height_bound = 1 .. m:
    for generalized_node_count = 0 .. m-1:
        enumerate rooted tree topologies on the native occurrences
            and the indicated number of generalized nodes
        enumerate generalized scopes from the union of native power sets
            (including the empty scope)
        reject candidates violating cover/connect/guard/above
        compute C* and reject if it does not cover the head
        reject if native path height exceeds height_bound
        if a candidate remains, return the first feasible height and tree

This is finite and complete; it is intentionally expensive in query size. Use it on small instances as an oracle and as the semantics of an unrestricted exact fallback. Optimize it through sound pruning, memoization and symmetry breaking only after the reference path is frozen. Empty-body constant queries are separate; disconnected nonempty queries may use an empty-scope generalized root.

For larger queries, use validated residual candidates together with independent lower-bound evidence, branch-and-bound, or a constraint encoding over the same complete family. Residual round counts are not certificates. A solver result is a useful computation, but a bare UNSAT string is not an independently checkable proof. Retain a replayable exhaustive proof or a solver certificate with a verifier if claiming externally verifiable optimality. A validated tree provides an upper bound; proving no tree of height h−1 exists provides the matching lower bound.

5.5 Planner status and optimizer policy

Return separate fields:

{
  "tree_valid": true,
  "selected_height": 2,
  "height_lower_bound": 2,
  "height_upper_bound": 2,
  "height_status": "proven_minimum",
  "height_evidence": "exact_search_certificate",
  "cost_status": "best_among_examined_minimum_height_candidates",
  "height_search_complete": true,
  "cost_search_complete": false,
  "query_semantics": "set",
  "runtime_backend": "crown_exact"
}

The example distinguishes a proved structural optimum from incomplete cost search. Also support valid_upper_bound, resource_limit, and unsupported statuses. Default --height-policy strict accepts only a proven minimum. An explicit --height-policy best-found can return an incumbent and its gap. Do not silently substitute this policy on timeout.

Minimum height is not the same as minimum observed latency. Make min_height_then_cost the default because it implements the requested objective. An optional cost_under_memory_budget policy may select a taller valid plan only when explicitly requested, and must display both the minimum and selected heights.

5.6 Structural regression requirements

Test a singleton, two full joined atoms with a generalized root, a proper-head two-atom query requiring height two, long full and projected paths, nested scopes, equal scopes, high-arity relations, high fan-out, Boolean queries, disconnected components, and the incompatible-anchor example above. Test atom/variable renaming invariance and head changes on the same body. The checker must reject missing occurrences, duplicated occurrences, a broken running-intersection variable, an unguarded generalized node, a generalized node below a native node, and a non-connex output.

Small finite exhaustive tests validate implementation behavior; they are not a proof that a novel polynomial planner is complete. Release evidence needs both the algorithm argument and independent oracle agreement.

6. Storage and the generic set runtime

6.1 Logical node state

For node v, write B_v for its scope and K_v for its separator with its parent. Let S_v be its surviving subtree tuples and P_v its projected parent support. For a native node,

[
S_v={t\in R_v:\forall c\text{ child of }v,\ t[K_c]\in P_c},
\qquad
P_v=\pi_{K_v}S_v,
]

Operationally, a native tuple survives exactly when every child supplies its matching separator key. For a generalized node, every child projects to the generalized scope, and its support is the intersection of those child key sets. P1, Section 4

In addition, for every enumeration node in the connex subtree, maintain a support-counted local output projection

[
E_v=\pi_{F\cap B_v}S_v.
]

Use E_v to enumerate visible assignments without repeating hidden witnesses. Do not assume the native root scope is contained in F; Q(x):R(x,z) is already a counterexample. A Boolean root uses a nullary E_v with either zero or one tuple.

Structure

Key

Contents/invariant

Base/occurrence table

Full normalized tuple

Physical derivation count and logical presence

Native tuple record

Stable tuple ID

Values/column IDs, number of satisfied children, membership in S_v

Child lookup

Separator key

Presence and support of a child's P_c

Reverse separator index

Child separator key

Native tuples whose support may be affected by that key

Parent projection table

K_v

Exact number of surviving local tuples projecting to the key

Generalized candidate table

Generalized scope

Child-presence count; survives iff all children are present

Enumeration projection

F ∩ B_v

Exact number of surviving local tuples, stable iteration links and separator buckets

Live output view, delta mode

F ∩ B_v

Assignments known to participate in a current full answer, with a documented epoch

Counters in different rows have different meanings. Use different types and names, for example PhysicalDerivationCount, SatisfiedChildCount, ProjectionSupportCount, and AnswerMultiplicity. A common field named count invites incorrect updates.

6.2 Native storage design

Intern schema/variable IDs at compile time. Intern strings where beneficial, while preserving dictionary lifetimes and release policies. Store tuple values in typed layouts and use precompiled projection programs for keys. Use arenas with generational handles so deleted and reused tuple slots cannot silently alias an old cursor reference.

Provide primary equality lookup, iteration over live records, and secondary separator buckets. A separator projection can be shared within a node if its column set and value semantics are identical. A hash bucket iterator should visit live tuple handles, not scan a high-water array full of tombstones. The cost and reclamation of hash-table resizing, overflow buckets and arenas belong in the accounting.

Start with a simple correct standard-container implementation behind the storage interface. Add a specialized map after measurements identify the bottleneck. If adapting DynaGox, make containers noncopyable or correctly movable, define destruction on clear, and separate annotation arithmetic from key-index membership. The reviewed ownership assumptions are appropriate to examine before introducing nontrivial strings or concurrency. R8

6.3 Event types and state transitions

Use explicit internal events such as NativeInsert, NativeDelete, ChildKeyAppeared, ChildKeyDisappeared, SurvivorAppeared, SurvivorDisappeared, VisibleAssignmentAppeared, and VisibleAssignmentDisappeared. In R2, add separate annotation-value-change events. A transition event represents a membership boundary crossing, not every numeric counter change.

On a native insertion, create/update the occurrence record, test each child key, and insert into S_v only if all children are satisfied. On a child-key transition, use the reverse separator index to visit exactly the matching native records and adjust one child's support state. On an S_v transition, update the parent projection count and, if relevant, the E_v count. Propagate further only on the corresponding zero crossing. Deletion must use the matching inverse transition and retain any records needed by active cursors until the epoch completes.

Generalized nodes receive child-key transitions; they do not accept externally inserted tuples. Their candidate key set is bounded by the union of child support keys. Reclaim keys whose child-presence count becomes zero. Do not construct Cartesian products at a generalized node.

Use an explicit work stack or queue rather than recursion tied to the host call stack. The schedule must be deterministic for debugging. Do not coalesce a positive and negative event if doing so changes the selected delta semantics. Each event records node ID, key/tuple ID, epoch, cause and transition polarity; trace payloads can be disabled in release mode.

6.4 Invariants checked in debug/reference mode

After each complete logical update, compare every S_v and P_v with a slow subtree evaluator on small data. Verify child counters, projection support counts, generalized intersections, E_v support, and empty-key behavior. Verify that index membership exactly matches the records it indexes, and that all tuple handles are live or intentionally pinned.

The storage invariant is proportional to native records and support keys for a fixed query, not to the number of full witnesses. Add instrumented limits on records per operator and cumulative support memberships. Repeated insert/delete churn must reclaim zero-support records and must not grow state with historical update count except for a declared allocator high-water budget or retained recovery log.

6.5 Bulk initialization and rebuild

Support two independently checked initialization routes. The first replays insertion updates from empty state and is the semantic baseline. The second builds occurrence tables, computes support bottom-up, and creates enumeration indexes directly. Compare their canonical states on the same data. An optional Yannakakis-style snapshot evaluator supplies an additional static reference and a rebuild path. P6

Bootstrap of a delta subscriber requires a consistent starting epoch and valid live views. For a validated connex subtree, use L_root = E_root and process its edges top-down with L_child = E_child semijoin L_parent, indexed on the separator; verify this against the reference global projection. This scans local support views rather than the entire potentially huge answer set. If the client requests an initial full snapshot, its output cost is still charged separately.

7. Enumeration and delta correctness

7.1 Current-result cursor

Build a generic N-ary cursor over local visible assignments in the connex subtree. It must enumerate Cartesian combinations lazily through a stack of child cursor states, reuse compiled variable-to-output mappings, and avoid materializing full intermediate joins. Nodes outside the connex subtree contribute existence support rather than hidden witness enumeration.

Provide fast empty detection, bounded startup to the first result, bounded advance to the next result, and bounded termination detection under the admitted index model. Measure all three delay components. Constant delay is a fixed-query claim: a row of |F| values still costs at least its width to emit.

Initially use one writer and explicitly pinned enumeration epochs. Either block updates while a snapshot cursor is open or reject them with a documented busy status. Do not mutate a cursor's underlying hash table silently. Later multi-version snapshots need their own memory/reclamation contract; they are not required to establish the first correct engine.

7.2 A separate pinned-assignment cursor

Delta enumeration needs to enumerate completions of a specific witness assignment, possibly including values outside the ordinary parent separator. Provide

enumerate_completions(subtree_or_fragment, fixed_assignment, snapshot_side)

where fixed_assignment is a typed partial assignment over all relevant variables, not just a parent key. Validate compatibility at construction and compile only the necessary key lookups. The cursor must retain the witness restriction while enumerating descendants and other fragments.

This is an implementation audit item in P1's Algorithm 6: passing only the parent separator can lose the identity of a root witness because the root separator is empty. For a one-relation full query, inserting a new row must emit that row only, not all old rows. The explanatory text and example indicate a pinned completion operation; the code interface should make it explicit. P1, Section 5.2

7.3 Projection changes are not projected witness changes

In general,

[
\Delta(\pi_X S)\neq\pi_X(\Delta S).
]

For Q(x):R(x,z), after inserting (a,1), inserting (a,2) changes the witness set but not the answer. Deleting either witness while the other remains also produces no set delta. Therefore witness discovery at a projected node must consume the zero crossings of its support-counted E_v, rather than blindly projecting all S_v changes.

P1's Section 5.2 contains a projection/delta equality that must not be used as a general programming identity. This observation does not negate the goal of constant-delay CROWN enumeration; it identifies a concrete semantic condition that the implementation and its proof must handle. Keep the one-relation collision case, multi-level hidden branches, and multiple changed witnesses for the same visible assignment in every delta regression run.

7.4 Old/new state and deletion scheduling

Give each logical update an explicit state journal with stable handles to the affected before and after records. Insertion witnesses are interpreted against the appropriate pre-update outside context and post-update surviving combinations. Deletion should be implemented as a precisely specified reverse transition, with surviving outside context or an equivalent proven ordering. Do not reuse old live membership for all changed nodes without proving that the resulting witness sets are disjoint.

A minimal regression is Q(x,y):R(x),S(x,y), initially containing R(a),S(a,b). Delete S(a,b). If both the disappearing child and disappearing root are selected against the same old live context, a naive implementation can emit the same deleted output twice. The required result is exactly one deletion.

Task D03 must write a step-by-step transition specification for insertion and deletion, prove soundness/completeness/disjointness of the selected delta fragments, and state when each live-view modification becomes visible. The specification is an integration gate. An implementation that obtains correct final snapshots but incorrect deltas does not pass it.

7.5 Live-view lifecycle and backpressure

The paper's delta method updates live information during delta enumeration. Therefore abandoning a cursor is not automatically harmless. The first production contract should serialize a logical update with completion of its internal delta maintenance. A client may consume, pause, or discard output, but discard must still execute the necessary internal completion work. A later update must not see stale live state. P1, Section 5.2

Expose pending_delta, draining, and ready states. Provide bounded output buffers, a sink cancellation policy, and a deterministic error if the caller attempts an incompatible operation. If the client disconnects, the engine either completes internal draining without delivery, persists a resumable epoch, or rolls back; each option needs an explicit contract. It must not drop the cursor and continue as if all live state had been maintained.

Keep maintenance-only mode separate. It need not maintain delta-only live state. Switching into delta mode requires a validated live-state bootstrap at a barrier. Report propagation time, internal delta drain time, serialization time, and sink wait time separately.

7.6 Self-joins and physical updates

Maintain one logical occurrence per alias, with a map from each physical base table to all occurrences and their adapters. A physical set insertion is applied as a deterministic sequence of occurrence insertions inside one logical epoch. For positive CQs, this sequence is monotone: each intermediate answer can only be added, so the true set deltas from the steps are disjoint. The corresponding argument holds for same-sign deletions. This includes combinations using the newly inserted tuple in more than one occurrence.

Drain each internal step according to the delta lifecycle while keeping intermediate database states invisible to public snapshots. Internal delta fragments must go to an unpublished epoch spool or a sink with transactional begin/commit/abort; snapshot invisibility alone does not prevent partial output from escaping. Publish the epoch only after every affected occurrence succeeds, and discard or abort unpublished output on failure. Use bounded memory with spill or backpressure, and account for output-sensitive spool space and I/O. If eager spooling is selected, public first-result latency includes completing that epoch's staged enumeration; it must not be described as constant-delay startup. A transactional sink may consume tentative records, but only a committed epoch is public. A later design that preserves lazy public output without eager staging needs its own state/version and failure argument.

A loop edge in a self-joined graph is a mandatory test because it exposes new–new cross terms. Same-scope aliases, different local predicates on aliases, and physical projection duplicates need separate fixtures. Inject a failure after any internal occurrence and verify that no partial logical epoch is visible to either snapshots or sinks.

The monotonicity argument does not cover a mixed insert/delete batch or an old-row/new-row replacement. Those operations require the next section's explicit batch contract.

8. Operational system components

8.1 Transaction and batch semantics

R1 guarantees atomic visibility for one physical set update, including its self-join occurrence fan-out. Input files may contain many such committed events. A throughput batch is initially a transport batch of ordered logical events, not an atomic net-change transaction.

R2 adds a separate atomic-batch API. Choose between an event stream that exposes the ordered individual deltas and a net-transaction stream defined by the before/after database. For net semantics, opposite changes must cancel, same-sign changes must consolidate correctly, and the public sink must not observe an intermediate result. A consolidation dictionary may be proportional to intermediate emitted deltas, not just final net output; report that resource use. Do not claim the single-tuple delay bound for arbitrary atomic batches without a separate argument.

UPDATE of a physical row is an atomic replacement contract, not an undocumented delete followed by insert visible to clients. Schema changes use barriers and invalidate affected plans; online schema migration is a later feature.

8.2 Input adapters and windows

Start with a documented JSONL or binary update format containing schema version, base table, operation, typed values, sequence number, and optional source position. Add CSV loading and trace adapters for the legacy experiments. CDC, Kafka and Arrow/Parquet adapters can follow through the same ingestion interface; they should not enter core operator code.

For event-time windows, store event timestamps and watermark policy separately from processing order. Expiration generates normal deletions. Define late-event acceptance, retraction and duplicate-delivery behavior. A FIFO proof assumption refers to the actual update/lifetime order required by its theorem, not merely to the existence of a timestamp column. Monitor declared patterns and downgrade guarantees or reject a violating event according to policy. P4

8.3 Checkpoints and recovery

Version checkpoint manifests with the engine format, catalog, plan hash, arithmetic policy, last committed input position, output epoch position, and checksums. Serialize dictionaries, base/occurrence state, required support/index state, and delta lifecycle state or enough information to rebuild it. Never serialize process addresses.

Use a write-ahead input journal and clear commit/barrier records. A crash in the middle of occurrence fan-out or delta draining must recover to a documented epoch boundary and replay deterministically. Test every persistence boundary. A simple first implementation may checkpoint only at quiescent boundaries and replay an interrupted epoch from its beginning.

An external sink requires its own delivery protocol. An idempotency key such as (query_id, epoch_id, ordinal) can support deduplication only when replay preserves the output order. Hash-table iteration may change after reconstruction; retain the necessary ordering/seed/cursor information or use another audited event identity. Charge any canonical sorting or durable buffering. Do not promise end-to-end exactly-once behavior unless the sink participates in a transactional or idempotent protocol. Keep a durable local sink as the first fully testable integration.

8.4 Concurrency and resource ownership

Use one state-mutating thread per query initially. This makes update ordering and cursor correctness inspectable. Parallel input decoding, independent queries, or output encoding can be added without parallelizing support mutation. Sharing base storage across queries is useful, but each query's state and resource budget remain explicit.

Parallel operator maintenance, distributed partitioning, and multi-version reads require separate protocols for ownership, synchronization, cross-partition keys, duplicate deltas, barriers and recovery. Do not inherit the legacy Flink partitioning scheme as an unexamined property of the native engine.

8.5 CLI, observability and explainability

The first public interface is a CLI and an embeddable library. A web interface is optional. Suggested commands are compile, explain, validate-plan, run, snapshot, checkpoint, restore, verify-trace, and benchmark. Every example should run using only SQL, a catalog file and input data.

EXPLAIN should show the normalized occurrences/head, recognized class, native/generalized tree, separators, connex subtree, native height, exactness status, source/certificate of the height result, estimated state, required indices, update assumptions, arithmetic policy, enumeration mode and cost-search status. Export JSON and DOT/SVG for inspection. Keep plan visualization read-only with respect to semantics.

Metrics should include base tuples, surviving tuples, projected keys, visible assignments, allocated/live bytes, support transitions, visited reverse-index records, annotation changes, output count, cursor startup/advance/end times, queue occupancy, drain duration, sink wait, checkpoint bytes/time, and replay length. Expose a sampled per-update causal trace for debugging. Do not require per-tuple string formatting in optimized runs.

9. Cost-based optimization

9.1 Three independent decisions

Separate structural admissibility, structural optimality and cost selection. The tree verifier decides whether a plan is valid. The height solver determines h* or a certified interval. The cost optimizer ranks valid plans within the requested policy. A cost estimate cannot excuse an invalid tree, and a low-height certificate does not prove low execution cost.

Define a CandidateProvider interface with a declared family, completeness status, lower bounds, resumable search state and candidate provenance. Initial providers are the exact generalized-tree enumerator, audited special cases, and validated ear-based candidate generation. Later providers include meta-decompositions, restricted rewrites, and specialized backends.

9.2 Start with an interpretable model

A first baseline is the paper's update-weighted native depth score, with update frequencies measured per occurrence/base relation. Keep this baseline for ablations even after introducing a richer model. Minimum height remains the primary objective in the default policy. P1, Section 6.3

The next model estimates work by event and index activity. For each physical relation r, operation type o, and plan T, estimate input rate u(r,o), the number of support events induced on each edge, and the event-weighted size of the parent buckets touched. One update may create several distinct transitions on the same edge. A useful shape is

[
\widehat C_{prop}(T)=\sum_{r,o}u(r,o)\sum_{c\to p}
\widehat{\mathbb E}!\left[
\sum_{\eta\in Events_{c\to p}(r,o)}
\left(c_{lookup}+c_{touch}|bucket_p(\eta.key)|\right)
\right].
]

Here the event multiset covers one physical update, including all affected self-join occurrences. Expected event count times event-weighted mean cost is a practical approximation; probability of at least one event alone is insufficient. Add measured costs for local adapters, base-index updates, visible-projection updates, annotation changes when enabled, snapshot demand, delta enumeration, serialization and checkpoints. Put state memory under an explicit budget; do not add bytes to nanoseconds without a stated conversion/penalty policy. Maintain a vector of estimated latency, throughput cost, memory and output costs before collapsing it to a configured objective.

Collect NDV, separator degree distributions, heavy keys, projected support multiplicities, zero-crossing rates, insertion/deletion mix, per-relation rates and local predicate selectivity. Conditional distributions matter: an average bucket size over all keys can be a poor estimate for the keys that actually change. Record confidence/sample size and an unknown-statistics fallback.

Enclosureness is a useful analytical interpretation, but exact future tuple lifetimes are not available to an online optimizer. Use observed proxies or replay estimates and label them accordingly. Do not claim that a static join cardinality estimate computes the future maintenance cost.

9.3 Connection to meta-decompositions

P3 gives a compact representation of ordinary join trees and a framework for width-one static plan optimization. Its local optimization is exponential in unbounded fan-out; Section 5.3 explicitly allows a heuristic when that search is too large. Its objective is based on static intermediate cardinalities, not CROWN support-event work. P3

Implement a separate adapter that maps meta-decomposition candidates into the engine's typed tree/plan interface. Before claiming complete minimum-height search, establish that the mapping covers generalized scopes, rooting, output boundaries, and all relevant CROWN plans. Ordinary join-tree enumeration alone misses height-one generalized-root examples.

The first useful integration can be heuristic: supply valid candidates, certify their height through the independent height mechanism, and measure their costs. A later dynamic program needs an explicit state containing the boundary/separator, available head variables, generalized/native status, height budget, required indices, and any statistics-dependent cost context. Prove optimal substructure for the selected cost model; many conditional update costs are not additive across arbitrary subtrees.

Do not claim global cost optimality when the provider, fan-out search, or physical-layout choices are incomplete. EXPLAIN should say, for example, “minimum height proved; cost best among 83 validated candidates; high-fan-out local order heuristic.”

9.4 Reoptimization

Implement static plan choice at query creation first. Next allow explicit reoptimization at a quiescent checkpoint. Build the new state from a consistent base snapshot, validate its results, catch up through the ordered log, and switch at a barrier. Do not migrate half-updated support tables in place as a first implementation.

Charge rebuild and migration work. Use hysteresis and a payback estimate so small cost-model fluctuations do not cause repeated rebuilds. A continuously adaptive optimizer is a later feature, after the static model demonstrates useful rankings on held-out traces.

10. Bags, aggregates and research extensions

10.1 Separate support from annotation value

R2 introduces annotation policies with exact operations, zero/equality semantics, overflow policy, and a deletion/replacement strategy. A support event and an annotation-value event are different. For example, a key whose multiplicity changes from two to three remains present, but its COUNT contribution changes. Conversely, a SUM may become numerically zero while its group still exists.

Use positive multiplicities to track SQL row/group existence and separate values for SUM or other payloads. Do not use sum == 0 to delete a SQL group. Do not inherit epsilon-based presence from approximate infrastructure. Do not promise arbitrary-semiring support merely because the API has add and multiply; zero divisors, cancellation, deletion and representation cost can change enumeration and maintenance behavior.

10.2 Weighted subtree messages

For supported exact nonnegative multiplicities, a natural weighted message specification is

[
A_v(k)=\sum_{t\in R_v:\ t[K_v]=k}w_v(t)\prod_{c}A_c(t[K_c])
]

at a native node. At a generalized node, first compute a value on the complete generalized scope, then aggregate to the parent separator:

[
W_v(s)=\prod_c A_c(s),\qquad
A_v(k)=\sum_{s\in S_v:\ s[K_v]=k}W_v(s).
]

The second step matters when a generalized scope such as {x,z} sends a message to {x}. Parent messages are defined for nonroots; an optional root summary uses an explicit empty-key convention. Use these equations as semantic specifications before designing incremental updates. A change to a nonzero message value must propagate even when its support does not change. Thus the Boolean insertion-only maintenance argument does not automatically give constant update time for these values.

Enumeration must avoid multiplying subtree messages twice. If a child is explicitly enumerated in the connex subtree, its full message must not also be multiplied into the parent's emitted local annotation. Define local factors from the native weight and hidden/outside-connex child messages, sum over local hidden variables, and combine each visible factor exactly once. Prove this factorization for generalized nodes as well as native nodes. A two-level counted path with several witnesses per separator is a mandatory overcounting test.

For a bag cursor, specify whether it emits (tuple, multiplicity) or repeats each tuple. These have different output sizes. Aggregate change output should use before/after values or a declared signed arithmetic delta; SQL group deletion is a separate state change. For exact COUNT, choose checked integer arithmetic with explicit overflow errors, or an arbitrary-precision mode whose bit cost is reported. Decimal SUM needs scale/rounding rules. AVG maintains sufficient statistics rather than averaging previous averages.

The scalar product equations above specify multiplicities, not arbitrary SQL SUM expressions. A supported numeric payload needs separate sufficient statistics and audited combine rules, for example count/sum pairs for an admitted one-relation payload. Cross-relation aggregate expressions require an explicit derivation or a costed fallback. SQL scalar aggregation also differs from group membership: on empty input, COUNT(*) without GROUP BY returns one zero-valued row, while scalar SUM/AVG return one NULL-valued row; an ordinary grouped query has no row for a vanished group.

10.3 Extension priority and gates

Extension

Priority

Required work before automatic selection

PK/FK and static-table specializations

After core correctness

Verify/enforce constraints; retain behavior under updates to referenced keys; identify theorem preconditions P5

FIFO and mixed-pattern planning

After baseline statistics

Pattern checker, violation policy, independently audited structural reduction and compatible-tree proof; no certificate from Trim/MixDetect acceptance alone P4

Heavy/light star backend

Research R3

Check query/head conditions and enumeration delay; P2's stated delay is not uniformly constant for projected stars

Snapshot top-k

R3 after exact aggregation

Ranking algebra, ties, projection/multiplicity semantics, static comparison against the native snapshot P10

Dynamic top-k

Separate research task

State maintenance and update proof; a static top-k bound is insufficient

Cross-relation comparisons

R3

Comparison structure, supporting tree, predicate indexes, distinct guarantees and dynamic proof P9

Acyclic non-free-connex queries

Explicit fallback

Correct projected duplicates; no borrowed constant-delay guarantee

Cyclic queries/GHD

Explicit fallback

Bag materialization costs, boundary consistency, width/state accounting and independent tests

SQL difference/negation

Later

Separate set/bag difference semantics and dynamic maintenance P11

Approximate aggregation

Opt-in research backend

Error contract, numeric stability, insertion/deletion restrictions, statistical validation P12

General annotations/provenance

Separate algebra audit

Capability checks, representation growth, support/nonzero distinction, full-text verification of relevant new results P13

Generated/specialized execution

After generic runtime measurements

Same plan and trace corpus as the interpreter; compile cost and cache invalidation

Multi-query shared state

After single-query reliability

Sharing keys include predicates, semantics and epoch; reference counts and resource attribution

Parallel/distributed runtime

Last major systems stage

Partition ownership, skew, cross-partition consistency, output deduplication and recovery

The extension registry should expose supports(query, semantics, update_contract, output_contract) -> admission_result, together with a guarantee profile. The optimizer can choose only an admitted backend. Every fallback must be visible in the plan.

11. Detailed coding-agent work breakdown

Each task below has a stable ID, dependencies, concrete artifacts, and an acceptance condition. A task may be split into smaller pull requests, but its acceptance condition must not be weakened. Dependencies refer to verified interfaces; an implementation team may parallelize work against agreed stubs. None means no implementation dependency, not permission to ignore the semantic contract.

11.1 A — Foundations and independent references

A01 — Select the native language and establish the build

Depends: None. Artifacts: decision record, CMake presets, dependency lock, minimal library/CLI/test targets, toolchain matrix. Establish C++23 as the default, verify the parser dependency in a small build, and document the alternative Rust decision if selected. Add warning policy, debug/release/sanitizer builds and deterministic test invocation. Acceptance: a clean checkout builds and runs one library test and CLI smoke command on the supported Linux environment; a second compiler build is recorded. No runtime design depends on an accidental local package.

A02 — Pin and document source baselines

Depends: None. Artifacts: source_baselines.md, component provenance/licensing record, legacy environment manifests. Pin the two reviewed repository commits and paper versions; list relevant source files, commands and supported modes. Record the new project's license decision before copying components. Acceptance: every reused file/design and comparison executable has provenance; source inspection, successful build, and reproduced experiment are different status fields.

A03 — Freeze semantics and feature admission

Depends: A01. Artifacts: semantics.md, sql_support.md, typed update/output contracts, feature matrix. Decide set no-op behavior, source row identity, Boolean results, batch mode, NULL boundary, arithmetic failures and cursor ownership. Acceptance: the contract determines exact expected behavior for all mandatory cases in Section 13; unresolved semantics are not hidden behind parser support.

A04 — Build an independent exact relational oracle

Depends: A03. Artifacts: slow CQ evaluator, before/after delta evaluator, canonical exact-result format. Implement direct joins and projection using simple data structures; correctness is more important than speed. Keep this evaluator independent of production support propagation, tree construction and cursor code. Acceptance: hand-calculated singleton/path/self-join examples match; exact sets and, later, arbitrary-precision multiplicities are compared without floating tolerances.

A05 — Build trace/query generators and failure shrinking

Depends: A04. Artifacts: seeded generators, trace format, shrinker, regression fixture registry. Generate shapes independently of the production planner and valid/invalid updates under declared policies. Preserve failing SQL, normalized CQ, seed and minimal trace. Acceptance: an intentionally injected projection or duplicate-delta bug is found and reduced to a small counterexample; generator validity is itself checked.

11.2 F — Catalog, SQL frontend and logical IR

F01 — Implement the catalog and scalar semantics

Depends: A03. Artifacts: catalog API/schema, typed values, comparison/hash rules, schema versioning. Distinguish enforced constraints from statistics and user hints. Implement the initial integer/string/date/decimal subset with deterministic equality. Acceptance: incompatible casts, ambiguous names and unsupported collations fail clearly; equal values hash consistently; no nullable value enters classical equality joins through an undocumented rule.

F02 — Wrap the SQL syntax parser

Depends: A01. Artifacts: libpg_query wrapper, owned syntax representation, parser-error mapping. Pin the parser version and isolate allocation/freeing. Retain source locations and reject malformed multi-statement inputs according to the API. Acceptance: parser memory is released on success and failure; comments/quoted identifiers/aliases/composite expressions produce stable AST fixtures; parser success alone does not mark a query admitted.

F03 — Implement binding and SQL desugaring

Depends: F01, F02. Artifacts: resolved SQL IR, name scopes, expansion of *, USING, NATURAL JOIN, aliases and the Boolean wrapper. Preserve output order and repeated columns. Acceptance: an ambiguous column produces a useful source diagnostic; natural joins use the declared catalog; two aliases of one base table retain distinct occurrence identities.

F04 — Normalize equality CQs and local adapters

Depends: F03. Artifacts: union-find normalization, constant/contradiction rules, local predicate IR, occurrence-to-base routing. Keep casts and NULL checks before equality merging. Support repeated variables and physical projection duplicates through derivation counts. Acceptance: SQL and hand-written CQ IR agree under A04; no distinct mutable atom disappears through scope containment; cross-relation comparisons remain rejected or explicit.

F05 — Version and validate CQ/plan schemas

Depends: F04. Artifacts: deterministic JSON schemas, canonical hashes, schema upgrader/rejection rules. Serialize variable sets, occurrence IDs, output mapping, local filters and semantics independently of in-memory addresses. Acceptance: round-trip preserves semantics; reordered textual aliases yield the intended canonical equivalence; unknown mandatory fields or incompatible versions fail rather than default silently.

F06 — Implement admission diagnostics and SQL integration tests

Depends: F05, P01. Artifacts: structured admission result, SQL support test corpus, diagnostic examples. Differentiate parser failure, semantic error, cyclic body, non-free-connex head, unsupported semantics and resource exhaustion. Acceptance: every query in the support matrix either compiles to the correct class or produces the documented reason; unsupported plain bag SELECT is never silently converted to set mode.

11.3 P — Structure, exact planning and proof artifacts

P01 — Recognize alpha-acyclicity and free-connexity

Depends: F05. Artifacts: GYO recognizer, reduction witness, failed-core diagnostic, H/H+F classification. Keep occurrence identities even when scope comparisons use sets. Acceptance: an independent small structural enumerator agrees; projected endpoint path is rejected as non-free-connex; adding the synthetic head edge never creates a runtime answer table.

P02 — Implement the independent tree verifier

Depends: F05. Artifacts: Cover/Connect/Guard/Above checker, maximal-connex traversal, native-height computation, standalone validate-plan. Deliberately avoid calling constructor helpers for the essential checks. Acceptance: valid hand-authored plans pass and individually corrupted properties fail with a node/variable witness; empty head, empty separator and duplicate scopes work.

P03 — Implement the finite complete tree oracle

Depends: P02. Artifacts: normalized-tree enumerator, complete scope universe, height feasibility search, proof note for generalized contraction. Use the m−1 bound and all relevant native-scope subsets, not only scopes appearing as pairwise separators unless that restriction is proved. Acceptance: oracle minimums match analytic fixtures, including the height-three residual counterexample; enumeration is deterministic and timeout status never means infeasible.

P04 — Implement safe fast paths and exact search improvements

Depends: P03. Artifacts: singleton/constant/disconnected handling, q-hierarchical recognizer and height-one construction, symmetry reduction and branch-and-bound. Each pruning rule includes a reason it cannot remove all optima. Acceptance: each fast path agrees with P03 on all feasible small instances; heuristic lower estimates cannot prune; query arity/variable count have no hardcoded semantic limit.

P05 — Audit and repair residual-based candidate construction

Depends: P02, P03. Artifacts: frozen-ear layers, anchor metadata, candidate reconstruction, proof-status report. Include mutual-ear representatives, induced heads, restored output variables and generalized-node grafting. Treat Section 5.3's counterexample as mandatory. Acceptance: every emitted tree passes P02; the counterexample is never certified as height two. A complete optimized minimum-height claim requires a corrected argument and independent checks; otherwise this module remains a candidate provider.

P06 — Implement exactness evidence and search budgets

Depends: P03, P04. Artifacts: lower/upper-bound records, exhaustive or solver-proof evidence, resumable search, strict/best-found policies. A valid incumbent and a proved optimum use different result types. Acceptance: deliberately interrupting search yields an honest bound interval; strict mode refuses to mislabel an incumbent; certificate corruption is detected independently.

P07 — Enumerate and cache alternative admissible plans

Depends: P04, P05, P06. Artifacts: CandidateProvider interface, plan canonicalization, duplicate suppression, minimum-height filter. Preserve provenance and completeness scope. Acceptance: CBO can request several distinct valid plans of the proved minimum height; candidate caching cannot mix catalogs, heads, update modes or arithmetic policies.

P08 — Lower validated trees to physical plans

Depends: P02, F05, S01. Artifacts: compiled tuple/key projections, index requirements, node/event wiring, enumeration program, GuaranteeProfile. No manually registered query classes. Acceptance: the same lowering handles native roots, generalized roots, arbitrary fan-out, hidden branches and empty keys; invalid/unverified plans cannot reach the executor accidentally.

11.4 S — Storage and native indices

S01 — Define typed IDs, layouts and key projection programs

Depends: F01, F05. Artifacts: relation/occurrence/node/tuple IDs, layout descriptors, tuple and key hashing. Compile column projections once. Acceptance: composite/reordered/empty keys are exact; no string field-name lookup is needed in the inner loop; types with equal textual representations remain distinct when semantics require it.

S02 — Implement a simple reference storage backend

Depends: S01. Artifacts: primary tables, separator buckets and live iteration using standard containers. This is the first runtime backend and the comparison target for optimized storage. Acceptance: randomized index operations match an independent map-of-sets model; duplicate/absent operations and key deletion are correct.

S03 — Implement tuple arenas and stable handles

Depends: S02. Artifacts: allocation/reclamation API, generational handles, noncopyable owning state, string/dictionary ownership. Define pinned-record retention. Acceptance: sanitizer runs cover churn, clear, destruction and handle reuse; stale handles fail in debug mode; counters and free lists remain consistent after failed allocations.

S04 — Add optimized primary and secondary indices

Depends: S03, A02. Artifacts: audited/adapted native index backend, collision handling, bucket iterator contract. Keep exact support membership independent of payload arithmetic. Acceptance: differential tests against S02 pass; integer counts above floating-point exact range remain exact; no epsilon check decides key presence; iterator traversal visits live records only.

S05 — Enforce capacity, overflow and memory accounting

Depends: S03, S04. Artifacts: checked support counters, per-query memory budget, allocation statistics, failure/rollback behavior. Distinguish live bytes, reserved bytes and historical logs. Acceptance: configured overflow/out-of-memory failures leave a valid previous epoch; repeated no-op/churn updates do not leak logical state; memory reports reconcile with operator record counts.

11.5 R — Support maintenance and initialization

R01 — Implement native node support maintenance

Depends: P08, S02. Artifacts: insertion/deletion, satisfied-child state, reverse separator lookup, survivor membership. Begin with simple storage. Acceptance: every node's survivors match subtree reference evaluation after each update on small traces, including updates to an internal native node and partial child support.

R02 — Implement generalized intersection nodes

Depends: R01. Artifacts: child-presence counts, candidate union, exact intersection support, empty-scope handling. Never accept external writes to generalized nodes. Acceptance: three-or-more-child intersections, last-child loss and empty-key truth work; zero-presence candidate keys are reclaimed; no Cartesian intermediate is allocated.

R03 — Implement parent and visible projection counts

Depends: R01, R02. Artifacts: P_v and E_v, zero-crossing events, stable visible-assignment buckets. Keep their schemas and counts separate. Acceptance: hidden witness collisions, multiple physical derivations, root projections and Boolean queries match A04; only genuine membership transitions propagate.

R04 — Implement the event scheduler and epoch journal

Depends: R03, S03. Artifacts: deterministic work queue/stack, before/after event values, exactly-once internal application, affected-record journal. Avoid call-stack limits and unbounded string logs. Acceptance: alternate valid schedules produce the same committed state; each event is accounted once; failures preserve recoverable state and deleted rows remain alive while required.

R05 — Implement physical-base routing and self-join updates

Depends: F04, R04. Artifacts: occurrence adapters, atomic logical epoch, deterministic alias order, output-staging hooks for D06/O06. Apply same-sign occurrence changes with correct cross terms and public visibility. Acceptance: loop-edge and multi-alias tests match full recomputation after each physical event; no intermediate alias state is observable; integrated delta tests show no duplicates or partial output after an injected alias failure.

R06 — Implement bulk build, rebuild and invariant inspection

Depends: R04, R05. Artifacts: replay loader, direct bottom-up build, state dump/checker, live-view bootstrap. Compare initialization methods. Acceptance: direct build and insertion replay produce equivalent canonical state/results; state size follows support records; a corrupted counter is localized by the invariant checker.

11.6 D — Snapshot and delta enumeration

D01 — Implement generic current-result cursors

Depends: R03, P08. Artifacts: N-ary cursor stack over E_v, output assembly, empty-result handling, epoch pinning. Use a lazy product over child cursors. Acceptance: no duplicates after projection; three/eight-child and disconnected products match A04; startup, per-result and termination operation counts are measured separately.

D02 — Implement pinned-assignment fragment cursors

Depends: D01, R04. Artifacts: typed fixed-assignment bindings, subtree/fragment traversal, before/after snapshot selection. The API must accept more than a parent separator. Acceptance: a root witness with an empty separator emits only its completions; ancestor/child bindings remain consistent; deleting a referenced row does not invalidate its pending before-state cursor.

D03 — Specify and audit the exact projected delta algorithm

Depends: R03, R04, D02, A04. Artifacts: insertion/deletion transition specification, witness partition proof, liveness state machine, complexity ledger. Address actual E_v changes, old/new outside context, witness disjointness and empty deltas. Acceptance: an independent reviewer can trace every output exactly once; the projection-collision and ancestor/child deletion examples pass on paper and in the reference model. Do not treat this task as pseudocode transcription.

D04 — Implement exact delta output against the oracle

Depends: D03. Artifacts: witness selection, lazy completion cursors, live-view updates, deletion journal retention. A conservative eager-live implementation may be a labeled correctness baseline, with its linear rebuild/scan cost recorded. Acceptance: after every generated update, emitted additions/deletions equal the exact before/after difference, not just the final snapshot; no missing/duplicate output on an empty delta.

D05 — Establish the intended lazy output and complexity contract

Depends: D04. Artifacts: optimized scheduling, bounded-work cursor transitions, proof-to-counter mapping. Charge live-state/witness discovery and journal work. Acceptance: constant-delay claims include first/last steps and are justified by the admitted structure; required full scans are either removed or reflected in the guarantee profile; correctness matches D04 under the same traces.

D06 — Implement cancellation, draining and mode changes

Depends: D04, D05. Artifacts: cursor ownership states, pause/resume/discard, bounded buffers, mode-switch barrier. Finish required internal work before the next update. Acceptance: pausing after any output, discarding, disconnecting, or encountering a sink error leaves a documented recoverable state; a subsequent update matches the oracle. Maintenance-only and delta-maintained modes remain distinguishable.

11.7 O — Ingestion, recovery and operational interfaces

O01 — Implement input codecs and ordered replay

Depends: F01, R05. Artifacts: update JSONL/binary codec, schema-aware CSV loader, sequence/position validation, legacy trace adapters. Keep physical row identity and value parsing explicit. Acceptance: malformed rows do not partially update state; identical ordered streams produce the same epoch sequence; adapters preserve signs, relation names and types and do not silently skip unsupported legacy operations.

O02 — Implement the query/session lifecycle

Depends: D06, O01. Artifacts: create/start/pause/snapshot/drain/stop/drop APIs and resource ownership. One writer owns a query's mutation state. Acceptance: every API call in each lifecycle state either succeeds with documented behavior or returns a precise error; stop/drop releases pinned rows and buffers without exposing a partially completed update.

O03 — Implement transport batches, windows and optional atomic batches

Depends: O02, A03. Artifacts: ordered-event batching, expiration queue, watermark/late-event policy, separately typed net-batch API for R2. Do not coalesce updates across observable barriers. Acceptance: R1 individual-event results match their reference definition; enabled window policies withdraw FIFO labels or reject actual order violations. The optional R2 net-batch API must additionally match before/after transaction semantics and handle insert/delete cancellation correctly.

O04 — Implement versioned checkpoints

Depends: R06, O02, S05. Artifacts: manifest, pointer-free state serialization, checksum verification, quiescent barrier, format compatibility rules. Include catalog/plan/arithmetic/source positions. Acceptance: restore produces the same exact state/results and next-update behavior; corrupted/truncated/wrong-version checkpoints fail safely; repeated checkpointing respects resource budgets.

O05 — Implement WAL and deterministic recovery

Depends: O04, R04. Artifacts: ordered input journal, commit markers, replay, interrupted-epoch handling. Define persistence ordering and log truncation only after durable checkpoints. Acceptance: crash injection before/after each write boundary recovers to the specified visible epoch; self-join fan-out is never recovered half-applied; replay output uses the documented deduplication protocol.

O06 — Implement sinks and bounded backpressure

Depends: D06, O05. Artifacts: in-process sink, durable local sink, output epoch IDs, unpublished epoch spools or transactional sink protocol, bounded queues, cancellation/error protocol. Separate result production from delivery. Acceptance: slow/disconnected/retrying sinks do not corrupt live state; failed occurrence fan-out exposes no partial epoch; memory remains bounded by configuration with spill/backpressure costs reported; delivery guarantees are demonstrated for each sink rather than inferred from WAL alone.

O07 — Implement EXPLAIN, metrics and diagnostic traces

Depends: P06, P08, R04, D01. Artifacts: human/JSON EXPLAIN, tree export, metrics registry, sampled causal trace. Expose height evidence separately from cost search. Acceptance: every benchmark mode can be identified from the report alone; operation counters reconcile with a short hand-traced update; instrumentation can be disabled without changing results.

O08 — Publish the CLI and embeddable API

Depends: O02, O06, O07. Artifacts: commands from Section 8.5, versioned public headers, examples, error codes, installation instructions. A server wrapper may follow but is not necessary for R1. Acceptance: a new user can compile an unseen supported SQL query, load updates, inspect a plan, consume results, checkpoint and restore without editing C++ or registering a query class.

11.8 C — Statistics and cost-based planning

C01 — Collect useful statistics with bounded overhead

Depends: O07, R04. Artifacts: cardinality/NDV/degree summaries, heavy keys, projection support distributions, update rates and zero crossings. Define sampling/update costs and reset/version policies. Acceptance: statistics agree with exact small-data counts; collection overhead and memory are measured; unknown or stale values are explicit.

C02 — Implement height-constrained baseline plan ranking

Depends: P07, C01. Artifacts: height-only, update-weighted-depth and simple memory-aware policies. Filter by the required certificate before ranking. Acceptance: the selected plan has the proved required height; a hot-relation trace can change ranking without changing semantics; every score is reproducible from recorded inputs.

C03 — Implement the maintenance cost model

Depends: C01, D05. Artifacts: conditional bucket/transition estimates, calibrated event costs, full/delta-output demand model, confidence fields. Separate observed facts from model assumptions. Acceptance: the model produces a decomposed estimate for each candidate; annotation events are not charged as support events; memory is a declared budget or normalized penalty.

C04 — Add a meta-decomposition candidate adapter

Depends: P07, C02, A02. Artifacts: source-grounded adapter, ordinary-to-CROWN mapping, family coverage report, local exact/heuristic status. Include generalized-node and head constraints explicitly. Acceptance: every candidate passes P02; no ordinary-tree-only result is labeled a globally minimum generalized tree; small-instance comparisons reveal any missing candidate families; unbounded-fan-out heuristics are reported.

C05 — Select physical plans under explicit policies

Depends: C02, P06, P08. Conditional dependency: C03 when the richer maintenance-cost policy is enabled. Artifacts: lexicographic default policy, optional cost policy, index-sharing/layout choices, fallback behavior, plan cache. R1 can use the C02 policies without C03. Acceptance: identical input/configuration yields identical choice; costs cannot bypass structural/semantic admission; timeout and stale-statistics behavior are visible; predicted memory respects budget or compilation fails honestly.

C06 — Implement barrier-based reoptimization

Depends: C05, R06, O05. Artifacts: snapshot rebuild, ordered catch-up, equivalence check, atomic plan switch, hysteresis/payback policy. Retain rollback to the old plan until the switch completes. Acceptance: outputs and epochs match a non-switching reference through changes in plan, rates and data; rebuild cost and temporary dual-state memory are included.

C07 — Validate ranking on held-out traces

Depends: C05, B03. Artifacts: train/calibration/evaluation split, regret report against measured feasible candidates, estimate-error analysis for implemented policies. Include workload shifts and high fan-out. Baseline C02 ranking is sufficient for the R1 packet; evaluate C03/C04/C06 separately when enabled. Acceptance: the report distinguishes search quality, estimation quality and runtime quality; no claim of optimal CBO is based only on matching the model's own score.

11.9 W — Exact SQL bags and aggregates, R2

W01 — Define annotation capabilities and arithmetic policies

Depends: A03, R03, D03. Artifacts: separate support/payload types, exact integer and decimal policies, capability admission, overflow/replacement rules. Include group existence independent of aggregate value. Acceptance: weight changes without membership changes are represented; cancellation of SUM does not erase a live group; unsupported algebras cannot select a certified backend.

W02 — Implement weighted subtree message maintenance

Depends: W01, R04. Artifacts: exact sums/products, numerical-change propagation, deletion handling, weighted reference state. Support generalized intersections/products without epsilon arithmetic. Acceptance: messages match a direct weighted subtree evaluator after every update; zero/nonzero and nonzero/nonzero changes both propagate correctly; actual update work is measured rather than assigned the Boolean bound.

W03 — Implement projected bag enumeration

Depends: W02, D02. Artifacts: local visible factors, hidden-variable summation, tuple/multiplicity cursor, optional expanded bag cursor. Avoid counting a child subtree in both parent and child factors. Acceptance: projected multiplicities equal an arbitrary-precision oracle, including duplicate base rows, deep hidden branches and sole-output-root cases; output size is stated in the chosen representation.

W04 — Implement COUNT, SUM and AVG

Depends: W03, F04. Artifacts: aggregate binder rules, group state, sufficient statistics, aggregate change events and global-empty behavior. Define COUNT(*), COUNT(expr) and the admitted DISTINCT aggregates separately. Acceptance: SQL oracle agreement covers empty global aggregation, empty groups, NULL expressions, signed sums, large counts and deletion of the last row; AVG uses sum/count state.

W05 — Complete SQL NULL/type behavior and bag admission

Depends: W03, F06. Artifacts: documented NULL equality/grouping, expression/type support, plain SELECT bag semantics. Extend the frontend only for implemented runtime rules. Acceptance: comparison with a mature SQL engine uses the same casts, collation and types; equality NULLs do not match, while DISTINCT/grouping behavior is correct; set-mode fixtures remain unchanged.

W06 — Integrate aggregate transactions and recovery

Depends: W04, W05, O03, O05. Artifacts: atomic weight replacement, aggregate batch consolidation, checkpoint formats, rollback on arithmetic errors. Acceptance: interrupted updates and mixed batches recover exact multiplicities and aggregates; overflow errors cannot leave partially changed ancestor messages; bag/count/SUM delta formats are unambiguous.

11.10 X — Optional research and performance extensions

X01 — Add update-pattern-aware planning

Depends: C01, P07, O03. Artifacts: insertion/FIFO/mixed-pattern metadata, monitors, compatible-plan analysis, source/proof audit. Recheck any residual characterization affected by Section 5.3 before using it as a guarantee. Acceptance: only proved preconditions appear in the guarantee profile; a violating trace triggers the declared downgrade/rebuild/rejection path and remains semantically correct.

X02 — Add key-aware specializations

Depends: F01, R05, C05. Artifacts: PK/FK validation/enforcement, guarded rewrite rules, specialized event routing. Distinguish schema constraints from approximate statistical dependencies. Acceptance: updates to every relation, including referenced keys, preserve correctness; deliberately violated/untrusted constraints cannot enable an invalid elimination; the general backend remains a comparison route.

X03 — Prototype the heavy/light star backend

Depends: D05, S05, C05. Artifacts: exact structural/head admission, degree/H-index structures, rebalancing, delay profile and proof audit against P2. Acceptance: small-state results match A04; rebalancing preserves output; projected-head delay claims use the actual stated exponent rather than assuming constant delay.

X04 — Add comparison-aware query support

Depends: F04, P01, D03. Artifacts: comparison graph, supporting-tree checker, range/index operators and new cursor proof obligations. Start with a narrow explicitly admitted family. Acceptance: cross-relation predicates cannot pass as equality CQs; boundary values and deletion changes match a predicate-aware oracle; static CQC results are not advertised as dynamic guarantees without proof.

X05 — Implement snapshot top-k

Depends: W04, D01. Artifacts: ranking algebra, ties, result identity, top-k physical operator, static reference comparison. Acceptance: output equals sorting the exact small snapshot under the declared tie policy; query/ranking preconditions from P10 are checked; all dynamic maintenance claims remain separate.

X06 — Add explicit general-query fallback backends

Depends: F06, P08, O07. Artifacts: non-free-connex projected fallback and cyclic/GHD backend interface, state/output estimates and admission reasons. Begin with a correct conservative evaluator. Acceptance: correctness holds for cyclic and acyclic-non-free-connex fixtures, but EXPLAIN clearly changes the guarantee; no hidden deduplication or bag materialization is counted as constant-delay CROWN work.

X07 — Add optional approximate aggregation

Depends: W01, B03, A02. Artifacts: explicit approximate query syntax/options, error/deletion contract, DynaGox-based comparator, uncertainty validation. Acceptance: approximation cannot be selected for an exact request; exact/approximate reports use different result checks; insertion-only versus fully dynamic restrictions are enforced.

X08 — Add difference/anti-join through a separate contract

Depends: F06, D03, W01. Artifacts: set/bag difference semantics, structural admission, negative-dependency maintenance, retraction tests. Use P11 as a source for static structure and keep incremental work separate. Acceptance: EXCEPT, EXCEPT ALL, absent/present transitions and aggregate signed deltas are not conflated; no unsupported negation cycle is admitted.

X09 — Add specialization/code generation after profiling

Depends: B03, P08, D05. Artifacts: specialized key/layout/cursor code or compiled execution program, cache policy, interpreter comparison. Preserve the versioned physical plan. Acceptance: the same generated trace corpus agrees with the generic executor; compile latency, executable size and cache effects are reported; no query-specific handwritten registration returns.

X10 — Add multi-query shared state

Depends: O08, C05, S05. Artifacts: shared base/dictionary ownership, equivalence keys for filters/projections, reference counting and per-query budget attribution. Share only what has identical semantics and epoch visibility. Acceptance: creating/dropping/replanning one query cannot change another's results; shared setup cost is charged once and amortization is explicit in experiments.

X11 — Design and implement parallel/distributed execution

Depends: O05, O06, B03, X10. Artifacts: ownership/partitioning design, skew handling, barriers, cross-partition delivery and recovery. Start with independent-query parallelism before intra-query partitioning. Acceptance: partition counts and rescaling preserve exact deltas and snapshot epochs; replicated inputs are not double-counted; recovery tests span worker failure and backpressure. This is a separate project stage, not a small final optimization.

11.11 B — Benchmarks and reproducible evaluation

B01 — Build legacy comparison environments

Depends: A02. Artifacts: isolated pinned CROWN Scala and C++ baseline builds, small supported replay examples, build-failure records. Distinguish published-artifact reproduction from local modifications. Acceptance: each usable baseline has verified output on at least one tiny supported workload before its timing is used; unsupported operations are excluded explicitly rather than silently ignored.

B02 — Create the query/trace workload manifest

Depends: A05, F06. Artifacts: classified legacy queries, generated structural families, trace regimes, data licenses/checksums. Include all SQL needed to reproduce a run. Acceptance: every workload has semantics, head, structure, update contract, expected backend and output mode; a graph-query suite alone is not presented as all-free-connex coverage.

B03 — Implement the measurement harness

Depends: O07, O08, B02. Artifacts: controlled runner, timing boundaries, operator counters, memory and latency histograms, raw result records. Separate compilation, loading, maintenance, enumeration, encoding and sink wait. Acceptance: deliberately toggling output modes changes the report label; correctness is checked before timing; environment and repetitions are recorded; no fixed speedup is assumed.

B04 — Evaluate planner, runtime and optimizer separately

Depends: B03, C07, B01. Artifacts: ablations for storage, generic/specialized runtime, generalized nodes, height policy, cost model, stats and batching. Hold other factors fixed. Acceptance: claimed improvements can be attributed to a component; static versus dynamic and exact versus approximate comparisons are labeled; shared setup is not repeatedly charged to only one system.

B05 — Run adversarial scalability and memory experiments

Depends: B03, D05, S05. Artifacts: scale curves, fan-out/height/arity/skew stress, output-small/huge families, long churn runs. Measure internal operation counts as well as wall time. Acceptance: tests expose scans hidden by favorable datasets, tombstone iteration and memory growth with historical updates; unexpected trends are explained or filed as blockers, not averaged away.

B06 — Publish a reproducible experimental report

Depends: B04, B05. Artifacts: manifests, raw data, plotting/report scripts, machine details, confidence/variance summaries and limits. Separate implementation goals from measured outcomes. Acceptance: another machine can reproduce the methodology and exact result checks; tables trace to raw records; no benchmark claim depends solely on an unverified legacy verifier.

11.12 V — Integration, review and releases

V01 — Produce complete user/developer documentation

Depends: O08, C05. Artifacts: quickstart, supported SQL matrix, model/guarantee document, plan/cursor examples, troubleshooting and extension guide. Document the minimal query contribution process. Acceptance: a new supported query is added as SQL plus fixtures only; examples run from a clean environment; limitations and exactness statuses agree with the executable.

V02 — Run the independent mathematical and semantic review

Depends: P06, D05, R06, A05. Artifacts: source-to-invariant matrix, planner proof review, projected-delta proof review, counterexample disposition and regression report. Use a reviewer who did not write the relevant algorithm. Acceptance: every advertised guarantee has a checked argument and matching implementation counters; finite tests are not substituted for completeness proofs.

V03 — Package and freeze R1

Depends: V01, V02, O03, O05, O06, B06. Artifacts: versioned native library/CLI, schemas, containers/build instructions, benchmark packet, release checklist. Required R1 tasks and the R1 portion of O03 are complete; optional R2/R3 work does not block release. Acceptance: clean-install unseen-query workflow, exact trace suite, strict-height behavior, recovery and resource tests pass. Any remaining performance qualification is stated in the guarantee profile, not hidden by the release name.

V04 — Package R2 and manage extensions separately

Depends: V03, W06. Artifacts: bag/aggregate compatibility matrix, migration notes, exact numeric tests, extended experimental report. Enable each R3 backend only after its own gate. Acceptance: R1 results and guarantees remain intact; SQL bag/aggregate behavior is independently verified; no extension silently changes the semantics or default height policy.

11.13 Dependency and parallel-work summary

Workstream

Can start after

Main handoff

Semantics and independent oracle

A03

Exact fixtures and A04/A05 reference API

Frontend

A01/A03

F05 versioned CQ IR

Structural planner

F05

P02 verifier, P06 height evidence, P08 physical plans

Storage

F01/F05

S02 simple backend, S04 optimized backend

Runtime

P08/S02

R06 maintained state with invariant inspection

Enumeration

R03/P08

D05 proven/qualified cursors and D06 lifecycle

Operations

R05/D06

O08 end-to-end CLI/library and recovery

Cost model

O07/P07

C05 selected plan and C07 ranking evidence

SQL bags/aggregates

Correct set engine interfaces

W06 independent weighted contract

Experiments

O08 and verified workload data

B06 reproducible evidence

The critical path is semantics → CQ IR → verifier/exact planning → support runtime → exact projected delta/cursor lifecycle → recovery → release. The optimized structural algorithm and rich cost model can progress in parallel, but neither may bypass the exactness gate.

12. Audit gates and intermediate checkpoints

These are future acceptance requirements, not completed audits. A gate packet should include its input revision, implementation commit, exact commands, raw outputs, failed cases and disposition, reviewed proof notes, resource assumptions, and the reviewer. A result of “tests passed” without specifying the semantics and coverage is insufficient.

Gate

Required evidence

Passing criterion

If it fails

G0 — Model and references

A01–A05 artifacts, source versions, exact update/output definitions

Every basic operation has unambiguous oracle behavior

Fix the contract before implementing additional runtime features

G1 — SQL-to-CQ equivalence

F01–F06 fixtures, hand-bound examples, SQL reference checks

Binding/normalization preserves the selected semantics

Keep structural/runtime tests on direct CQ IR; do not advertise SQL completeness

G2 — Structural validity and minimum height

P01–P04/P06 proofs and certificates, P05 audit disposition, exhaustive small cases, counterexample fixtures; repaired candidate construction only if enabled

Validity and optimality are separately established; strict timeout is honest

Use complete exact search or reject strict compilation with a resource status; no heuristic relabeling

G3 — Support invariants

R01–R06 state comparisons, S/P/E counters and memory records

Every committed state equals the independent subtree semantics

Shrink the trace and repair the first violated invariant

G4 — Current-result enumeration

D01/D02 exact outputs and operation counts

Duplicate-free exact snapshot; bounded admitted cursor delays

Retain a labeled slow reference path; do not claim constant delay

G5 — Actual projected deltas

D03 proof review, D04/D05 traces, old/new contexts

Exact additions/deletions with disjoint witnesses, including empty deltas

Block delta release even if full snapshots are correct

G6 — Logical update and cursor lifecycle

R05/D06/O02/O03 interleavings, cancellation and self-join traces

One coherent visible epoch; no stale live state after pause/failure

Restrict concurrency/modes until the state machine is proved and tested

G7 — Recovery and delivery

O04–O06 crash matrix, checkpoint round trips, sink replay

State and delivery match documented boundaries at every injected crash point

Keep durability/sink guarantee disabled; do not call it exactly-once

G8 — Runtime performance integrity

B03/B05 raw counters and scale curves

Reported maintenance/output work includes all required computation; state does not hide witness materialization

Correct accounting or implementation; do not mask by disabling output work

G9 — Cost optimizer

P07/C01/C02/C05/C07 baseline evidence; C03/C04/C06 evidence when those features are enabled

Selected plan is admitted and appropriately certified; cost exactness is honest

Fall back to height-only or weighted-depth ranking

G10 — SQL bags and aggregates

W01–W06 exact arithmetic, NULL/global/grouped semantics

Multiplicities and values match independent exact/SQL oracles

Disable the affected feature; preserve R1 support semantics

G11 — Release

V01–V03 checklist for R1; add V04 for R2; clean install and unseen-query trial

Complete end-to-end workflow with matching docs, sources and limits

Keep the release candidate internal until its advertised scope passes

12.1 Mathematical review packet

The structural packet must state the exact admissible family, show native/generalized height conventions, prove the finite search normalization, describe every pruning rule, and specify the lower-bound evidence. It must include both examples where generalized nodes reduce height and examples where the head makes a lower-height candidate invalid. The residual counterexample must remain visible even if a later corrected structural algorithm is developed.

The runtime packet must state the S/P/E/L invariants at complete epochs, prove each event transition, define before/after visibility, prove witness soundness/completeness/disjointness for both insertion and deletion, and account for startup/advance/termination work. It must explain how the next update can safely start after zero output, partial consumption, cancellation, or error.

For annotations, the packet must prove local factorization and the algebraic capability requirements. “The Boolean code with multiplication added” is not a proof. For reoptimization and recovery, it must establish a linearization/visibility boundary and ownership of old state.

12.2 Test independence and useful coverage

Use at least three levels of evidence: hand-calculated adversarial fixtures, a slow independent relational oracle, and end-to-end SQL checks against a mature engine for admitted SQL semantics. The third level cannot replace the first two: another engine may share a semantic assumption, overflow policy or normalization error with the test adapter.

Use exhaustive finite data/query families where feasible, seeded randomized traces with shrinking, and memory/race/sanitizer checks for implementation risks. State the exact finite scope. For arbitrary query-size completeness and worst-case delay, require analytical reasoning; no number of passing examples replaces it.

13. Mandatory regression corpus

13.1 Structural and frontend cases

ID

Query or condition

Required result

Q01

Q(x):R(x)

Singleton native height one; exact insert/delete/no-op behavior

Q02

Q(x):R(x,z)

Projected root support, height one, no duplicate answers

Q03

Q():R(x) and SQL EXISTS wrapper

Internal zero/one nullary tuples; SQL FALSE/TRUE row translation

Q04

Full R(a,b),S(b,c)

Minimum height one using generalized {b}; ordinary-root height two is not the optimum

Q05

Q(a):R(a,b),S(b)

Free-connex, minimum height two; projection changes hierarchy

Q06

Full four-edge path

Minimum CROWN height two; traditional-root minimum three

Q07

Q(a,c):R(a,b),S(b,c)

Acyclic body but non-free-connex head; precise native rejection/fallback

Q08

Triangle R(a,b),S(b,c),T(a,c)

Cyclic; not admitted to the free-connex engine merely by adding a head node

Q09

Four/eight-child shared-key star

Generic fan-out, height-one generalized plan where appropriate

Q10

Nested and equal scopes from distinct tables

All mutable occurrences retained, exact semantics

Q11

Disconnected R(a),S(b) with full/proper/empty heads

Empty separator support, Cartesian output, Boolean conjunction

Q12

Atom containing repeated variable, constants, and contradiction

Intra-tuple filtering; contradictions compile to empty state

Q13

Renamed self-join aliases on one physical graph

Occurrence identity preserved; physical update atomic

Q14

More than 64 variables and composite keys

Dynamic variable sets; no accidental fixed-bitset restriction

Q15

Six-atom incompatible-anchor example in Section 5.3

Reject the invalid reconstruction; accept a valid output-connected tree

Q16

Generalized-root augmentation example in Section 5.3

Support insertion of a generalized separator/root during candidate construction

Q17

Seven-atom residual counterexample

Residual height one, original optimum three; never certify two

Q18

Nine-atom residual counterexample

Same property with two guarded branches; independent lower/upper evidence

Q19

Atom/variable permutation and alias renaming

Same structural minimum and equivalent results

Q20

Deliberately corrupted tree/certificate

Independent verifier rejects with a concrete failed property

13.2 Dynamic, SQL and operational cases

ID

Scenario

Required result

U01

Repeated insertion/absent deletion in set mode

Defined no-op or strict error, never counter drift

U02

Two hidden witnesses project to one visible tuple

No change until first/last support boundary

U03

Root witness with empty parent key

Emit only completions of the actual witness

U04

Child deletion also removes root support

One actual deletion, not ancestor/child duplication

U05

Propagation stops before root but answer changes

Correct delta discovery below root

U06

Multiple changed survivor rows share one visible projection

Consolidate support before deciding visible membership

U07

Insertion creates a combination using two self-join aliases

Include new–new combination once

U08

Two physical rows map to one occurrence tuple

Deleting one physical row leaves logical presence

U09

No-op updates and empty delta cursors

Coherent state and bounded termination

U10

Pause/discard delta after any emitted prefix

Required internal liveness work finishes or remains explicitly pending

U11

Update while snapshot/delta cursor owns state

Documented block/reject/version behavior, no iterator corruption

U12

Mixed-sign batch and atomic row replacement

Correct selected event/net semantics and public epoch

U13

Count/weight change without support change

R2 payload changes propagate

U14

Weighted generalized {x,z} child of {x}

Sum over z before parent message

U15

Parent and enumerated child annotations

No double multiplication of subtree contribution

U16

Counts above 2^53 and at integer limit

Exact value or explicit atomic overflow failure

U17

SUM cancels to zero while rows remain

Group persists; payload zero is not absence

U18

Empty global COUNT/SUM/AVG and disappeared grouped key

SQL scalar/global and group behavior are distinguished

U19

NULL equality, DISTINCT and COUNT(expr)

Correct admitted SQL semantics

U20

Repeated insert/delete churn with fixed live cardinality

Bounded logical state; declared allocator high-water behavior

U21

Crash or injected failure during alias fan-out, propagation, drain or checkpoint

Recovery matches an allowed committed boundary; no partial logical epoch reaches a public sink

U22

Sink retry/restart changes hash iteration

No ordinal-identity misuse or duplicate delivery under the claimed protocol

U23

FIFO violation or late expiration

Correct result plus declared guarantee/policy response

U24

Plan switch during a continuing update stream

One consistent boundary; no missing/repeated delta

13.3 Four copyable semantic traces

Projection collision. For Q(x):R(x,z), begin empty. Insert (a,1) → {+a}. Insert (a,2) → empty delta. Delete (a,1) → empty delta. Delete (a,2) → {-a}. The current set after the four steps is respectively {a}, {a}, {a}, and empty.

Root witness. For Q(x):R(x), start with {a} and insert b. The delta is {+b}. Calling an unrestricted root snapshot and returning {a,b} is incorrect.

Ancestor/child deletion. For Q(x,y):R(x),S(x,y), start with R={a} and S={(a,b)}. Delete (a,b) from S. The result becomes empty and the delta contains exactly one -(a,b), even if survivor changes are observed at both nodes.

Self-join cross term. For Q(a,b,c):Edge(a,b),Edge(b,c), start empty and insert the physical edge (u,u). The logical occurrence updates must produce exactly one (u,u,u). Applying each alias against only the original empty state misses it; treating both updates as independent completed physical events can corrupt visibility or counting.

14. Experimental plan and success criteria

14.1 Questions the experiments should answer

Establish first whether the generic native engine preserves exact results across the whole admitted class. Then measure the runtime cost of generic plans versus specialized legacy implementations, the effect of generalized nodes and height selection, the value of update statistics, and the cost of operational features. Do not make a predetermined speedup the correctness criterion.

For planning, measure compile time, peak planner memory, minimum-height evidence time, candidate count, local fan-out and timeout frequency against query size and shape. Compare exact reference search, optimized exact search, validated residual candidates and any meta-decomposition provider. Report height gaps for incomplete searches, not only the latency of the returned plan.

For maintenance, measure total input work from empty state, p50/p95/p99 update latency, maximum observed latency, affected-record counts, support and annotation transitions, and state memory. Separate amortized throughput from per-update latency. Include insertion-only, deletion-only after explicitly charged loading, global FIFO, per-relation FIFO, mixed patterns and adversarial churn; these are different workload contracts.

For output, measure cursor startup, per-result work, termination, total enumeration time, serialization and sink delay. Include large-witness/small-projected-output cases and large-output cases. A client that consumes and discards rows still performs enumeration; a maintenance-only mode does not.

14.2 Dataset and query families

Start with synthetic distributions that isolate a mechanism: uniform keys, skewed keys, many hidden witnesses per visible answer, selective/nonselective joins, empty and dangling branches, high fan-out, increasing height, composite keys, and wide/string tuples. Generate both output-small and output-large instances. Scale live database size while keeping the query fixed for data-complexity measurements; separately scale query size for compiler/runtime-overhead measurements.

Then classify and import the relevant CROWN/DynaGox workloads: graph paths/stars/combs, projected queries, SNB/LSQB, and admitted portions of JOB, CEB, TPC-H and TPC-DS. Some legacy queries are cyclic or aggregate and belong in later stages. Record transformations and do not quietly replace a source workload with an easier free-connex query while keeping its benchmark name.

14.3 Baselines and fair comparisons

Use the original Scala/Flink CROWN artifact, the DynaGox C++ CROWN baseline, the independent snapshot evaluator, and a mature SQL engine for appropriate recomputation workloads. Additional IVM systems can be added once their semantics and operation modes are verified. DynaGox approximation belongs in an explicitly approximate experiment; exact and approximate outputs should not share one unlabeled ranking.

Pin source commits, compilers, optimization flags, dependency versions, allocator, hardware, thread counts and input traces. Match memory/output modes and verify tiny results before performance runs. Charge parsing/loading/index construction/checkpoint work consistently. Report baseline failures and unsupported cases. Shared setup is charged once with a declared amortization policy; temporary tables, conversion, sorting and output draining are real costs.

14.4 Ablation matrix

Axis

Comparisons

What it isolates

Storage

Simple standard containers vs optimized indices

Container/layout improvement

Runtime

Generic executor vs generated/specialized implementation

Interpretation and specialization cost

Structure

Valid ordinary tree vs generalized minimum tree

Value of the generalized tree family

Planner

Height-only vs weighted depth vs event-cost model

Benefit of dynamic estimates beyond structure

Search

Exact candidates vs restricted/meta-decomposition candidates

Search coverage versus scoring quality

Statistics

Exact small-data stats vs sampled/stale/absent stats

Estimation sensitivity

Output

Maintenance only; enumerate/discard; serialize; durable sink

Cost boundaries and backpressure

Updates

Single events vs transport batches vs atomic net batches

Batching benefit and semantic cost

Recovery

No durability vs WAL vs checkpoints

Operational overhead

SQL semantics

Set vs bag vs admitted aggregates

Additional annotation work

14.5 Release success criteria

Correctness is exact agreement with the independent oracle on the specified finite corpus, successful fault tests, and reviewed arguments for general structural and cursor claims. Coverage is demonstrated through unseen SQL/CQ inputs, not the count of handwritten benchmarks. The minimum-height claim needs a certificate or a proved complete algorithm; the residual counterexample must be handled correctly.

Performance success should be stated after measurements. A reasonable engineering objective is to retain near-linear state scaling for the fixed-query set core, avoid avoidable global scans on support-preserving updates, and show where a general native implementation improves or costs more than specialized baselines. Report any overhead from exact arithmetic, generic dispatch and recovery honestly. An observed speedup is evidence for the tested workload, not a universal theorem.

15. Recommended implementation sequence

Stage 1: make correctness executable. Complete A01–A05, F01–F05, P01–P03 and the simple storage interface. Deliver a command that parses or reads a CQ, classifies it, checks a supplied tree, computes an exact small-query optimum and runs the independent evaluator. This stage should finish before a large optimized engine is written.

Stage 2: build the generic set engine. Complete P08, R01–R06 and D01/D02 using standard-container storage. Demonstrate one native-root query, one generalized-root query, a proper projection, a Boolean query, a disconnected query and a self-join using the same executor. Confirm state invariants after every update.

Stage 3: close the delta and minimum-height gates. Complete D03–D06, P04/P06 and the exactness status interface. Keep P05 as a separately audited candidate/repair task. Do not postpone projected delta correctness or height certification until after throughput optimization; both affect the core representation and interfaces.

Stage 4: make it a usable system. Add O01–O08, optimized storage where justified, C01/C02/C05 baseline ranking, and B01–B03. A query should now be installable from SQL, consume a stream, expose current/delta results, explain its plan and recover from a checkpoint.

Stage 5: establish evidence and ship R1. Finish the independent audits, full regression suite, scaling experiments, clean-install documentation and V03. Richer CBO can improve the release but must not delay a correct basic cost-ranking interface indefinitely.

Stage 6: add SQL analytics. Complete W01–W06 and the R2 tests. Use separate semantic and performance results. Then prioritize R3 work according to measured bottlenecks and research value; do not enable all extensions simultaneously.

A practical division is a frontend/planner owner, a runtime/storage owner, and an independent verification/experiment owner, with a research reviewer for P05 and D03. With fewer people, preserve these review roles even if implementation is sequential. Estimate calendar time only after the parser/build spike, exact-planner profile and delta prototype reveal the main risks; task dependencies are more reliable than an invented fixed deadline.

16. Coding-agent assignment and completion templates

16.1 Standard assignment

Task: <one task ID and title from this plan>
Repository/worktree: <resolved project location>
Base commit: <exact commit>
Dependencies verified: <task IDs and their evidence>

Read:
  - The relevant contract/architecture sections in this plan.
  - The repository's current AGENTS.md and module documentation.
  - The cited source sections that define this component's assumptions.

Implement:
  <Concrete deliverables from the task card.>

Preserve:
  - Existing semantic mode and public interface compatibility.
  - Atom-occurrence identity and the stated height definition.
  - Exact support and arithmetic rules.
  - Independent reference/checker code paths.

Acceptance:
  <Task criteria, required fixtures, and the relevant gate.>

Return:
  - Changed files and why each changed.
  - Build/test commands with actual outcomes.
  - Minimal failing traces, if any.
  - Proof obligations or assumptions not discharged.
  - Performance evidence only for measurements actually executed.
  - Updated task-ledger status and next dependency that is now enabled.

Do not label a heuristic plan minimum-height. Do not replace a requested
semantic feature by a silently different one. If a proof gate fails,
preserve a correct labeled fallback and report the exact unresolved claim.

16.2 First assignment to issue

Implement the R0 foundation for CROWN Next, covering A01, A03 and A04.
Use C++23 unless the project has already selected Rust. Add the native
build, a small versioned direct-CQ input schema, exact set semantics,
and an independent slow evaluator for current answers and before/after
set deltas. Support singleton, projected singleton, two-edge path,
Boolean and self-join fixtures. Do not begin optimized CROWN propagation
in this task. Produce the relevant partial G0 evidence for these three
tasks, and record unresolved API/semantics choices explicitly. G0 remains
open until source-baseline task A02 and generator/shrinker task A05 also
pass.

Then issue the structural verifier/oracle tasks and frontend tasks as separate workstreams. This gives later coding agents stable targets and prevents the first agent from embedding a handwritten query plan in a demonstration and calling the system complete.

16.3 Review packet template

Gate:
Commit:
Semantic scope:
Input/update/output contract:
Source versions and assumptions:
Algorithms/invariants reviewed:
Independent oracle/checker used:
Commands executed and outcomes:
Finite coverage (queries, domains, traces, seeds):
Analytical proof status:
Memory/latency accounting boundaries:
Known failures or unsupported cases:
Reviewer findings and disposition:
Release decision for this scope:

17. Definition of done

R1 is ready when SQL within the declared free-connex fragment compiles through the same generic frontend/planner/runtime without query-specific C++ additions; every admitted plan passes the independent structural checker; strict minimum-height results carry valid evidence; and full and delta outputs agree with independent semantics across the mandatory cases.

The operational workflow must include typed ingestion, consistent logical updates, explicit cursor ownership, bounded backpressure, checkpoint/replay, usable EXPLAIN/metrics, installation documentation, and reproducible experiments. Exactness, arithmetic, query coverage, update assumptions and resource limits must be visible to users. A failed proof of a fast special case cannot be hidden by a broad marketing claim.

R2 additionally requires exact bags and admitted aggregates, SQL NULL and empty-aggregation behavior, transactional annotation updates and recovery. Each R3 feature has its own admission and evidence; an unfinished extension does not invalidate the completed core, but it must remain disabled or explicitly experimental.

The two main research checkpoints are now concrete: a scalable complete minimum-height algorithm under the exact CROWN tree definition, and a fully specified projected-delta/liveness implementation with the intended delay and maintenance accounting. The complete finite planner and independent semantic evaluators make progress possible while those optimized paths are developed and reviewed.

18. Source register and limits of this review

All linked sources were inspected or explicitly marked as discovery/abstract-level material. The architectural choices, task decomposition, API sketches, finite-search normalization argument, and counterexamples in this plan are proposed engineering or analytical work, not quotations from those sources. This document does not reproduce the papers or their proofs in full.

18.1 Research papers

P1 Qichen Wang, Xiao Hu, Binyang Dai and Ke Yi. Change Propagation Without Joins. PVLDB 16(5), 2023; corrected full version arXiv:2301.04003v2, 2 December 2023. Full text · version record · DOI. The technical text, Algorithms 1–6, relevant extensions, experiment design and appendices were examined. The arXiv record explicitly identifies v2 as correcting errors in the original version. The implementation observations in Sections 7.2–7.4 are independently derived hazards for literal transcription; they are not claims that a new executor has been tested.

P2 Qichen Wang. Towards Parameterized Hardness on Maintaining Conjunctive Queries. PODS/PACMMOD 2026; arXiv:2603.14754v1. Full text · version record · DOI. Definitions, structural height claims, relevant appendix proofs and the star-algorithm complexity were examined. Section 5.3 records a concrete analytical issue with the inspected residual-height recipe. The remaining hardness results were not subjected to a complete independent proof audit here.

P3 Zhekai Jiang, Qichen Wang and Christoph Koch. Succinct Structure Representations for Efficient Query Optimization. SIGMOD/PACMMOD 2026; full version arXiv:2603.15465v2, 18 August 2026. Full text · DOI. Principal definitions, meta-decomposition construction/enumeration, optimizer sections and selected appendix material were examined. Section 5.3's unbounded-fan-out qualification is reflected in this plan. This review does not claim a complete audit of every appendix proof.

P4 Xiao Hu and Qichen Wang. Towards Update-Dependent Analysis of Query Maintenance. PODS/PACMMOD 2025, article 117. Author PDF · DOI. Main results, update models, tree definitions, Trim/weak-q-hierarchical structural statements and mixed-pattern material were examined. The structural issue described in Section 5.3 also applies to the literal Lemma 3.7 reconstruction. This is a focused finding, not a full certification or rejection of the paper's remaining results.

P5 Qichen Wang and Ke Yi. Maintaining Acyclic Foreign-Key Joins under Updates. SIGMOD 2020. Author PDF. Definitions, maintenance framework and complexity assumptions were read for constraint/update-pattern implications; not every proof was independently audited.

P6 Qichen Wang, Bingnan Chen, Binyang Dai, Ke Yi, Feifei Li and Liang Lin. Yannakakis+: Practical Acyclic Query Evaluation with Theoretical Guarantees. SIGMOD 2025. Author PDF. Main algorithms, structural conditions, aggregation/planning and implementation sections were examined. The linked author manuscript is used for technical content rather than its placeholder publication fields.

P7 Bingnan Chen, Binyang Dai, Qichen Wang and Ke Yi. Query running too slow? Rewrite it with Quorion! PVLDB 18(12), 2025, pp. 5243–5246. Paper · DOI. The four-page demo was read for parser/planner/CBO/IR/backend design. Its implementation was not separately audited in this task.

P8 Binyang Dai, Qichen Wang and Ke Yi. SparkSQL+: Next-generation Query Planning over Spark. SIGMOD Companion 2023. Author PDF · DOI. The demo was read for frontend, structural planning and code-generation architecture.

P9 Qichen Wang and Ke Yi. Conjunctive Queries with Comparisons. SIGMOD 2022. Author PDF · DOI. Structural definitions and result/planner implications were examined. This was the conference paper, not a complete audit of the later TODS extension.

P10 Qichen Wang, Qiyao Luo and Yilei Wang. Relational Algorithms for Top-k Query Evaluation. SIGMOD/PACMMOD 2024, article 168. Author PDF · DOI. Ranking model, main algorithm/results and static/dynamic boundaries were examined. The plan deliberately postpones dynamic top-k.

P11 Xiao Hu and Qichen Wang. Computing the Difference of Conjunctive Queries Efficiently. SIGMOD/PACMMOD 2023, article 153. Full paper · DOI. Problem/model, structural result and rewrite sections, and set/bag distinction were examined. General dynamic negation is not inferred from this static work.

P12 Binyang Dai and Ke Yi. Approximate Query Processing under Updates. PACMMOD 3(6), article 295, 2025 / SIGMOD 2026. Publisher page · repository. Publisher abstract/metadata and repository source were inspected; the publisher's full paper was not accessible in this pass. This is not a Qichen Wang-authored paper. Its approximate insertion-only result is not treated as a fully dynamic exact CROWN guarantee.

P13 Qichen Wang and Xiao Hu. Answering Conjunctive Queries with Aggregations under Updates. arXiv:2607.23881, 2026. Primary record. Discovery and abstract-level evidence only; direct full-text retrieval was unavailable during preparation. Read the actual full version and audit its assumptions before making any implementation claim based on it. No specific theorem from it is a dependency of R1 or R2 in this plan.

18.2 Repository and implementation sources

Ref

Source

How it was used

R1

NTU-DBT/CROWN, complete tree at e369a623517723b3be3ea3e9806779f3c591e7f9

Repository inventory, language/build boundaries and provenance

R2

hkustDB/DynaGox, complete tree at c6811db68a34ab3b32722968c4e1e821f730c5ac

Native baseline and experiment inventory

R3

CROWN crown/README.md

Manual custom-query workflow and documented feature support

R4

CROWN RelationType/Relation.scala

Support/enumeration design, fan-out restriction and annotated-path limitations

R5

CROWN RelationType/Attributes.scala

Tuple representation and annotation arithmetic

R6

DynaGox Readme.md

Repository layout, build/reproduction context and F-IVM acknowledgement

R7

DynaGox experiments/src/crown/main.cpp

Fixed-query dispatch and baseline entry point

R8

DynaGox multi_hash_map/include/multi_hash_map.h and associated pool/index files

Index design, arithmetic/zero behavior and ownership audit

R9

DynaGox experiments/src/crown/crown_line5cd.cpp

Insertion-only behavior in the inspected specialization

R10

DynaGox ResultVerifier/.../Main.scala

Numeric tolerance in legacy verification

R11

DynaGox C++ top-level CMakeLists.txt

C++23/CMake build assumptions

R12

CROWN OutputResultTest.scala

Existing asserted trace cases to preserve as fixtures

The reviewed trees were complete, not truncated listings. The review covered key runtime, index, build, entry-point and test files plus representative query implementations. It did not cover every specialization or vendored compiler file. No legacy executable was built or benchmarked as part of preparing this plan.

18.3 Frontend dependencies

T1 libpg_query official documentation. Repository/README. Read the C API example, PostgreSQL parse-tree behavior, allocation/freeing interface and release-pinning guidance. This is a syntax frontend choice; a new semantic binder is still required.

T2 sqlparser-rs official documentation. Repository/README. Read the syntax-versus-semantics distinction and AST facilities. This is the Rust alternative, not a second mandatory runtime dependency.
