#pragma once

#include "crown/io/tree.hpp"
#include "crown/planner/oracle.hpp"

namespace crown::io {
[[nodiscard]] Json write_oracle(const planner::OracleResult& result, const Catalog& catalog, const Query& query);
[[nodiscard]] planner::HeightCertificate read_height_certificate(std::string_view text, const Catalog& catalog, const Query& query);
[[nodiscard]] Json write_certificate_report(const planner::CertificateReport& report);
}  // namespace crown::io
