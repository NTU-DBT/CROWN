// length3_filter: SELECT DISTINCT g1.a,g1.b,g2.c,g3.d FROM g1,g2,g3
//   WHERE g1.b=g2.b AND g2.c=g3.c; g3 receives an edge only when dst > 32684.
// Signed factorized ring, variable order B -> {A, C -> D}; every variable lifted.
#include "length3_filter.hpp"
#include "replay_common.hpp"

using namespace dbtoaster;
using replay::Count;

struct Plan {
    static constexpr const char* query = "length3_filter";
    static constexpr const char* plan = "signed";
    static constexpr bool tagged = false;

    static Count route(data_t& q, replay::Edits& e) {
        q.on_batch_update_G1(e.binary);
        q.on_batch_update_G2(e.binary);
        if (*e.dst > 32684) {
            q.on_batch_update_G3(e.binary);
            return 3;
        }
        return 2;
    }

    template <class Sink>
    static void enumerate(const data_t& q, Sink& sink) {
        const auto& left = q.get_V_A_G1();
        const auto& middle = q.get_V_C_GG1();
        const auto& right = q.get_V_D_G1();
        for (const auto& [b_key, b_weight] : q.get_V_B_GGG1().store) {
            if (b_weight <= 0) continue;
            const auto [b] = b_key;
            const auto* a_rows = left.get(V_A_G1_entry{}.modify(b));
            const auto* c_rows = middle.get(V_C_GG1_entry{}.modify(b));
            if (!a_rows || !c_rows) continue;
            for (const auto& [c_key, c_weight] : c_rows->__av.store) {
                if (c_weight <= 0) continue;
                const auto [c] = c_key;
                const auto* d_rows = right.get(V_D_G1_entry{}.modify(c));
                if (!d_rows) continue;
                for (const auto& [a_key, a_weight] : a_rows->__av.store) {
                    if (a_weight <= 0) continue;
                    for (const auto& [d_key, d_weight] : d_rows->__av.store) {
                        if (d_weight > 0) sink(std::get<0>(a_key), b, c, std::get<0>(d_key));
                    }
                }
            }
        }
    }
};

int main(int argc, char** argv) { return replay::main_for<Plan>(argc, argv); }
