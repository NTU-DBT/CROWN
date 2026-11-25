// TwoComb: SELECT DISTINCT g1.a,g1.b,g2.c,g3.d FROM g1,g2,g3,v1,v2
//   WHERE g1.b=g2.b AND g2.c=g3.c AND v1.a=g1.a AND v2.d=g3.d.
// Tagged input: G -> g1,g2,g3; V1 -> v1; V2 -> v2 (no filters).
// Signed factorized ring, variable order B -> {A, C -> D}; every variable lifted.
#include "twocomb.hpp"
#include "replay_common.hpp"

using namespace dbtoaster;
using replay::Count;

struct Plan {
    static constexpr const char* query = "TwoComb";
    static constexpr const char* plan = "signed";
    static constexpr bool tagged = true;

    static Count route(data_t& q, replay::Edits& e, std::string_view tag, const std::vector<int32_t>& v) {
        if (tag == "G") {
            if (v.size() != 2) throw std::runtime_error("G expects two values");
            *e.src = v[0];
            *e.dst = v[1];
            q.on_batch_update_G1(e.binary);
            q.on_batch_update_G2(e.binary);
            q.on_batch_update_G3(e.binary);
            return 3;
        }
        if (v.size() != 1) throw std::runtime_error("V1/V2 expect one value");
        *e.x = v[0];
        if (tag == "V1") {
            q.on_batch_update_V1(e.unary);
        } else if (tag == "V2") {
            q.on_batch_update_V2(e.unary);
        } else {
            throw std::runtime_error("unknown tagged relation");
        }
        return 1;
    }

    template <class Sink>
    static void enumerate(const data_t& q, Sink& sink) {
        const auto& left = q.get_V_A_GV1();
        const auto& middle = q.get_V_C_GVG1();
        const auto& right = q.get_V_D_GV1();
        for (const auto& [b_key, b_weight] : q.get_V_B_GVGVG1().store) {
            if (b_weight <= 0) continue;
            const auto [b] = b_key;
            const auto* a_rows = left.get(V_A_GV1_entry{}.modify(b));
            const auto* c_rows = middle.get(V_C_GVG1_entry{}.modify(b));
            if (!a_rows || !c_rows) continue;
            for (const auto& [c_key, c_weight] : c_rows->__av.store) {
                if (c_weight <= 0) continue;
                const auto [c] = c_key;
                const auto* d_rows = right.get(V_D_GV1_entry{}.modify(c));
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
