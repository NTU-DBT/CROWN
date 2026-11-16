#pragma once

#include "crown/frontend/bind.hpp"
#include "crown/io/document.hpp"

namespace crown::io {
[[nodiscard]] Json write_sql_binding(const frontend::SqlBindResult& result);
// A success artifact is accepted only after bounded replay matches every field.
[[nodiscard]] frontend::BoundSql read_sql_binding(std::string_view text, frontend::BindLimits replay_limits = {});
// {schema_version:1,parameters:[{type,nullable?,collation?,decimal?}, ...]}
[[nodiscard]] frontend::BindOptions read_bind_options(std::string_view text);
}  // namespace crown::io
