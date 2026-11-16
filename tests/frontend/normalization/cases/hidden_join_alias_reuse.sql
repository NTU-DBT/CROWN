SELECT DISTINCT j.k, x.label
FROM (A AS x JOIN B AS y ON x.id = y.id)
  AS j(k, ga, la, ib, gb, payload, day, amount)
CROSS JOIN A AS x
WHERE j.k = x.id;
