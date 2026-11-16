# O07 run-context independent root review — 2026-11-07

Scope: static review of the frozen [run-context proposal](o07-run-context-proposal/README.md),
package b4b985c8050bd42414f93b8b7ec07366340b96e61f695943393c904ff619f541.
No current static blocker was found. Compiler results are preparation; the six
independent runtime groups remain required and have not passed yet.

The 639-line patch records initialization only after successful physical build
and changes rebuilt provenance after the new owner exists. Session admission
owns exact input/options, queue/window/default snapshot policy and original
requested/resolved delta settings through a shared const context. Every current
native input/queue/window/snapshot option appears in the companion export; typed
input is explicitly distinguished from wire decoding. Individual snapshot and
transport-batch overrides are outside the stored default policy.

Attempt begin copies the current declaration/configuration; replacement of
current labels does not rewrite history. Output disposition uses the existing
prepare/publication/transfer/callback/discard sites. A local closed flag prevents
an old empty epoch or repeated release from rewriting a later attempt. Callback
discard stays deferred while the borrowed row is active. Failed mandatory drain
charges do not falsely claim successful retention suppression. Flags record
observed actions, not delivery totals or guarantees.

Snapshots now own shared const metadata and have explicitly nonthrowing copy
and move operations. Admission can allocate; update/cancel/drop hooks copy only
fixed values/shared handles and can deallocate on final release. The complete
nine-runtime-unit and all consumers must be rebuilt for this ABI. Native binding
admission constructs no JSON; the separate bounded companion writer performs
strict UTF-8 validation only at export. Caller declarations remain unmeasured
and cannot provide proof, durable delivery or recovery authority.

Runtime checks must still establish lifecycle flags, old-empty-epoch retention,
callback failures/retry/discard, cap rollback, off equivalence, allocation/clock
behavior, exact metadata lifetimes, UTF-8/NUL text boundaries and encoded limits.
The companion is not yet wired into native human/JSON EXPLAIN/schema, and cursor
phases plus progress/infeasible-query reports remain separate O07 work. No native
source or task status changed for this review.
