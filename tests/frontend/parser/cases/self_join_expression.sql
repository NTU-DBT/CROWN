SELECT l.id, r.id AS right_id
FROM person AS l, person AS r
WHERE l.parent_id::bigint = r.id AND (l.score + 1) >= 10;
