/*
1418. Display Table of Food Orders in a Restaurant


Given the array orders, which represents the orders that customers have done in a restaurant. More specifically orders[i]=[customerNamei,tableNumberi,foodItemi] where customerNamei is the name of the customer, tableNumberi is the table customer sit at, and foodItemi is the item customer orders.

Return the restaurant's “display table”. The “display table” is a table whose row entries denote how many of each food item each table ordered. The first column is the table number and the remaining columns correspond to each food item in alphabetical order. The first row should be a header whose first column is “Table”, followed by the names of the food items. Note that the customer names are not part of the table. Additionally, the rows should be sorted in numerically increasing order.

 

Example 1:

Input: orders = [["David","3","Ceviche"],["Corina","10","Beef Burrito"],["David","3","Fried Chicken"],["Carla","5","Water"],["Carla","5","Ceviche"],["Rous","3","Ceviche"]]
Output: [["Table","Beef Burrito","Ceviche","Fried Chicken","Water"],["3","0","2","1","0"],["5","0","1","0","1"],["10","1","0","0","0"]] 
Explanation:
The displaying table looks like:
Table,Beef Burrito,Ceviche,Fried Chicken,Water
3    ,0           ,2      ,1            ,0
5    ,0           ,1      ,0            ,1
10   ,1           ,0      ,0            ,0
For the table 3: David orders "Ceviche" and "Fried Chicken", and Rous orders "Ceviche".
For the table 5: Carla orders "Water" and "Ceviche".
For the table 10: Corina orders "Beef Burrito". 
Example 2:

Input: orders = [["James","12","Fried Chicken"],["Ratesh","12","Fried Chicken"],["Amadeus","12","Fried Chicken"],["Adam","1","Canadian Waffles"],["Brianna","1","Canadian Waffles"]]
Output: [["Table","Canadian Waffles","Fried Chicken"],["1","2","0"],["12","0","3"]] 
Explanation: 
For the table 1: Adam and Brianna order "Canadian Waffles".
For the table 12: James, Ratesh and Amadeus order "Fried Chicken".
Example 3:

Input: orders = [["Laura","2","Bean Burrito"],["Jhon","2","Beef Burrito"],["Melissa","2","Soda"]]
Output: [["Table","Bean Burrito","Beef Burrito","Soda"],["2","1","1","1"]]
 

Constraints:

1 <= orders.length <= 5 * 10^4
orders[i].length == 3
1 <= customerNamei.length, foodItemi.length <= 20
customerNamei and foodItemi consist of lowercase and uppercase English letters and the space character.
tableNumberi is a valid integer between 1 and 500.

*/
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <map>

using std::map;
using std::set;
using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;




class DisplayTable {

    /*
        1418.Display-Table-of-Food-Orders-in-a-Restaurant
        本题有很多数据结构的设计方法，但是彼此之间的时间复杂度差别很大。

        比较快的方法是：设计map<int, unordered_map<string, int>>table2Order，用来记录每个桌号、每道food被点单的次数。其中桌号已经满足了升序排列。这其实已经和最终的表格样式很接近了。
        我们还需要知道每道food的点单次数应该填在哪个列。故我们把所有food name经过排序后，就可以得到每道food所对应的Column编号的映射。
    */
    vector<vector<string>> displayTable(vector<vector<string>>& orders) 
    {
        map<int, unordered_map<string, int>>table2Order;
        set<string>foodNames;
        for (auto order:orders)
        {
            table2Order[stoi(order[1])][order[2]]++;
            foodNames.insert(order[2]);
        }
        
        int i = 1;
        unordered_map<string,int>food2index;
        for (auto food: foodNames)        
        {
            food2index[food] = i;
            i++;
        }
        
        vector<vector<string>>rets;

        vector<string>header({"Table"});
        for (auto x:foodNames) header.push_back(x);        
        rets.push_back(header);
        
        for (auto x:table2Order)
        {            
            int id = x.first;
            auto order = x.second;

            vector<string>row(foodNames.size()+1, "0");
            row[0] = to_string(id);
            
            for (auto y: order)
            {
                int col = food2index[y.first];
                int num = y.second;
                row[col] = to_string(num);
            }            
            rets.push_back(row);            
        }
        
        return rets;
    }

public:
    
    vector<vector<string>> doit_search(vector<vector<string>>& orders) {

        unordered_set<string> foods;
        unordered_map<int, unordered_map<string, int>> table2orders;
        
        for (const auto& c : orders) {
            
            int tableid = stoi(c[1]);
            string food = c[2];
            
            if (foods.count(food) == 0)
                foods.insert(food);
            
            table2orders[tableid][food]++;
        }
        
        vector<string> foodsSorted(begin(foods), end(foods));
        std::sort(begin(foodsSorted), end(foodsSorted));
        
        vector<vector<string>> ans;
        ans.push_back({begin(foodsSorted), end(foodsSorted)});
        ans.back().insert(begin(ans.back()), "Table");    
        
        vector<int> ids;
        for (auto it: table2orders) 
            ids.push_back(it.first);
        std::sort(begin(ids), end(ids));
        
        for (auto id: ids) {
            auto& tables = table2orders[id];
            vector<string> tmp{std::to_string(id)};
            
            for (auto& food : foodsSorted) {
                tmp.push_back(tables.count(food) ? std::to_string(tables[food]) : "0");
            }
            ans.push_back(tmp);
        }

        return ans;
    }
};
