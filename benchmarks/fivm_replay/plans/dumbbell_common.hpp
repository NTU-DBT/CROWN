// Routing shared by dumbbell and dumbbell_full: CROWN's original source order
// m, lbc, lca, rde, rfd, lab, ref. m receives every edge; each triangle alias
// receives an edge only when src > T and dst > T (T = binding min_*_exclusive).
#pragma once

template <int32_t T>
replay::Count route_dumbbell(dbtoaster::data_t& q, replay::Edits& e) {
    q.on_batch_update_M(e.binary);
    if (*e.src <= T || *e.dst <= T) return 1;
    q.on_batch_update_LBC(e.binary);
    q.on_batch_update_LCA(e.binary);
    q.on_batch_update_RDE(e.binary);
    q.on_batch_update_RFD(e.binary);
    q.on_batch_update_LAB(e.binary);
    q.on_batch_update_REF(e.binary);
    return 7;
}
