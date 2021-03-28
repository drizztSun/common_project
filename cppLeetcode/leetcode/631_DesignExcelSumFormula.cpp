/*
631. Design Excel Sum Formula

Your task is to design the basic function of Excel and implement the function of sum formula. Specifically, you need to implement the following functions:

Excel(int H, char W): This is the constructor. The inputs represents the height and width of the Excel form. H is a positive integer, range from 1 to 26. 
It represents the height. W is a character range from 'A' to 'Z'. It represents that the width is the number of characters from 'A' to W. 
The Excel form content is represented by a height * width 2D integer array C, it should be initialized to zero. You should assume that the first row of C starts from 1, and the first column of C starts from 'A'.


. void Set(int row, char column, int val): Change the value at C(row, column) to be val.

. int Get(int row, char column): Return the value at C(row, column).

. int Sum(int row, char column, List of Strings : numbers): This function calculate and set the value at C(row, column), where the value should be the sum of cells represented by numbers. 
This function return the sum result at C(row, column). This sum formula should exist until this cell is overlapped by another value or another sum formula.
numbers is a list of strings that each string represent a cell or a range of cells. If the string represent a single cell, then it has the following format : ColRow. For example, "F7" represents the cell at (7, F).

If the string represent a range of cells, then it has the following format : ColRow1:ColRow2. The range will always be a rectangle, and ColRow1 represent the position of the top-left cell, and ColRow2 represents the position of the bottom-right cell.


Example 1:
Excel(3,"C"); 
// construct a 3*3 2D array with all zero.
//   A B C
// 1 0 0 0
// 2 0 0 0
// 3 0 0 0

Set(1, "A", 2);
// set C(1,"A") to be 2.
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 0

Sum(3, "C", ["A1", "A1:B2"]);
// set C(3,"C") to be the sum of value at C(1,"A") and the values sum of the rectangle range whose top-left cell is C(1,"A") and bottom-right cell is C(2,"B"). Return 4. 
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 4

Set(2, "B", 2);
// set C(2,"B") to be 2. Note C(3, "C") should also be changed.
//   A B C
// 1 2 0 0
// 2 0 2 0
// 3 0 0 6
Note:
You could assume that there won't be any circular sum reference. For example, A1 = sum(B1) and B1 = sum(A1).
The test cases are using double-quotes to represent a character.
Please remember to RESET your class variables declared in class Excel, as static/class variables are persisted across multiple test cases. Please see here for more details.


*/

#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;

/*
    631.Design-Excel-Sum-Formula
    本题需要注意的是操作的完整性。

    Set：如果该单元格已经有公式，则需要先把公式从Map里清除，再对该单元格赋值。

    Get：不是简单地从table里读数据。如果该单元格已经有公式，则该单元格依赖于其他单元格且可能未被更新。所以需要先执行一遍公式，即sum(r,c,Map[to_string(r)+c])更新该单元格的内容，再返回。

    Sum：在根据公式计算时，对于所需要的单元格数值，不能简单地从table里读取，而是要通过get操作来实现，因为那个单元格可能存在公式且未更新。
*/

class Excel {
    vector<vector<int>>Table;
    unordered_map<string,vector<string>>Map;
    
public:
    Excel(int H, char W) 
    {
        Table = vector<vector<int>>(H+1,vector<int>(W-'A'+1,0));
    }
    
    void set(int r, char c, int v) 
    {
        if (Map.find(std::to_string(r)+c)!=Map.end())
            Map.erase(std::to_string(r)+c);
        Table[r][c-'A']=v;
    }
    
    int get(int r, char c) 
    {
        if (Map.find(std::to_string(r)+c)==Map.end()) return Table[r][c-'A'];

        Table[r][c-'A'] = sum(r,c,Map[std::to_string(r)+c]);
        return Table[r][c-'A'];
    }
    
    int sum(int r, char c, vector<string> strs) 
    {
        Map[std::to_string(r)+c]=strs;
        int sum=0;
        for (int i=0; i<strs.size(); i++)
        {
            int row1,row2;
            char col1,col2;
            bool flag = read(strs[i],row1,row2,col1,col2);
                        
            if (flag==0)
                sum+=get(row1,col1);
            else
            {   for (int j=row1; j<=row2; j++)
                 for (char k=col1; k<=col2; k++)
                 {
                     sum+=get(j,k);                     
                 }
            }            
        }
        Table[r][c-'A']=sum;
        return sum;
    }
    
    bool read(string str, int& row1, int& row2, char& col1, char& col2)
    {
        bool flag=false;
        int i=0;
        
        while (i<str.size() && str[i]!=':') i++;
        flag = (i!=str.size());
        
        if (flag==0)
        {
            col1=str[0];
            row1=stoi(str.substr(1));
        }
        else
        {
            string str1=str.substr(0,i);
            string str2=str.substr(i+1);
            col1=str1[0];
            row1=stoi(str1.substr(1));
            col2=str2[0];
            row2=stoi(str2.substr(1));
        }
        return flag;        
    }
};
