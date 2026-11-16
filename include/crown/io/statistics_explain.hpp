#pragma once
#include "crown/observability/statistics_explain.hpp"

namespace crown::io {
struct StatisticsTextLimits { std::size_t bytes=16*1024*1024,items=1000000; };
// Items count each JSON value (object, array, scalar/null), excluding field
// names. Human output adds a fixed introduction to the same complete JSON.
// Both limits are checked before publication; failure returns no partial text.
// Native byte payloads use hex; internal labels are ASCII. Report storage and
// string capacity are separate from final encoded length.
struct StatisticsText { std::string text; std::size_t items{}; };
[[nodiscard]] StatisticsText write_statistics_json(const observability::StatisticsExplanation&,StatisticsTextLimits={});
[[nodiscard]] StatisticsText write_statistics_text(const observability::StatisticsExplanation&,StatisticsTextLimits={});
}
