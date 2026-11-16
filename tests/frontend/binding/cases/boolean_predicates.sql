SELECT a.id AS item FROM A AS a
WHERE (a.flag IS NOT TRUE OR a.note IS NULL) AND a.id = $1;
