SELECT DISTINCT t.id FROM Triple AS t
WHERE t.first_key = t.second_key AND t.second_key = t.third_key;
