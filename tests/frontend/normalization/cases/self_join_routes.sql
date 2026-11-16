SELECT DISTINCT l.id, r.label FROM A AS l JOIN A AS r
  ON l.group_id = r.group_id
WHERE l.id = 1 AND r.id = 2;
