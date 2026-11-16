SELECT DISTINCT 7 AS marker, a.id AS first_id, a.id AS again_id
FROM A AS a WHERE a.id = 1 OR a.id = 2;
