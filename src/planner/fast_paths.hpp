// Private compatibility header; use ProducerMachine for owned fast analysis and construction.
// See docs/planner_continuations.md, grants.
#pragma once
// P06 fast analysis, union/find, hierarchy recognition and choice construction
// are owned coroutines in ProducerMachine::Impl (exact.cpp). They deliberately
// share the producer's retryable operation scheduler and immutable Choice DAG;
// no blocking WorkBudget-driven fast-path entry point remains.
