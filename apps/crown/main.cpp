#include "crown/api/error.hpp"
#include "crown/version.hpp"
#include "crown/io/document.hpp"
#include "crown/io/tree.hpp"
#include "crown/io/oracle.hpp"
#include "crown/io/sql.hpp"
#include "crown/io/catalog.hpp"
#include "crown/io/binding.hpp"
#include "crown/io/normalization.hpp"
#include "crown/io/identity.hpp"
#include "crown/io/admission.hpp"
#include "crown/io/recognition.hpp"
#include "crown/io/physical.hpp"
#include "crown/io/support.hpp"
#include "crown/io/ingest.hpp"
#include "crown/catalog/catalog.hpp"
#include "crown/planner/recognize.hpp"
#include "evaluator.hpp"
#include "explain.hpp"
#include "workflow.hpp"
#include "aggregate.hpp"

#include <exception>
#include <new>
#include <charconv>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>

namespace {
crown::planner::SearchLimits search_limits(const char* value) {
  crown::planner::SearchLimits limits;
  if (!value) return limits;
  const std::string text = value;
  if (text == "unlimited") { limits.work_limit.reset(); return limits; }
  std::uint64_t work = 0;
  const auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), work);
  if (error != std::errc{} || end != text.data() + text.size()) throw crown::Error("usage", "WORK_LIMIT must be an unsigned integer or unlimited");
  limits.work_limit = work;
  return limits;
}
std::string read_text(const char* path, std::optional<std::size_t> byte_limit = std::nullopt) {
  std::ifstream input(path, std::ios::binary);
  if (!input) throw crown::Error("io_error", "cannot open input document");
  std::string text;
  if (byte_limit) {
    // Read at most limit+1; the parser or caller reports its normal limit error.
    // Calls without byte_limit retain the separate legacy whole-file behavior.
    // These private bounded callers use finite SQL/catalog limits.
    text.resize(*byte_limit + 1);
    input.read(text.data(), static_cast<std::streamsize>(text.size()));
    text.resize(static_cast<std::size_t>(input.gcount()));
  } else {
    text.assign(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
  }
  if (input.bad()) throw crown::Error("io_error", "failed reading input document");
  return text;
}
}  // namespace

static int command_main(int argc, char** argv) {
  using crown::io::Json;
  try {
    if (argc == 2 && std::string(argv[1]) == "--version") {
      std::cout << "CROWN Next " << crown::version << " (C++23; exact set semantics; native API " << crown::public_api_version << ")\n";
      return 0;
    }
    if (argc == 2 && std::string(argv[1]) == "--help") {
      std::cout << "usage: crown COMMAND ...\n"
          "  --version; --help\n"
          "  compile; run; restore; snapshot; checkpoint; results; verify-trace; benchmark\n"
          "  aggregate {create|run|status|snapshot|checkpoint}; aggregate --help\n"
          "  parse-sql; bind-sql; normalize-sql; admit-sql; admit-normalized\n"
          "  validate-normalized; canonicalize-normalized; upgrade-cq; upgrade-normalized\n"
          "  fingerprint-cq; fingerprint-normalized; lower-plan; lower-normalized\n"
          "  support-trace; validate-input; validate-physical; canonicalize-physical\n"
          "  validate-catalog; canonicalize-catalog; oracle; validate-cq; canonicalize\n"
          "  classify; tree-oracle; validate-plan; verify-height\n"
          "  explain {physical|runtime|session|query|progress|replay} INPUT [OPTIONS]\n"
          "  crown explain --help lists EXPLAIN options.\n";
      return 0;
    }
    if (argc >= 2) {
      const std::string_view command(argv[1]);
      if(command=="aggregate")return crown::cli::aggregate_main(argc,argv);
      if (command=="compile" || command=="run" || command=="restore" || command=="snapshot" || command=="checkpoint" || command=="results" || command=="benchmark" || command=="verify-trace" || ((command=="explain" || command=="validate-plan") && argc>=3 && std::string_view(argv[2])=="compiled"))
        return crown::cli::workflow_main(argc,argv);
    }
    if (argc >= 2 && std::string(argv[1]) == "explain")
      return crown::cli::explain_main(argc-1,argv+1);
    if (argc >= 2 && std::string(argv[1]) == "validate-input") {
      if (argc < 5 || argc > 6) {
        throw crown::Error("usage", "usage: crown validate-input CATALOG.json FORMAT INPUT [TABLE]");
      }

      const std::string format = argv[3];
      crown::io::InputOptions options;
      const bool needs_table = format == "csv" || format == "legacy-signed" ||
          format == "legacy-insert-only" || format == "legacy-flags";
      if (format == "jsonl") options.format = crown::io::InputFormat::jsonl;
      else if (format == "binary") options.format = crown::io::InputFormat::binary;
      else if (format == "csv") options.format = crown::io::InputFormat::csv;
      else if (format == "legacy-signed") options.format = crown::io::InputFormat::legacy_signed;
      else if (format == "legacy-insert-only") options.format = crown::io::InputFormat::legacy_insert_only;
      else if (format == "legacy-flags") options.format = crown::io::InputFormat::legacy_flags;
      else throw crown::Error("unsupported_input_format", "unsupported validate-input format: " + format);

      if ((needs_table && argc != 6) || (!needs_table && argc != 5)) {
        throw crown::Error("usage", "jsonl and binary need no TABLE; csv and legacy formats need an exact physical TABLE");
      }

      constexpr std::size_t catalog_byte_limit = 16U * 1024U * 1024U;
      const auto catalog_text = read_text(argv[2], catalog_byte_limit);
      if (catalog_text.size() > catalog_byte_limit) {
        throw crown::Error("resource_limit", "catalog document exceeds the 16 MiB byte limit");
      }
      const auto catalog = crown::io::read_catalog(catalog_text);
      if (needs_table) options.table = crown::catalog::find_table(catalog, argv[5]);

      std::ifstream input(argv[4], std::ios::binary);
      if (!input) throw crown::Error("io_error", "cannot open physical input stream");
      crown::io::EventReader reader(input, catalog, options);
      while (reader.peek()) reader.acknowledge();

      const auto progress = reader.progress().export_value();
      const Json summary{{"schema_version", 1}, {"input_valid", true}, {"format", format},
          {"catalog_sha256", reader.catalog_sha256()}, {"records", reader.records_read()},
          {"bytes", reader.bytes_read()}, {"sequence", progress.sequence},
          {"source_positions", progress.source_positions}};
      std::cout << summary.dump(2) << '\n';
      return 0;
    }
    // Syntax, binding, normalization and structural admission remain separate.
    if (argc >= 2 && std::string(argv[1]) == "parse-sql") {
      if (argc != 3) throw crown::Error("usage", "usage: crown parse-sql INPUT.sql");
      const auto parsed = crown::frontend::parse_sql(read_text(argv[2], crown::frontend::ParseLimits{}.source_bytes));
      std::cout << crown::io::write_sql_parse(parsed).dump(2) << '\n';
      return std::holds_alternative<crown::frontend::SqlSyntax>(parsed) ? 0 : 1;
    }
    if (argc >= 2 && std::string(argv[1]) == "bind-sql") {
      if (argc != 4 && argc != 5) throw crown::Error("usage","usage: crown bind-sql INPUT.sql CATALOG.json [PARAMETER_TYPES.json]");
      const auto catalog = crown::io::read_catalog(read_text(argv[3]));
      const auto options = argc == 5 ? crown::io::read_bind_options(read_text(argv[4])) : crown::frontend::BindOptions{};
      const auto bound = crown::frontend::bind_sql(read_text(argv[2],crown::frontend::ParseLimits{}.source_bytes),catalog,options);
      std::cout << crown::io::write_sql_binding(bound).dump(2) << '\n';
      return std::holds_alternative<crown::frontend::BoundSql>(bound) ? 0 : 1;
    }
    if (argc >= 2 && std::string(argv[1]) == "normalize-sql") {
      if (argc < 4 || argc > 6) throw crown::Error("usage","usage: crown normalize-sql INPUT.sql CATALOG.json [PARAMETER_TYPES.json [PARAMETER_VALUES.json]]");
      const auto catalog = crown::io::read_catalog(read_text(argv[3]));
      const auto bind_options = argc >= 5 ? crown::io::read_bind_options(read_text(argv[4])) : crown::frontend::BindOptions{};
      crown::frontend::NormalizeOptions options;
      if (argc == 6) options.parameters = crown::io::read_parameter_values(read_text(argv[5]));
      const auto bound = crown::frontend::bind_sql(read_text(argv[2],crown::frontend::ParseLimits{}.source_bytes),catalog,bind_options);
      const auto result = std::holds_alternative<crown::frontend::BoundSql>(bound) ?
          crown::frontend::normalize_sql(std::get<crown::frontend::BoundSql>(bound),options) :
          crown::frontend::SqlNormalizeResult{std::get<crown::frontend::BindingDiagnostic>(bound)};
      std::cout << crown::io::write_sql_normalization(result).dump(2) << '\n';
      return std::holds_alternative<crown::frontend::NormalizedSql>(result) ? 0 : 1;
    }
    if (argc >= 2 && std::string(argv[1]) == "admit-sql") {
      if (argc != 4 && argc != 5) throw crown::Error("usage","usage: crown admit-sql INPUT.sql CATALOG.json [OPTIONS.json]");
      const auto catalog = crown::io::read_catalog(read_text(argv[3]));
      const auto options = argc == 5 ? crown::io::read_admission_options(read_text(argv[4])) : crown::frontend::AdmissionOptions{};
      const auto result = crown::frontend::admit_sql(read_text(argv[2],crown::frontend::ParseLimits{}.source_bytes),catalog,options);
      std::cout << crown::io::write_admission(result).dump(2) << '\n';
      return result.status == crown::frontend::AdmissionStatus::admitted ? 0 : 1;
    }
    if (argc >= 2 && std::string(argv[1]) == "admit-normalized") {
      if (argc != 3 && argc != 4) throw crown::Error("usage","usage: crown admit-normalized PROGRAM.json [WORK_LIMIT]");
      crown::planner::RecognitionLimits limits;
      if (argc == 4) limits.work_limit = search_limits(argv[3]).work_limit;
      crown::frontend::AdmissionResult result;
      try { result = crown::frontend::admit_normalized(crown::io::read_sql_normalization(read_text(argv[2])),limits); }
      catch (const crown::Error& error) {
        if (error.code() != "resource_limit") throw;
        result.status = crown::frontend::AdmissionStatus::resource_limit; result.phase = "artifact";
        result.limits.recognition = limits;
        result.diagnostic = crown::frontend::SqlDiagnostic{error.code(),error.what(),{},{},{},{}};
      }
      std::cout << crown::io::write_admission(result).dump(2) << '\n';
      return result.status == crown::frontend::AdmissionStatus::admitted ? 0 : 1;
    }
    if (argc >= 2 && (std::string(argv[1]) == "validate-normalized" || std::string(argv[1]) == "canonicalize-normalized")) {
      if (argc != 3) throw crown::Error("usage","usage: crown {validate-normalized|canonicalize-normalized} PROGRAM.json");
      const auto program=crown::io::read_sql_normalization(read_text(argv[2]));
      const Json output=std::string(argv[1]) == "canonicalize-normalized" ? crown::io::write_sql_normalization(program) :
          Json{{"schema_version",1},{"program_valid",true},{"admission_status","not_checked"}};
      std::cout << output.dump(2) << '\n'; return 0;
    }
    if (argc >= 2 && (std::string(argv[1]) == "upgrade-cq" || std::string(argv[1]) == "upgrade-normalized")) {
      if (argc != 4) throw crown::Error("usage","usage: crown {upgrade-cq|upgrade-normalized} INPUT.json TARGET_VERSION");
      const std::string value=argv[3]; std::uint64_t version=0;
      const auto [end,error]=std::from_chars(value.data(),value.data()+value.size(),version);
      if (error != std::errc{} || end != value.data()+value.size()) throw crown::Error("usage","TARGET_VERSION must be an unsigned integer");
      if (std::string(argv[1]) == "upgrade-cq") {
        const auto document=crown::io::read_document(read_text(argv[2]));
        std::cout << crown::io::write_document(crown::io::upgrade_document(document,version)).dump(2) << '\n';
      } else {
        const auto program=crown::io::read_sql_normalization(read_text(argv[2]));
        std::cout << crown::io::write_sql_normalization(crown::io::upgrade_sql_normalization(program,version)).dump(2) << '\n';
      }
      return 0;
    }
    if (argc >= 2 && (std::string(argv[1]) == "fingerprint-cq" || std::string(argv[1]) == "fingerprint-normalized")) {
      if (argc != 3 && argc != 4) throw crown::Error("usage","usage: crown {fingerprint-cq|fingerprint-normalized} INPUT.json [WORK_LIMIT]");
      crown::io::IdentityLimits limits;
      if (argc == 4) limits.work_limit=search_limits(argv[3]).work_limit;
      try {
        crown::io::QueryIdentity identity;
        if (std::string(argv[1]) == "fingerprint-cq") {
          const auto document=crown::io::read_document(read_text(argv[2]));
          identity=crown::io::query_identity(document.catalog,document.query,{},limits);
        } else identity=crown::io::query_identity(crown::io::read_sql_normalization(read_text(argv[2])),{},limits);
        std::cout << crown::io::write_identity(identity).dump(2) << '\n'; return 0;
      } catch (const crown::Error& error) {
        if (error.code() != "resource_limit") throw;
        std::cout << Json{{"schema_version",1},{"identity_valid",false},{"status","resource_limit"},
            {"diagnostic",{{"code",error.code()},{"message",error.what()}}}}.dump(2) << '\n'; return 1;
      }
    }
    if (argc >= 2 && (std::string(argv[1]) == "lower-plan" || std::string(argv[1]) == "lower-normalized")) {
      if (argc != 4 && argc != 5) throw crown::Error("usage","usage: crown {lower-plan QUERY.json|lower-normalized PROGRAM.json} TREE.json [OPTIONS.json]");
      const auto options=argc==5 ? crown::io::read_physical_options(read_text(argv[4])) : crown::PhysicalOptions{};
      try {
        const auto plan=[&]() {
          if (std::string(argv[1])=="lower-plan") {
            const auto document=crown::io::read_document(read_text(argv[2]));
            const auto tree=crown::io::read_tree(read_text(argv[3]),document.catalog,document.query);
            return crown::planner::lower_tree(document.catalog,document.query,tree,options);
          }
          auto program=crown::io::read_sql_normalization(read_text(argv[2]));
          if (program.schema_version==1) program=crown::io::upgrade_sql_normalization(program,2);
          const auto tree=crown::io::read_tree(read_text(argv[3]),program.core_catalog,program.core);
          return crown::planner::lower_normalized(program,tree,options);
        }();
        std::cout << crown::io::write_physical(plan).dump(2) << '\n'; return 0;
      } catch (const crown::Error& error) {
        if (error.code()!="invalid_plan" && error.code()!="resource_limit") throw;
        std::cout << Json{{"schema_version",1},{"physical_lowered",false},{"status",error.code()},
            {"diagnostic",{{"code",error.code()},{"message",error.what()}}}}.dump(2) << '\n'; return 1;
      }
    }
    // Diagnostic logical-native events; full snapshots/invariant scans are explicit.
    if (argc >= 2 && std::string(argv[1]) == "support-trace") {
      if (argc!=4) throw crown::Error("usage","usage: crown support-trace PLAN.json LOGICAL_TRACE.json");
      const auto plan=crown::io::read_physical(read_text(argv[2]));
      const auto trace=crown::io::read_support_trace(read_text(argv[3]),plan);
      crown::runtime::SupportRuntime runtime(plan,trace.options);
      Json report{{"schema_version",2},{"backend","reference_incremental_journal"},{"update_contract","logical_native_set"},
          {"physical_sha256",plan.physical_sha256()},{"options",crown::io::write_support_options(trace.options)},
          {"status","complete"},{"diagnostic",nullptr},{"rejected_sequence",nullptr},
          {"initial",crown::io::write_support_snapshot(runtime.snapshot(),plan)},{"epochs",Json::array()}};
      for (const auto& update : trace.updates) {
        try {
          const auto effect=runtime.apply(update); runtime.check_invariants();
          report["epochs"].push_back({{"effect",crown::io::write_support_epoch(effect)},{"state",crown::io::write_support_snapshot(runtime.snapshot(),plan)}});
        } catch (const crown::Error& error) {
          if (error.code()!="resource_limit" && error.code()!="support_overflow") throw;
          report["status"]="update_rejected"; report["rejected_sequence"]=update.sequence;
          report["diagnostic"]={{"code",error.code()},{"message",error.what()}};
          report["final"]=crown::io::write_support_snapshot(runtime.snapshot(),plan);
          std::cout << report.dump(2) << '\n'; return 1;
        }
      }
      report["final"]=crown::io::write_support_snapshot(runtime.snapshot(),plan);
      std::cout << report.dump(2) << '\n'; return 0;
    }
    if (argc >= 2 && (std::string(argv[1]) == "validate-physical" || std::string(argv[1]) == "canonicalize-physical")) {
      if (argc != 3) throw crown::Error("usage","usage: crown {validate-physical|canonicalize-physical} PLAN.json");
      const auto plan=crown::io::read_physical(read_text(argv[2]));
      const auto output=std::string(argv[1])=="canonicalize-physical" ? crown::io::write_physical(plan) :
          Json{{"schema_version",1},{"physical_valid",true},{"execution_status",plan.guarantee().execution_status},{"physical_sha256",plan.physical_sha256()}};
      std::cout << output.dump(2) << '\n'; return 0;
    }
    if (argc >= 2 && (std::string(argv[1]) == "validate-catalog" || std::string(argv[1]) == "canonicalize-catalog")) {
      if (argc != 3) throw crown::Error("usage", "usage: crown {validate-catalog|canonicalize-catalog} CATALOG.json");
      const auto catalog = crown::io::read_catalog(read_text(argv[2]));
      const Json result = std::string(argv[1]) == "canonicalize-catalog" ? crown::io::write_catalog(catalog) :
          Json{{"schema_version", 1}, {"catalog_valid", true}, {"catalog_version", catalog.version}};
      std::cout << result.dump(2) << '\n';
      return 0;
    }
    // Remaining commands operate on typed set CQs and original structural evidence.
    if (argc < 3 || argc > 5) throw crown::Error("usage", "usage: crown parse-sql INPUT.sql; crown {oracle|validate-cq|canonicalize|classify|tree-oracle} QUERY.json; crown {validate-plan|verify-height} QUERY.json ARTIFACT.json");
    const std::string command = argv[1];
    if (command != "oracle" && command != "validate-cq" && command != "canonicalize" && command != "classify" && command != "validate-plan" && command != "tree-oracle" && command != "verify-height") throw crown::Error("usage", "unknown command: " + command);
    const bool argument_count = command == "verify-height" ? argc == 4 || argc == 5 : command == "tree-oracle" ? argc == 3 || argc == 4 : command == "validate-plan" ? argc == 4 : argc == 3;
    if (!argument_count) throw crown::Error("usage", "invalid arguments; tree-oracle and verify-height accept an optional final WORK_LIMIT");
    const auto document = crown::io::read_document(read_text(argv[2]));
    if (command == "canonicalize") {
      std::cout << crown::io::write_document(document).dump(2) << '\n';
    } else if (command == "validate-cq") {
      std::cout << Json{{"schema_version", 1}, {"cq_valid", true}, {"semantics", "set"}, {"structural_admission", "not_checked"}}.dump() << '\n';
    } else if (command == "tree-oracle") {
      const auto result = crown::planner::minimum_tree(document.catalog, document.query, search_limits(argc == 4 ? argv[3] : nullptr));
      std::cout << crown::io::write_oracle(result, document.catalog, document.query).dump(2) << '\n';
      return result.status == crown::planner::OracleStatus::proven_minimum ? 0 : 1;
    } else if (command == "verify-height") {
      crown::planner::CertificateReport report;
      try {
        const auto certificate = crown::io::read_height_certificate(read_text(argv[3]), document.catalog, document.query);
        report = crown::planner::verify_height_certificate(document.catalog, document.query, certificate, search_limits(argc == 5 ? argv[4] : nullptr));
      } catch (const crown::Error& error) {
        if (error.code() != "certificate_binding") throw;
        report.message = error.what();
      }
      std::cout << crown::io::write_certificate_report(report).dump(2) << '\n';
      return report.valid ? 0 : 1;
    } else if (command == "validate-plan") {
      const auto tree = crown::io::read_tree(read_text(argv[3]), document.catalog, document.query);
      const auto report = crown::planner::validate_tree(document.catalog, document.query, tree);
      std::cout << crown::io::write_validation(report, tree, document.query).dump(2) << '\n';
      return report.valid ? 0 : 1;
    } else if (command == "classify") {
      const auto analysis = crown::planner::analyze(document.catalog, document.query);
      std::cout << crown::io::write_structural_analysis(analysis,document.query).dump(2) << '\n';
    } else {
      crown::reference::Session session(document.catalog, document.query, document.initial);
      Json result{{"schema_version", document.schema_version}, {"backend", "reference_recompute"}, {"semantics", "set"},
                  {"initial", crown::io::write_relation(session.snapshot())}, {"epochs", Json::array()}};
      for (const auto& update : document.updates) result["epochs"].push_back(crown::io::write_epoch(session.apply(update)));
      std::cout << result.dump(2) << '\n';
    }
    return 0;
  } catch (const crown::Error& error) {
    std::cerr << Json{{"error", {{"code", error.code()}, {"message", error.what()}}}}.dump() << '\n';
    return error.code() == "parser_contract" || error.code() == "binding_contract" || error.code() == "normalization_contract" || error.code() == "admission_contract" || error.code() == "lowering_contract" || error.code() == "runtime_contract" ? 3 : 2;
  } catch (const std::exception& error) {
    std::cerr << Json{{"error", {{"code", "internal_error"}, {"message", error.what()}}}}.dump() << '\n';
    return 3;
  }
}

// Keep diagnostic failures inside the process boundary and flush once at exit.
int main(int argc, char** argv) {
  try {
    const int status=command_main(argc,argv);
    std::cout.flush();
    if(!std::cout && status==0) {
      std::cerr<<"{\"error\":{\"code\":\"io_error\",\"message\":\"command output flush failed\"}}\n";
      return 2;
    }
    return status;
  }catch(const std::bad_alloc&) {
    std::cerr<<"{\"error\":{\"code\":\"resource_limit\",\"message\":\"allocation failed\"}}\n";
    return 3;
  }catch(const std::exception&) {
    std::cerr<<"{\"error\":{\"code\":\"internal_error\",\"message\":\"command diagnostic failed\"}}\n";
    return 3;
  }
}
