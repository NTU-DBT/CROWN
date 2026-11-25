// length4_project: SELECT DISTINCT g2.b,g2.c,g3.d FROM g1,g2,g3,g4
//   WHERE g1.b=g2.b AND g2.c=g3.c AND g3.d=g4.d; g4 filter dst > -1 (every edge passes).
// Signed factorized ring, variable order C -> {B -> A, D -> E}; only B, C, D lifted.
#include "length4_project.hpp"
#include "replay_common.hpp"

using namespace dbtoaster;
using replay::Count;

struct Plan {
    static constexpr const char* query = "length4_project";
    static constexpr const char* plan = "signed";
    static constexpr bool tagged = false;

    static Count route(data_t& q, replay::Edits& e) {
        q.on_batch_update_G1(e.binary);
        q.on_batch_update_G2(e.binary);
        q.on_batch_update_G3(e.binary);
        if (*e.dst > -1) {
            q.on_batch_update_G4(e.binary);
            return 4;
        }
        return 3;
    }

    template <class Sink>
    static void enumerate(const data_t& q, Sink& sink) {
        const auto& bs = q.get_V_B_GG1();
        const auto& ds = q.get_V_D_GG1();
        for (const auto& [c_key, c_weight] : q.get_V_C_GGGG1().store) {
            if (c_weight <= 0) continue;
            const auto [c] = c_key;
            const auto* b_rows = bs.get(V_B_GG1_entry{}.modify(c));
            const auto* d_rows = ds.get(V_D_GG1_entry{}.modify(c));
            if (!b_rows || !d_rows) continue;
            for (const auto& [b_key, b_weight] : b_rows->__av.store) {
                if (b_weight <= 0) continue;
                const auto b = std::get<0>(b_key);
                for (const auto& [d_key, d_weight] : d_rows->__av.store) {
                    if (d_weight > 0) sink(b, c, std::get<0>(d_key));
                }
            }
        }
    }
};

int main(int argc, char** argv) { return replay::main_for<Plan>(argc, argv); }
