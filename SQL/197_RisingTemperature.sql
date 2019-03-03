

select
	weather.Id as 'Id'
from
	weather
	
	join weather b on DATEDIFF(weather.RecordDate, b.RecordDate) = 1
		and weather.Temperature > b.Temperature




Given a Weather table, write a SQL query to find all dates' Ids with higher temperature compared to its previous (yesterday's) dates.

+---------+------------------+------------------+
| Id(INT) | RecordDate(DATE) | Temperature(INT) |
+---------+------------------+------------------+
|       1 |       2015-01-01 |               10 |
|       2 |       2015-01-02 |               25 |
|       3 |       2015-01-03 |               20 |
|       4 |       2015-01-04 |               30 |
+---------+------------------+------------------+
For example, return the following Ids for the above Weather table:

+----+
| Id |
+----+
|  2 |
|  4 |
+----+


Approach: Using JOIN and DATEDIFF() clause [Accepted]
Algorithm

MySQL uses DATEDIFF to compare two date type values.

So, we can get the result by joining this table weather with itself and use this DATEDIFF() function.

MySQL

SELECT
    weather.id AS 'Id'
FROM
    weather
        JOIN
    weather w ON DATEDIFF(weather.date, w.date) = 1
        AND weather.Temperature > w.Temperature
;