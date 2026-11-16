# Independent query sessions

Link `CROWN::queries` and include
[`crown/runtime/queries.hpp`](../include/crown/runtime/queries.hpp) to own several
existing QuerySessions through one serial directory. Every query retains its
own input, progress, results, finite native account and publication/recovery
boundaries. The directory adds ownership and lookup, with no shared operator or
update-path callback. This implements [Refactor X10](../Refactor.md).

```cpp
crown::runtime::IndependentQueries queries;
auto owner = crown::runtime::QuerySession::create_typed(program);
const auto id = queries.admit(owner); // success moves owner; failure preserves it
auto& session = queries.at(id);       // borrow from this registered owner
session.start();
// Use its ordinary enqueue/begin/step/commit/output operations.
queries.erase(id);                    // destroys only this session
```

Create or restore each session through its existing public factory before
admitting it. `release(id)` transfers that exact owner back to the caller without
changing its account or progress. Replanning and recovery use the normal
[Session](session_lifecycle.md) and [reoptimization](reoptimization.md) contracts on that
query. A failure has no directory-wide recovery or publication effect.

The default directory allows 1,024 live queries and 256 KiB for its controller
and ordered-map nodes. `QueryDirectoryLimits` selects both finite limits; zero
query slots disables admission. Session memory is separate from this allowance.
`directory_memory()` reports actual directory requested bytes, while each
session exposes its own account statistics. The fixed-size caller facade and
the process's allocator/RSS are outside these requested-byte counts.

An ID contains the process-local directory account identity and a monotonically
increasing ordinal. Removed IDs are never reused; foreign/stale IDs reject.
ID exhaustion rejects before publication. An ID is a local name, so a recovered
session receives a fresh ID when admitted into a new directory. Its durable
identity remains the Session/recovery identity.

`at(id)` returns a borrowed reference. Changes to other directory entries preserve
that borrow; removing/releasing its own entry or destroying the directory ends
it. Owning snapshots and result values keep their existing lifetimes after
removal. Serialize all directory/session use as required by the existing
creator-thread and account contracts. Admission/removal/lookup use ordered-map
work in the number of live queries. Keeping a valid Session reference avoids
that lookup during native updates; the directory keeps no dropped-query history.

The [installed example](../examples/independent-queries/main.cpp) accepts one
catalog and two SQL/input-stream pairs. It compiles the supplied SQL through the
normal frontend/planner, runs the sessions serially and prints each query's
actual rows, progress and distinct account identity. Its
[standalone CMake file](../examples/independent-queries/CMakeLists.txt) uses only
the installed package. Parallel execution and cross-query state optimization
remain deferred.
