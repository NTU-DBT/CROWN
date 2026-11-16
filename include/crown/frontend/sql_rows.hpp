#pragma once

#include "crown/frontend/bind.hpp"
#include "crown/resource/memory.hpp"
#include "crown/storage/accounted_row.hpp"
#include <memory>
#include <span>
#include <utility>

namespace crown::frontend {
namespace detail { class SqlRowsCompiler; }
using SqlRowCell = std::optional<storage::ScalarView>;

// These spans borrow a factory-owned immutable program. NULL belongs to this
// SQL boundary; derived core fields are always ordinary non-null scalars.
struct SqlRowsColumn { std::string_view name; SqlType type; };
struct SqlRowsSource {
  TableId table;
  std::string_view name;
  std::uint64_t schema_version;
  std::span<const SqlRowsColumn> columns;
  std::span<const std::size_t> constraints;
  std::span<const OccurrenceId> occurrences;
};
struct SqlRowsConstraint {
  TableId source;
  std::string_view name;
  // A missing parent denotes UNIQUE with NULLS DISTINCT. Foreign columns are
  // ordered to match that parent; NULL foreign keys use MATCH SIMPLE. Empty
  // keys retain the catalog's at-most-one / target-nonempty extension.
  std::span<const ColumnId> columns;
  std::optional<std::size_t> parent;
  std::span<const std::size_t> referenced_by;
};
struct SqlRowsInput { ExpressionId target; ColumnId column; };
struct SqlRowsOperation {
  ExpressionId target;
  SqlOperator operation;
  std::span<const ExpressionId> arguments;
};
struct SqlRowsEquality { ColumnId left, right; };
// The constant slot can contain SQL NULL for an IS NULL guard. Ordinary
// equality with NULL is compiled as contradiction, never as matching NULLs.
struct SqlRowsConstant { ColumnId column; ExpressionId constant; };
enum class SqlRowsFieldKind { value, nullable_payload, presence };
struct SqlRowsProjection {
  VariableId variable;
  ExpressionId expression;
  ScalarType type;
  SqlRowsFieldKind kind = SqlRowsFieldKind::value;
};
struct SqlRowsOccurrence {
  OccurrenceId occurrence;
  TableId source;
  std::span<const SqlRowsInput> inputs;
  std::span<const SqlRowsOperation> operations;
  std::span<const ColumnId> non_null_columns;
  std::span<const SqlRowsEquality> equal_columns;
  std::span<const SqlRowsConstant> constant_columns;
  std::span<const ExpressionId> predicates;
  // Ascending variable IDs: the actual native node scope/input order.
  std::span<const SqlRowsProjection> projection;
};
struct SqlRowsResultField {
  std::size_t payload;
  std::optional<std::size_t> presence;
};
struct SqlRowsExistsOutput {};
struct SqlRowsOutput {
  std::string_view name;
  SqlType type;
  // ExpressionId selects a constant initial slot, including NULL.
  std::variant<SqlRowsResultField, ExpressionId, SqlRowsExistsOutput> value;
};
struct SqlRowsCore { Catalog catalog; Query query; };
struct SqlRowsBindOptions {
  BindOptions binding;
  std::vector<std::optional<Value>> parameters;
  std::optional<std::uint64_t> work_limit = 1000000;
  std::uint64_t memory_limit_bytes = 16ULL * 1024 * 1024;
  // Recovery opts into an additional accounted copy of the canonical binding.
  // Ordinary programs retain only the source hash and executable metadata.
  bool retain_binding_image = false;
};

// A separate SQL family preserves frozen normalization v1/v2 meanings. Source
// identity includes exact SQL, typed parameters and catalog metadata. It is a
// conservative source binding, not an alias-insensitive F05 canonical key.
class SqlRowsProgram {
  struct Data;
 public:
  SqlRowsProgram() noexcept = default;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] static SqlRowsProgram freeze(const resource::MemoryAccount&, const SqlRowsProgram&);
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
  [[nodiscard]] std::string_view source() const &;
  std::string_view source() const && = delete;
  // Empty unless binding opted into retention. Otherwise exact genuine
  // source/catalog/typed-parameter CBOR, owned by immutable account metadata.
  // Cold retention/copy is linear in the image; the getter only borrows it.
  [[nodiscard]] std::string_view binding_image() const &;
  std::string_view binding_image() const && = delete;
  [[nodiscard]] std::string_view source_sha256() const &;
  std::string_view source_sha256() const && = delete;
  [[nodiscard]] SqlSemantics semantics() const;
  [[nodiscard]] SqlWrapper wrapper() const;
  [[nodiscard]] bool contradiction() const;
  [[nodiscard]] std::uint64_t work() const;
  [[nodiscard]] std::span<const SqlRowsSource> sources() const &;
  std::span<const SqlRowsSource> sources() const && = delete;
  [[nodiscard]] std::span<const SqlRowsConstraint> constraints() const &;
  std::span<const SqlRowsConstraint> constraints() const && = delete;
  [[nodiscard]] std::span<const SqlRowsOccurrence> occurrences() const &;
  std::span<const SqlRowsOccurrence> occurrences() const && = delete;
  [[nodiscard]] std::span<const SqlRowsOutput> outputs() const &;
  std::span<const SqlRowsOutput> outputs() const && = delete;
  [[nodiscard]] std::span<const SqlRowCell> initial_values() const &;
  std::span<const SqlRowCell> initial_values() const && = delete;
  // Explicit cold DTO export for tree choice. Runtime creation must export
  // again from the actual program; a caller-mutated export is not authority.
  [[nodiscard]] SqlRowsCore export_core() const;
 private:
  friend class detail::SqlRowsCompiler;
  explicit SqlRowsProgram(std::shared_ptr<const Data> value) noexcept : data_(std::move(value)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
using SqlRowsBindResult = std::variant<SqlRowsProgram, BindingDiagnostic>;

// Parsing/binding workspace is cold caller/compiler work. Retained metadata
// and constants use the finite compiler account; _into never creates a cap.
// Compiler allocation/account failures propagate. Parsing/binding retain
// bind_sql's existing diagnostic/exception boundary; SQL rejection is diagnostic.
[[nodiscard]] SqlRowsBindResult bind_sql_rows(std::string_view, const Catalog&, const SqlRowsBindOptions& = {});
[[nodiscard]] SqlRowsBindResult bind_sql_rows_into(const resource::MemoryAccount&,
    std::string_view, const Catalog&, const SqlRowsBindOptions& = {});
}  // namespace crown::frontend
