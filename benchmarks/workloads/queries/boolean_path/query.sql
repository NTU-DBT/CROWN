SELECT EXISTS(SELECT 1 FROM "r0" AS "a0" CROSS JOIN "r1" AS "a1" CROSS JOIN "r2" AS "a2" WHERE "a1"."c0" = "a0"."c1" AND "a2"."c0" = "a1"."c1");
