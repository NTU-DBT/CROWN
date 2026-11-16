SELECT
    o_orderkey, o_orderdate, o_shippriority,
    SUM(l_extendedprice * (1 - l_discount)) as revenue
FROM CUSTOMER, ORDERS, LINEITEM
WHERE c_mktsegment = 'BUILDING'
  AND c_custkey = o_custkey
  AND l_orderkey = o_orderkey
  AND o_orderdate < DATE '1995-03-15'
  AND l_shipdate > DATE '1995-03-15'
GROUP BY o_orderkey, o_orderdate, o_shippriority;
