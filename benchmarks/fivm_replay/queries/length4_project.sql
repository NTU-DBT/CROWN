IMPORT DTREE FROM FILE 'length4_project.order';

CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

CREATE STREAM G1(A INT, B INT) FROM FILE 'unused.g1' LINE DELIMITED CSV;
CREATE STREAM G2(B INT, C INT) FROM FILE 'unused.g2' LINE DELIMITED CSV;
CREATE STREAM G3(C INT, D INT) FROM FILE 'unused.g3' LINE DELIMITED CSV;
CREATE STREAM G4(D INT, E INT) FROM FILE 'unused.g4' LINE DELIMITED CSV;

SELECT SUM(
  [lift<0>: RingFactorizedRelation<[0,INT]>](C) *
  [lift<1>: RingFactorizedRelation<[1,INT]>](B) *
  [lift<2>: RingFactorizedRelation<[2,INT]>](D)
)
FROM G1 NATURAL JOIN G2 NATURAL JOIN G3 NATURAL JOIN G4;
