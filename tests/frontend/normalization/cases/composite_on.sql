SELECT DISTINCT a.id FROM A AS a JOIN B AS b
  ON a.id = b.id AND a.group_id = b.group_id;
