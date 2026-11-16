SELECT EXISTS (SELECT 1 FROM flags AS f WHERE f.active = TRUE) AS found;
