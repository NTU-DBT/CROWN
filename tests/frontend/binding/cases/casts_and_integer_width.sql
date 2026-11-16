SELECT CAST(a.id AS bigint) AS identity_id, CAST(1 AS bigint) AS cast_literal
FROM A AS a WHERE a.id = 1;
