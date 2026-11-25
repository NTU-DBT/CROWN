// dumbbell: SELECT DISTINCT m.c,m.d FROM m,lbc,lca,rde,rfd,lab,ref (same body as dumbbell_full).
// Triangle aliases filtered src > 0 and dst > 0.
// Signed factorized ring, cyclic variable order C -> {D -> E -> F, A -> B};
// only C and D lifted. Rows = distinct (c,d) with weight > 0.
#include "dumbbell.hpp"
#include "replay_common.hpp"
#include "dumbbell_common.hpp"

using namespace dbtoaster;
using replay::Count;

struct Plan {
    static constexpr const char* query = "dumbbell";
    static constexpr const char* plan = "signed";
    static constexpr bool tagged = false;

    static Count route(data_t& q, replay::Edits& e) { return route_dumbbell<0>(q, e); }

    template <class Sink>
    static void enumerate(const data_t& q, Sink& sink) {
        const auto& ds = q.get_V_D_RRRM1();
        for (const auto& [c_key, c_weight] : q.get_V_C_RRRMLLL1().store) {
            if (c_weight <= 0) continue;
            const auto [c] = c_key;
            const auto* d_rows = ds.get(V_D_RRRM1_entry{}.modify(c));
            if (!d_rows) continue;
            for (const auto& [d_key, d_weight] : d_rows->__av.store) {
                if (d_weight > 0) sink(c, std::get<0>(d_key));
            }
        }
    }
};

int main(int argc, char** argv) { return replay::main_for<Plan>(argc, argv); }
