// Shared replay loop for the per-query F-IVM plans in plans/*.cpp.
//
// Each plan .cpp includes its generated F-IVM header (namespace dbtoaster,
// type data_t) and defines a `Plan` struct with:
//   static constexpr const char* query, *plan;
//   static constexpr bool tagged;             // tagged_csv instead of graph_csv
//   static Count route(Query&, Edits&, ...);  // apply one physical edit, return relation updates
//   template <class Sink> static void enumerate(const Query&, Sink&);
// then calls run<Plan>(argc, argv) from main.
//
// Input: graph_csv lines "+,src,dst" / "-,src,dst", or tagged_csv lines
// "+,TAG,v1[,v2]"; a line "*" is an enumeration marker. Each relation update is
// one call of the generated batch trigger with a reusable 1-row DataChunk whose
// payload is +1 or -1. In mode "full" every marker enumerates the maintained
// (factorized) result and counts its rows; mode "none" only maintains. The
// final result after the stream is always enumerated (outside the timed loop).
#pragma once

#include <charconv>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace replay {
using Clock = std::chrono::steady_clock;
using Count = std::uint64_t;

inline int32_t integer(std::string_view input) {
    int32_t value{};
    const auto [end, error] = std::from_chars(input.data(), input.data() + input.size(), value);
    if (error != std::errc{} || end != input.data() + input.size()) {
        throw std::runtime_error("invalid input integer: " + std::string(input));
    }
    return value;
}

// Reusable one-row chunks: a binary (src,dst) chunk and a unary (x) chunk.
struct Edits {
    DataChunk binary;
    DataChunk unary;
    int32_t* src;
    int32_t* dst;
    int32_t* x;

    static DataChunk make(std::vector<SchemaField> schema) {
        DataSourceConfig source{};
        source.schema = std::move(schema);
        DataChunk chunk(source, 1);
        chunk.row_count = 1;
        chunk.payload.push_back(0);
        for (const auto& column : chunk.cols) {
            static_cast<Column<int32_t>&>(*column).data.push_back(0);
        }
        return chunk;
    }

    Edits()
        : binary(make({{"src", PrimitiveType::INT32}, {"dst", PrimitiveType::INT32}})),
          unary(make({{"x", PrimitiveType::INT32}})),
          src(&static_cast<Column<int32_t>&>(*binary.cols[0]).data[0]),
          dst(&static_cast<Column<int32_t>&>(*binary.cols[1]).data[0]),
          x(&static_cast<Column<int32_t>&>(*unary.cols[0]).data[0]) {}

    void sign(int32_t weight) {
        binary.payload[0] = weight;
        unary.payload[0] = weight;
    }
};

// Counts enumerated rows; optionally writes them as CSV for row-by-row checks.
struct Sink {
    Count rows = 0;
    std::ostream* capture = nullptr;

    template <class... Values>
    inline void operator()(const Values&... values) {
        ++rows;
        if (capture) {
            const char* separator = "";
            ((*capture << separator << values, separator = ","), ...);
            *capture << '\n';
        }
    }
};

template <class Plan>
int run(int argc, char** argv) {
    using Query = dbtoaster::data_t;
    if (argc < 3 || argc > 4) {
        throw std::runtime_error("usage: replay INPUT full|none [CAPTURE.csv]");
    }
    std::ifstream input(argv[1]);
    const std::string_view mode(argv[2]);
    if (!input) throw std::runtime_error("cannot open input");
    if ((mode != "full" && mode != "none") || (argc == 4 && mode != "full")) {
        throw std::runtime_error("invalid mode");
    }
    std::ofstream capture;
    if (argc == 4) {
        capture.open(argv[3]);
        capture.exceptions(std::ios::badbit | std::ios::failbit);
    }
    std::ostream* output = argc == 4 ? &capture : nullptr;

    auto* query = new Query();  // views live on the heap; never freed (process exits)
    query->on_system_ready_event();
    Edits edits;
    Count physical_inputs = 0, relation_updates = 0, markers = 0, snapshot_rows = 0;
    std::vector<std::pair<Count, Count>> snapshots;
    Clock::duration output_time{};
    const bool full = mode == "full";
    std::vector<int32_t> values;
    const auto start = Clock::now();
    for (std::string line; std::getline(input, line);) {
        if (line == "*") {
            ++markers;
            if (full) {
                const auto marker_start = Clock::now();
                if (output) *output << "*," << physical_inputs << '\n';
                Sink sink{0, output};
                Plan::enumerate(*query, sink);
                output_time += Clock::now() - marker_start;
                snapshots.emplace_back(physical_inputs, sink.rows);
                snapshot_rows += sink.rows;
            }
            continue;
        }
        if (line.size() < 4 || line[1] != ',' || (line[0] != '+' && line[0] != '-')) {
            throw std::runtime_error("invalid edit: " + line);
        }
        edits.sign(line[0] == '+' ? 1 : -1);
        const std::string_view raw(line);
        ++physical_inputs;
        if constexpr (Plan::tagged) {
            const auto tag_end = raw.find(',', 2);
            if (tag_end == std::string_view::npos) throw std::runtime_error("missing tagged values");
            const auto tag = raw.substr(2, tag_end - 2);
            values.clear();
            std::size_t begin = tag_end + 1;
            for (;;) {
                const auto end = raw.find(',', begin);
                values.push_back(integer(raw.substr(begin, end == std::string_view::npos ? end : end - begin)));
                if (end == std::string_view::npos) break;
                begin = end + 1;
            }
            relation_updates += Plan::route(*query, edits, tag, values);
        } else {
            const auto comma = raw.find(',', 2);
            if (comma == std::string_view::npos || raw.find(',', comma + 1) != std::string_view::npos) {
                throw std::runtime_error("invalid graph pair: " + line);
            }
            *edits.src = integer(raw.substr(2, comma - 2));
            *edits.dst = integer(raw.substr(comma + 1));
            relation_updates += Plan::route(*query, edits);
        }
    }
    const auto loop_time = Clock::now() - start;
    if (input.bad()) throw std::runtime_error("input read failed");
    if (output) *output << "*," << physical_inputs << '\n';
    Sink final_sink{0, output};
    Plan::enumerate(*query, final_sink);
    if (output) capture.close();
    using Ns = std::chrono::nanoseconds;
    std::cout << "{\"query\":\"" << Plan::query << "\",\"plan\":\"" << Plan::plan << "\",\"mode\":\"" << mode
              << "\",\"physical_inputs\":" << physical_inputs
              << ",\"relation_updates\":" << relation_updates
              << ",\"enumeration_markers\":" << markers
              << ",\"snapshot_rows\":" << snapshot_rows
              << ",\"final_rows\":" << final_sink.rows
              << ",\"loop_wall_ns\":" << std::chrono::duration_cast<Ns>(loop_time).count()
              << ",\"output_ns\":" << std::chrono::duration_cast<Ns>(output_time).count()
              << ",\"snapshots\":[";
    const char* separator = "";
    for (const auto& [sequence, rows] : snapshots) {
        std::cout << separator << "{\"sequence\":" << sequence << ",\"rows\":" << rows << '}';
        separator = ",";
    }
    std::cout << "]}\n";
    return 0;
}

template <class Plan>
int main_for(int argc, char** argv) {
    try {
        return run<Plan>(argc, argv);
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
}  // namespace replay
