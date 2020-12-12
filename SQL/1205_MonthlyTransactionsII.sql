"""
1205. Monthly Transactions II


Table: Transactions

+----------------+---------+
| Column Name    | Type    |
+----------------+---------+
| id             | int     |
| country        | varchar |
| state          | enum    |
| amount         | int     |
| trans_date     | date    |
+----------------+---------+
id is the primary key of this table.
The table has information about incoming transactions.
The state column is an enum of type ["approved", "declined"].
Table: Chargebacks

+----------------+---------+
| Column Name    | Type    |
+----------------+---------+
| trans_id       | int     |
| charge_date    | date    |
+----------------+---------+
Chargebacks contains basic information regarding incoming chargebacks from some transactions placed in Transactions table.
trans_id is a foreign key to the id column of Transactions table.
Each chargeback corresponds to a transaction made previously even if they were not approved.


Write an SQL query to find for each month and country, the number of approved transactions and their total amount, the number of chargebacks and their total amount.

Note: In your query, given the month and country, ignore rows with all zeros.

The query result format is in the following example:

Transactions table:
+------+---------+----------+--------+------------+
| id   | country | state    | amount | trans_date |
+------+---------+----------+--------+------------+
| 101  | US      | approved | 1000   | 2019-05-18 |
| 102  | US      | declined | 2000   | 2019-05-19 |
| 103  | US      | approved | 3000   | 2019-06-10 |
| 104  | US      | approved | 4000   | 2019-06-13 |
| 105  | US      | approved | 5000   | 2019-06-15 |
+------+---------+----------+--------+------------+

Chargebacks table:
+------------+------------+
| trans_id   | trans_date |
+------------+------------+
| 102        | 2019-05-29 |
| 101        | 2019-06-30 |
| 105        | 2019-09-18 |
+------------+------------+

Result table:
+----------+---------+----------------+-----------------+-------------------+--------------------+
| month    | country | approved_count | approved_amount | chargeback_count  | chargeback_amount  |
+----------+---------+----------------+-----------------+-------------------+--------------------+
| 2019-05  | US      | 1              | 1000            | 1                 | 2000               |
| 2019-06  | US      | 3              | 12000           | 1                 | 1000               |
| 2019-09  | US      | 0              | 0               | 1                 | 5000               |
+----------+---------+----------------+-----------------+-------------------+--------------------+
"""

/* Write your T-SQL query statement below */

-- Calculate chargeback count and amount and assign 0 to approved values
with chargeback_CTE as (
Select t.country, left(c.trans_date,7) as month, 0 as approved_count, 0 as approved_amount,  ISNULL(count(c.trans_id),0) as chargeback_count ,ISNULL(sum(t.amount),0) as chargeback_amount
    from transactions t
    inner join Chargebacks c
    on t.id = c.trans_id
    group by t.country, left(c.trans_date,7)
)

-- Calculate approved count and amount and union with CTE and collapse all to count the final values
Select month, country, ISNULL(SUM(approved_count),0) approved_count,
ISNULL(SUM(approved_amount),0) approved_amount,
ISNULL(SUM(chargeback_count),0) chargeback_count,
ISNULL(SUM(chargeback_amount),0) chargeback_amount
from (
            Select country, left(trans_date,7) as month, ISNULL(count(id),0) as approved_count, ISNULL(sum(amount),0) as  approved_amount, 0 as chargeback_count, 0 as chargeback_amount
            from Transactions
            where state = 'approved'
            group by country, left(trans_date,7)
                UNION ALL
            Select * from chargeback_CTE) t
group by month, country