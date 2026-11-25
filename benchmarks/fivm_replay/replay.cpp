// Use the generated C++ triggers directly to preserve CROWN's edit and marker order.
#include "generated.hpp"

#include <charconv>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace {
using Clock = std::chrono::steady_clock;
using Query = dbtoaster::data_t;
using Count = std::uint64_t;

int32_t integer(std::string_view input) {
    int32_t value{};
    const auto [end, error] = std::from_chars(input.data(), input.data() + input.size(), value);
    if (error != std::errc{} || end != input.data() + input.size()) {
        throw std::runtime_error("invalid input integer");
    }
    return value;
}

DataChunk make_edit() {
    DataSourceConfig source{};
    source.schema = {{"src", PrimitiveType::INT32}, {"dst", PrimitiveType::INT32}};
    DataChunk edit(source, 1);
    edit.row_count = 1;
    edit.payload.push_back(0);
    for (const auto& column : edit.cols) {
        static_cast<Column<int32_t>&>(*column).data.push_back(0);
    }
    return edit;
}

Count enumerate(const Query& query, std::ostream* capture) {
    Count rows = 0;
    const auto emit = [&](int32_t a, int32_t b, int32_t c, int32_t d) {
        ++rows;
        if (capture) {
            *capture << a << ',' << b << ',' << c << ',' << d << '\n';
        }
    };
#ifdef FIVM_FACTOR_PAYLOAD
    const auto& left = query.get_V_A_G1();
    const auto& middle = query.get_V_C_GG1();
    const auto& right = query.get_V_D_G1();
    for (const auto& [b_key, b_weight] : query.get_V_B_GGG1().store) {
        if (b_weight <= 0) {
            continue;
        }
        const auto [b] = b_key;
        const auto* a_rows = left.get(dbtoaster::V_A_G1_entry{}.modify(b));
        const auto* c_rows = middle.get(dbtoaster::V_C_GG1_entry{}.modify(b));
        if (!a_rows || !c_rows) {
            continue;
        }
        for (const auto& [c_key, c_weight] : c_rows->__av.store) {
            if (c_weight <= 0) {
                continue;
            }
            const auto [c] = c_key;
            const auto* d_rows = right.get(dbtoaster::V_D_G1_entry{}.modify(c));
            if (!d_rows) {
                continue;
            }
            for (const auto& [a_key, a_weight] : a_rows->__av.store) {
                for (const auto& [d_key, d_weight] : d_rows->__av.store) {
                    if (a_weight > 0 && d_weight > 0) {
                        emit(std::get<0>(a_key), b, c, std::get<0>(d_key));
                    }
                }
            }
        }
    }
#else
    for (auto* row = query.get_V_B_GGG1().head; row; row = row->nxt) {
        if (row->__av != 1) {
            throw std::runtime_error("expected unit weight in full join");
        }
        emit(row->A, row->B, row->C, row->D);
    }
#endif
    return rows;
}

int replay(int argc, char** argv) {
    if (argc < 3 || argc > 4) {
        throw std::runtime_error("usage: replay INPUT full|none [CAPTURE.csv]");
    }
    std::ifstream input(argv[1]);
    const std::string_view mode(argv[2]);
    if (!input || (mode != "full" && mode != "none") || (argc == 4 && mode != "full")) {
        throw std::runtime_error("cannot open input or invalid mode");
    }
    std::ofstream capture;
    if (argc == 4) {
        capture.open(argv[3]);
        capture.exceptions(std::ios::badbit | std::ios::failbit);
    }
    auto* output = argc == 4 ? &capture : nullptr;

    Query query;
    query.on_system_ready_event();
    auto edit = make_edit();
    auto& src = static_cast<Column<int32_t>&>(*edit.cols[0]).data[0];
    auto& dst = static_cast<Column<int32_t>&>(*edit.cols[1]).data[0];
    Count physical_inputs = 0, relation_updates = 0, markers = 0, snapshot_rows = 0;
    std::vector<std::pair<Count, Count>> snapshots;
    Clock::duration output_time{};
    const auto start = Clock::now();
    for (std::string line; std::getline(input, line);) {
        if (line == "*") {
            ++markers;
            if (mode == "full") {
                const auto marker_start = Clock::now();
                if (output) {
                    *output << "*," << physical_inputs << '\n';
                }
                const auto rows = enumerate(query, output);
                output_time += Clock::now() - marker_start;
                snapshots.emplace_back(physical_inputs, rows);
                snapshot_rows += rows;
            }
            continue;
        }
        const auto comma = line.find(',', 2);
        if (line.size() < 5 || line[1] != ',' || comma == std::string::npos ||
            (line[0] != '+' && line[0] != '-')) {
            throw std::runtime_error("invalid edit");
        }
        const std::string_view raw(line);
        src = integer(raw.substr(2, comma - 2));
        dst = integer(raw.substr(comma + 1));
        edit.payload[0] = line[0] == '+' ? 1 : -1;
        ++physical_inputs;
        query.on_batch_update_G1(edit);
        query.on_batch_update_G2(edit);
        relation_updates += 2;
        if (dst > 32684) {
            query.on_batch_update_G3(edit);
            ++relation_updates;
        }
    }
    const auto loop_time = Clock::now() - start;
    if (input.bad()) {
        throw std::runtime_error("input read failed");
    }
    if (output) {
        *output << "*," << physical_inputs << '\n';
    }
    const auto final_rows = enumerate(query, output);
    if (output) {
        capture.close();
    }
    using Ns = std::chrono::nanoseconds;
    std::cout << "{\"physical_inputs\":" << physical_inputs
              << ",\"relation_updates\":" << relation_updates
              << ",\"enumeration_markers\":" << markers
              << ",\"snapshot_rows\":" << snapshot_rows
              << ",\"final_rows\":" << final_rows
              << ",\"loop_wall_ns\":" << std::chrono::duration_cast<Ns>(loop_time).count()
              << ",\"output_ns\":" << std::chrono::duration_cast<Ns>(output_time).count()
              << ",\"snapshots\":[";
    const char* separator = "";
    for (const auto [sequence, rows] : snapshots) {
        std::cout << separator << "{\"sequence\":" << sequence << ",\"rows\":" << rows << '}';
        separator = ",";
    }
    std::cout << "]}\n";
    return 0;
}
}  // namespace

int main(int argc, char** argv) {
    try {
        return replay(argc, argv);
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
