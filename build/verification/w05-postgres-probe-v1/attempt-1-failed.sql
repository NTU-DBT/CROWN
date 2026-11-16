-- PostgreSQL 16 local capability probe; all decimal outputs are text/JSON.
SELECT json_build_object(
  'server_version', current_setting('server_version'),
  'server_version_num', current_setting('server_version_num'),
  'current_user', current_user,
  'server_encoding', current_setting('server_encoding'),
  'listen_addresses', current_setting('listen_addresses'),
  'unix_socket_directories', current_setting('unix_socket_directories'),
  'port', current_setting('port')
)::text;

CREATE TEMP TABLE exact_numeric_probe (n numeric);
INSERT INTO exact_numeric_probe(n) VALUES
  ('99999999999999999999999999999999999999'::numeric),
  ('0.00000000000000000000000000000000000001'::numeric);
SELECT json_build_object(
  'column_type', (SELECT pg_typeof(n)::text FROM exact_numeric_probe LIMIT 1),
  'typmod', (SELECT atttypmod FROM pg_attribute
    WHERE attrelid = 'pg_temp.exact_numeric_probe'::regclass
      AND attname = 'n' AND attnum > 0 AND NOT attisdropped),
  'values_ascending', (SELECT json_agg(n::text ORDER BY n) FROM exact_numeric_probe),
  'tiny_equal_exactly', EXISTS (SELECT 1 FROM exact_numeric_probe
    WHERE n = '0.00000000000000000000000000000000000001'::numeric),
  'integer_equal_exactly', EXISTS (SELECT 1 FROM exact_numeric_probe
    WHERE n = '99999999999999999999999999999999999999'::numeric),
  'integer_greater_than_tiny', (SELECT max(n) > min(n) FROM exact_numeric_probe)
)::text;

SELECT json_build_object(
  'null_equal_is_unknown', (NULL::numeric = NULL::numeric) IS UNKNOWN,
  'null_equal_is_null', (NULL::numeric = NULL::numeric) IS NULL,
  'null_equal_text', (NULL::numeric = NULL::numeric)::text
)::text;

CREATE TEMP TABLE null_group_probe (v text);
INSERT INTO null_group_probe(v) VALUES (NULL), (NULL), ('x'), ('x'), ('y');
SELECT json_build_object(
  'grouped', (SELECT json_agg(json_build_object('value', v, 'count', n)
                              ORDER BY v NULLS FIRST)
              FROM (SELECT v, count(*) AS n FROM null_group_probe GROUP BY v) AS g),
  'distinct_values', (SELECT json_agg(value ORDER BY value NULLS FIRST)
                      FROM (SELECT DISTINCT v AS value FROM null_group_probe) AS d)
)::text;

SELECT json_build_object(
  'date_value', DATE '2024-02-29'::text,
  'boolean_true', TRUE,
  'boolean_false', FALSE,
  'collation_name', (SELECT collname::text FROM pg_collation WHERE oid = 'C'::regcollation),
  'C_same_text_equal', ('A'::text COLLATE "C" = 'A'::text COLLATE "C"),
  'C_upper_before_lower', ('A'::text COLLATE "C" < 'a'::text COLLATE "C"),
  'C_ascii_before_utf8', ('z'::text COLLATE "C" < 'é'::text COLLATE "C")
)::text;
