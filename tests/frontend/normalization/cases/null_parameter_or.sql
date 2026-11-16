SELECT DISTINCT a.id FROM A AS a
WHERE a.id = $1 OR a.label = 'beta';
