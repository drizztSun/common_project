"""


1747. Leetflex Banned Accounts


Table: LogInfo

+-------------+----------+
| Column Name | Type     |
+-------------+----------+
| account_id  | int      |
| ip_address  | int      |
| login       | datetime |
| logout      | datetime |
+-------------+----------+
There is no primary key for this table, and it may contain duplicates.
The table contains information about the login and logout dates of Leetflex accounts. It also contains the IP address from which the account logged in and out.
It is guaranteed that the logout time is after the login time.
 

Write an SQL query to find the account_id of the accounts that should be banned from Leetflex. An account should be banned if it was logged in at some moment from two different IP addresses.

Return the result table in any order.

The query result format is in the following example:

 

LogInfo table:
+------------+------------+---------------------+---------------------+
| account_id | ip_address | login               | logout              |
+------------+------------+---------------------+---------------------+
| 1          | 1          | 2021-02-01 09:00:00 | 2021-02-01 09:30:00 |
| 1          | 2          | 2021-02-01 08:00:00 | 2021-02-01 11:30:00 |
| 2          | 6          | 2021-02-01 20:30:00 | 2021-02-01 22:00:00 |
| 2          | 7          | 2021-02-02 20:30:00 | 2021-02-02 22:00:00 |
| 3          | 9          | 2021-02-01 16:00:00 | 2021-02-01 16:59:59 |
| 3          | 13         | 2021-02-01 17:00:00 | 2021-02-01 17:59:59 |
| 4          | 10         | 2021-02-01 16:00:00 | 2021-02-01 17:00:00 |
| 4          | 11         | 2021-02-01 17:00:00 | 2021-02-01 17:59:59 |
+------------+------------+---------------------+---------------------+

Result table:
+------------+
| account_id |
+------------+
| 1          |
| 4          |
+------------+
Account ID 1 --> The account was active from "2021-02-01 09:00:00" to "2021-02-01 09:30:00" with two different IP addresses (1 and 2). It should be banned.
Account ID 2 --> The account was active from two different addresses (6, 7) but in two different times.
Account ID 3 --> The account was active from two different addresses (9, 13) on the same day but they do not intersect at any moment.
Account ID 4 --> The account was active from "2021-02-01 17:00:00" to "2021-02-01 17:00:00" with two different IP addresses (10 and 11). It should be banned.

"""



"""

The idea is very simple

First, cross join the the LogInfo table itself to get all the possible combinations.
Then use WHERE to make sure we are having the right account id to be returned:
a. a.account_id = b.account_id : make sure it is the same person
b. (a.logout >= b.login and a.logout <= b.logout): To find out if the account is logged in at the same moment, we just have to find the logout time of a earlier access that is later or equal to the login time of the later access AND eariler or equal to the logout time of the later access.
c. a.ip_address != b.ip_address: Making sure that the two ip address from the same account_id are not the same.
"""

select distinct a.account_id
from LogInfo a, LogInfo b
where a.account_id = b.account_id 
and (a.logout >= b.login and a.logout <= b.logout)
and a.ip_address != b.ip_address


SELECT DISTINCT l1.account_id
FROM loginfo l1,
     loginfo l2 where(l1.account_id = l2.account_id
                      AND l1.ip_address <> l2.ip_address
                      AND (l1.login BETWEEN l2.login AND l2.logout
                           OR l1.logout BETWEEN l2.login AND l2.logout))