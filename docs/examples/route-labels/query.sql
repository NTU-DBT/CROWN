SELECT DISTINCT b.dst AS terminal, l.label AS category
FROM edge AS a
JOIN edge AS b ON a.dst = b.src
JOIN labels AS l ON b.dst = l.id
WHERE a.kind = 'kept';
