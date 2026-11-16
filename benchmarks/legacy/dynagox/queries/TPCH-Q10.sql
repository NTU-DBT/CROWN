SELECT
    c_custkey, c_name, c_address, c_phone, c_acctbal, c_comment, n_name,
    SUM(l_extendedprice * (1 - l_discount)) AS revenue
FROM CUSTOMER, ORDERS, LINEITEM, NATION
WHERE c_custkey = o_custkey
  AND l_orderkey = o_orderkey
  AND o_orderdate >= DATE '1993-10-01'
  AND o_orderdate < DATE '1993-10-01' + INTERVAL '3' MONTH
  AND l_returnflag = 'R'
  AND c_nationkey = n_nationkey
GROUP BY c_custkey, c_name, c_address, c_phone, c_acctbal, c_comment, n_name;
