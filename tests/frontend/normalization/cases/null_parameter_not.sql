SELECT DISTINCT a.id FROM A AS a
WHERE NOT (a.id = $1 OR a.label = 'missing');
