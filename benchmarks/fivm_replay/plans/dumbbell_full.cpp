// dumbbell_full: SELECT DISTINCT lab.a,lab.b,m.c,m.d,rde.e,ref.f FROM m,lbc,lca,rde,rfd,lab,ref
//   WHERE lab.b=lbc.b AND lbc.c=lca.c AND lca.a=lab.a AND m.c=lbc.c AND m.d=rde.d
//     AND rde.e=ref.e AND ref.f=rfd.f AND rfd.d=m.d
// Columns: m(c,d) lbc(b,c) lca(c,a) rde(d,e) rfd(f,d) lab(a,b) ref(e,f) = (src,dst).
// Triangle aliases filtered src > 32684 and dst > 32684.
// Signed factorized ring, cyclic variable order C -> {A -> B, D -> E -> F}
// (every relation on a root-to-leaf path); every variable lifted.
#include "dumbbell_full.hpp"
#include "replay_common.hpp"
#include "dumbbell_common.hpp"

using namespace dbtoaster;
using replay::Count;

struct Plan {
    static constexpr const char* query = "dumbbell_full";
    static constexpr const char* plan = "signed";
    static constexpr bool tagged = false;

    static Count route(data_t& q, replay::Edits& e) { return route_dumbbell<32684>(q, e); }

    template <class Sink>
    static void enumerate(const data_t& q, Sink& sink) {
        const auto& as = q.get_V_A_LLL1();
        const auto& bs = q.get_V_B_LL1();
        const auto& ds = q.get_V_D_RRRM1();
        const auto& es = q.get_V_E_RRR1();
        const auto& fs = q.get_V_FF_RR1();
        using FStore = decltype(fs.head->__av.store);
        struct Right { int32_t d, e; const FStore* f; };
        std::vector<Right> right;  // (d, e, f-store) for the current c
        for (const auto& [c_key, c_weight] : q.get_V_C_LLLRRRM1().store) {
            if (c_weight <= 0) continue;
            const auto [c] = c_key;
            const auto* a_rows = as.get(V_A_LLL1_entry{}.modify(c));
            const auto* d_rows = ds.get(V_D_RRRM1_entry{}.modify(c));
            if (!a_rows || !d_rows) continue;
            right.clear();
            for (const auto& [d_key, d_weight] : d_rows->__av.store) {
                if (d_weight <= 0) continue;
                const auto [d] = d_key;
                const auto* e_rows = es.get(V_E_RRR1_entry{}.modify(d));
                if (!e_rows) continue;
                for (const auto& [e_key, e_weight] : e_rows->__av.store) {
                    if (e_weight <= 0) continue;
                    const auto [e] = e_key;
                    if (const auto* f_rows = fs.get(V_FF_RR1_entry{}.modify(d, e))) right.push_back({d, e, &f_rows->__av.store});
                }
            }
            for (const auto& [a_key, a_weight] : a_rows->__av.store) {
                if (a_weight <= 0) continue;
                const auto [a] = a_key;
                const auto* b_rows = bs.get(V_B_LL1_entry{}.modify(c, a));
                if (!b_rows) continue;
                for (const auto& [b_key, b_weight] : b_rows->__av.store) {
                    if (b_weight <= 0) continue;
                    const auto b = std::get<0>(b_key);
                    for (const auto& r : right) {
                        for (const auto& [f_key, f_weight] : *r.f) {
                            if (f_weight > 0) sink(a, b, c, r.d, r.e, std::get<0>(f_key));
                        }
                    }
                }
            }
        }
    }
};

int main(int argc, char** argv) { return replay::main_for<Plan>(argc, argv); }
