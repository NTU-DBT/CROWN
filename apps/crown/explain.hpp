#pragma once
namespace crown::cli {
// Private application dispatcher. argv[0] is "explain", argv[1] its subcommand.
// Owns EXPLAIN-only diagnostics; the outer CLI keeps all existing handlers.
int explain_main(int argc,char** argv);
} // namespace crown::cli
