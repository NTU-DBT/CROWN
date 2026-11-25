// star_cnt: SELECT COUNT(*), g1.a FROM g1,g2,g3,g4
//   WHERE g1.a=g2.a AND g1.a=g3.a AND g1.a=g4.a GROUP BY g1.a; every edge goes to all four.
// Numeric plan: SUM(1) GROUP BY A, variable order A -> {B, C, D, E}. The root view
// holds one count per group; rows = groups with a nonzero count.
#include "star_cnt.hpp"
#include "replay_common.hpp"

using namespace dbtoaster;
using replay::Count;

struct Plan {
    static constexpr const char* query = "star_cnt";
    static constexpr const char* plan = "numeric";
    static constexpr bool tagged = false;

    static Count route(data_t& q, replay::Edits& e) {
        q.on_batch_update_G1(e.binary);
        q.on_batch_update_G2(e.binary);
        q.on_batch_update_G3(e.binary);
        q.on_batch_update_G4(e.binary);
        return 4;
    }

    template <class Sink>
    static void enumerate(const data_t& q, Sink& sink) {
        for (const auto* row = q.get_V_A_GGGG1().head; row; row = row->nxt) {
            if (row->__av != 0) sink(row->A, row->__av);
        }
    }
};

int main(int argc, char** argv) { return replay::main_for<Plan>(argc, argv); }
