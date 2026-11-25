// length3_project: SELECT DISTINCT g2.b,g2.c FROM g1,g2,g3
//   WHERE g1.b=g2.b AND g2.c=g3.c; g3 filter dst > -1 (every edge passes).
// Signed factorized ring, variable order B -> {C -> D, A}; only B and C lifted,
// A and D are marginalised into counts. Rows = distinct (b,c) with weight > 0.
#include "length3_project.hpp"
#include "replay_common.hpp"

using namespace dbtoaster;
using replay::Count;

struct Plan {
    static constexpr const char* query = "length3_project";
    static constexpr const char* plan = "signed";
    static constexpr bool tagged = false;

    static Count route(data_t& q, replay::Edits& e) {
        q.on_batch_update_G1(e.binary);
        q.on_batch_update_G2(e.binary);
        if (*e.dst > -1) {
            q.on_batch_update_G3(e.binary);
            return 3;
        }
        return 2;
    }

    template <class Sink>
    static void enumerate(const data_t& q, Sink& sink) {
        const auto& cs = q.get_V_C_GG1();
        for (const auto& [b_key, b_weight] : q.get_V_B_GGG1().store) {
            if (b_weight <= 0) continue;
            const auto [b] = b_key;
            const auto* c_rows = cs.get(V_C_GG1_entry{}.modify(b));
            if (!c_rows) continue;
            for (const auto& [c_key, c_weight] : c_rows->__av.store) {
                if (c_weight > 0) sink(b, std::get<0>(c_key));
            }
        }
    }
};

int main(int argc, char** argv) { return replay::main_for<Plan>(argc, argv); }
