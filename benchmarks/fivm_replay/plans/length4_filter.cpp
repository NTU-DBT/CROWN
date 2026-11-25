// length4_filter: SELECT DISTINCT g1.a,g1.b,g2.c,g3.d,g4.e FROM g1,g2,g3,g4
//   WHERE g1.b=g2.b AND g2.c=g3.c AND g3.d=g4.d; g4 receives an edge only when dst > 32684.
// Signed factorized ring, variable order C -> {B -> A, D -> E}; every variable lifted.
#include "length4_filter.hpp"
#include "replay_common.hpp"

using namespace dbtoaster;
using replay::Count;

struct Plan {
    static constexpr const char* query = "length4_filter";
    static constexpr const char* plan = "signed";
    static constexpr bool tagged = false;

    static Count route(data_t& q, replay::Edits& e) {
        q.on_batch_update_G1(e.binary);
        q.on_batch_update_G2(e.binary);
        q.on_batch_update_G3(e.binary);
        if (*e.dst > 32684) {
            q.on_batch_update_G4(e.binary);
            return 4;
        }
        return 3;
    }

    template <class Sink>
    static void enumerate(const data_t& q, Sink& sink) {
        const auto& bs = q.get_V_B_GG1();
        const auto& as = q.get_V_A_G1();
        const auto& ds = q.get_V_D_GG1();
        const auto& es = q.get_V_E_G1();
        using EStore = decltype(es.head->__av.store);
        std::vector<std::pair<int32_t, const EStore*>> right;  // (d, e-store) for the current c
        for (const auto& [c_key, c_weight] : q.get_V_C_GGGG1().store) {
            if (c_weight <= 0) continue;
            const auto [c] = c_key;
            const auto* b_rows = bs.get(V_B_GG1_entry{}.modify(c));
            const auto* d_rows = ds.get(V_D_GG1_entry{}.modify(c));
            if (!b_rows || !d_rows) continue;
            right.clear();
            for (const auto& [d_key, d_weight] : d_rows->__av.store) {
                if (d_weight <= 0) continue;
                const auto [d] = d_key;
                if (const auto* e_rows = es.get(V_E_G1_entry{}.modify(d))) right.emplace_back(d, &e_rows->__av.store);
            }
            for (const auto& [b_key, b_weight] : b_rows->__av.store) {
                if (b_weight <= 0) continue;
                const auto [b] = b_key;
                const auto* a_rows = as.get(V_A_G1_entry{}.modify(b));
                if (!a_rows) continue;
                for (const auto& [a_key, a_weight] : a_rows->__av.store) {
                    if (a_weight <= 0) continue;
                    const auto a = std::get<0>(a_key);
                    for (const auto& [d, e_store] : right) {
                        for (const auto& [e_key, e_weight] : *e_store) {
                            if (e_weight > 0) sink(a, b, c, d, std::get<0>(e_key));
                        }
                    }
                }
            }
        }
    }
};

int main(int argc, char** argv) { return replay::main_for<Plan>(argc, argv); }
