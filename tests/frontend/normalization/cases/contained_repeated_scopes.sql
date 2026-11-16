SELECT DISTINCT a.id FROM A AS a
JOIN GateLeft AS l ON a.id = l.id
JOIN GateRight AS r ON l.id = r.id;
