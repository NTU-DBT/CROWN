SELECT
    i_brand_id, i_brand, i_manufact_id, i_manufact,
    SUM(ss_ext_sales_price)
FROM store_sales, store, customer, customer_address, date_dim, item
WHERE d_date_sk = ss_sold_date_sk
  AND ss_item_sk = i_item_sk
  AND ss_customer_sk = c_customer_sk
  AND c_current_addr_sk = ca_address_sk
  AND ss_store_sk = s_store_sk
GROUP BY i_brand_id, i_brand, i_manufact_id, i_manufact;
