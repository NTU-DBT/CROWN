SELECT DISTINCT "a0"."c0" AS "x0", "a0"."c1" AS "x1", "a1"."c1" AS "x2" FROM "edge" AS "a0" CROSS JOIN "edge" AS "a1" WHERE "a1"."c0" = "a0"."c1";
