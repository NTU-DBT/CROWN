SELECT DISTINCT e1.src AS x, e1.dst AS y, e2.dst AS z FROM edge AS e1 JOIN edge AS e2 ON e1.dst = e2.src;
