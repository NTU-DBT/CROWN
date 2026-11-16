SELECT j.join_id, j.left_only, j.right_only
FROM (A AS l JOIN B AS r USING (id, shard)) AS j(join_id)
WHERE j.join_id = 1;
