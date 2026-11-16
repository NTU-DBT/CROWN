SELECT DISTINCT a.id FROM A AS a
WHERE (a.group_id = 10 OR a.group_id = 20) AND NOT (a.id = 99);
