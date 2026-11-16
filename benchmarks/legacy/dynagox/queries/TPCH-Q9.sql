SELECT
    nation, o_year,
    SUM(v1) AS value1,
    SUM(v2) AS value2
FROM (
         SELECT
             n_name AS nation,
             EXTRACT(YEAR FROM o_orderdate) AS o_year,
             l_extendedprice * (1 - l_discount) AS v1,
             ps_supplycost * l_quantity AS v2
         FROM PART, SUPPLIER, LINEITEM, PARTSUPP, ORDERS, NATION
         WHERE s_suppkey = l_suppkey
           AND ps_suppkey = l_suppkey
           AND ps_partkey = l_partkey
           AND p_partkey = l_partkey
           AND o_orderkey = l_orderkey
           AND s_nationkey = n_nationkey
           AND p_name LIKE '%green%'
     ) AS PROFIT
GROUP BY nation, o_year;
