SELECT
    ca_zip, SUM(cs_sales_price)
FROM catalog_sales, customer, customer_address, date_dim
WHERE cs_bill_customer_sk = c_customer_sk
  AND c_current_addr_sk = ca_address_sk
  AND cs_sold_date_sk = d_date_sk
GROUP BY ca_zip;
