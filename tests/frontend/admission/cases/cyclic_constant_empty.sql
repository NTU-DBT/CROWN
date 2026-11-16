SELECT DISTINCT r.x,r.y,s.z FROM r JOIN s USING(y) JOIN t ON t.x=r.x AND t.z=s.z WHERE FALSE
