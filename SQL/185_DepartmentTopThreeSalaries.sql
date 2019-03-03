select 
    d.Name as Department,
    e1.Name as Employee,
    e1.Salary as Salary
    
from 

    Employee e1
        join 
    Department d on d.Id = e1.DepartmentId
    
where 3 > ( select
            COUNT(DISTINCT e2.Salary)
         from
            Employee e2
         where
            e2.Salary > e1.Salary and e1.DepartmentId = e2.DepartmentId
    )

	
	The Employee table holds all employees. Every employee has an Id, and there is also a column for the department Id.

	
+----+-------+--------+--------------+
| Id | Name  | Salary | DepartmentId |
+----+-------+--------+--------------+
| 1  | Joe   | 70000  | 1            |
| 2  | Henry | 80000  | 2            |
| 3  | Sam   | 60000  | 2            |
| 4  | Max   | 90000  | 1            |
| 5  | Janet | 69000  | 1            |
| 6  | Randy | 85000  | 1            |
+----+-------+--------+--------------+
The Department table holds all departments of the company.

+----+----------+
| Id | Name     |
+----+----------+
| 1  | IT       |
| 2  | Sales    |
+----+----------+
Write a SQL query to find employees who earn the top three salaries in each of the department. For the above tables, your SQL query should return the following rows.

+------------+----------+--------+
| Department | Employee | Salary |
+------------+----------+--------+
| IT         | Max      | 90000  |
| IT         | Randy    | 85000  |
| IT         | Joe      | 70000  |
| Sales      | Henry    | 80000  |
| Sales      | Sam      | 60000  |
+------------+----------+--------+




Approach: Using JOIN and sub-query [Accepted]
Algorithm

A top 3 salary in this company means there is no more than 3 salary bigger than itself in the company.

select e1.Name as 'Employee', e1.Salary
from Employee e1
where 3 >
(
    select count(distinct e2.Salary)
    from Employee e2
    where e2.Salary > e1.Salary
)
;
In this code, we count the salary number of which is bigger than e1.Salary. So the output is as below for the sample data.

| Employee | Salary |
|----------|--------|
| Henry    | 80000  |
| Max      | 90000  |
| Randy    | 85000  |
Then, we need to join the Employee table with Department in order to retrieve the department information.

MySQL

SELECT
    d.Name AS 'Department', e1.Name AS 'Employee', e1.Salary
FROM
    Employee e1
        JOIN
    Department d ON e1.DepartmentId = d.Id
WHERE
    3 > (SELECT
            COUNT(DISTINCT e2.Salary)
        FROM
            Employee e2
        WHERE
            e2.Salary > e1.Salary
                AND e1.DepartmentId = e2.DepartmentId
        )
;
| Department | Employee | Salary |
|------------|----------|--------|
| IT         | Joe      | 70000  |
| Sales      | Henry    | 80000  |
| Sales      | Sam      | 60000  |
| IT         | Max      | 90000  |
| IT         | Randy    | 85000  |