/*

# 765. Couples Holding Hands

# N couples sit in 2N seats arranged in a row and want to hold hands.
# We want to know the minimum number of swaps so that every couple is sitting side by side.
#
# A swap consists of choosing any two people, then they stand up and switch seats.

# The people and seats are represented by an integer from 0 to 2N-1, the couples are numbered in order,
# the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2N-2, 2N-1).

# The couples' initial seating is given by row[i] being the value of the person
# who is initially sitting in the i-th seat.

# Example 1:

# Input: row = [0, 2, 1, 3]
# Output: 1
# Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
# Example 2:

# Input: row = [3, 2, 0, 1]
# Output: 0
# Explanation: All couples are already seated side by side.

# Note:
# len(row) is even and in the range of [4, 60].
# row is guaranteed to be a permutation of 0...len(row)-1.


*/

#include <unordered_map>
#include <vector>

using std::vector;
using std::unordered_map;


class MinSwapsCouples {

	/*
		765.Couples-Holding-Hands
		解法1：此题可以人工找到最优的策略,所以属于贪心法.
		考虑这么一个字串03....61....42.....我们试图想把前两个数字变为01使得配成一对,那么最高效的方法就只有把3和1进行交换.于是得到01....63....42....接下来,为了充分利用刚才的这次交换,我们可以假定3已经处于了最终位置,那么我们需要把6换掉变成2,使得23配成一对.于是得到01....23....46....接下来,
        同理,为了充分利用刚才的这次交换,我们固定4的位置,需要把6换走,换来5,...以此类推,直到某次交换结束后恰好配成了一对不需要再做这样的换走/换来的swap.这其实说明这M次swap形成了一个闭环,共配成了M+1对,是最高效的方法.

		接下来,我们可以继续在这个数列里寻找下一个没配对的位置,重复上述的过程,在一个闭环中完成若干次匹配.这种算法可以成为cyclic swapping

		以上述例子的第二次swap为例,核心的代码如下:

		while (flag==0)
		{
		// 此时序列是```03....61....42....```,partner是1,curPos是1
		
		swap(row[curPos],row[Pos[partner]]);  // 交换3和1,得到```01....63....42....```
		
		holder = row[Pos[partner]]; // holder是在当前配对中已经固定好的那个数,即3
		int holder_pos = Pos[partner];  // holder所在的idx,即此时3的那个位置
		
		partner = coupleID[holder]*2==holder? holder+1:holder-1;  //根据holder,确定它的partner,即2
		curPos = (holder_pos%2==0) ? holder_pos+1:holder_pos-1;   //根据holder_pos,确定下次需要交换的两个数的其中一个位置,即此时3前面的那个位置
		
		flag = row[curPos]==partner; //判断此时holder和partner是否已经配对,否则需要继续循环
		}
        
		解法2：Union Find
		我们根据如下的规则将所有的人分组：1.同属于一对couple的聚为一组；2.被安排在相邻位置的聚为一组（指的是01，23，45这样的位置）。

		这样我们就得到了若干个union。这些union有如下性质：1.每个union之间是没有关系的，即没有任何couple被拆在不同的union里。2.在每个union内部，都可以通过若干次的swap使得内部的couple得到配对。3.每个union不可能再拆分为若干个更小的union。

		因为每个union是这样一个“最小”的社区单位，所以他们其实形成了一个闭环。如果一个union内部有k对couple，则最多只需要k-1次swap就可以让所有couple配对。（这是因为每次swap至少能保证一对couple配对，而使得k-1对couple配对后，最后一对couple自然也就配对了。）那么有没有可能用更少次数的swap使其配对呢？其实不可能。

		给一个比较粗糙的类比。Union A有k个couple，Union B有m个couple，Union C有n个couple，且k=m+n。要是的B和C理顺关系，只需要m-1+n-1=m+n-2=k-2次swap。如果理顺A也只需要k-2此的话，其意味着A可能分为B+C？但事实上A不可再分，其拓扑结构必然复杂于B+C，所以不可能也用k-2次swap就实现目标，只能用k-1次。
	*/
	int minSwapsCouples(vector<int>& row) 
    {        
        if (row.size()==0) return 0;
        
        int N = row.size();
        unordered_map<int,int>Pos;
        unordered_map<int,int>coupleID;
        
        for (int i=0; i<N; i++)
        {
            Pos[row[i]] = i;
            coupleID[i] = i/2;
        }
            
        int count = 0;
        
        for (int k=0; k<N; k+=2)
        {           
            if (coupleID[row[k]]==coupleID[row[k+1]])
                continue;

            int flag=0;       
            
            int holder = row[k];
            int partner = coupleID[holder]*2==holder? holder+1:holder-1;
            int curPos = k+1;
            
            while (flag==0)
            {                
                std::swap(row[Pos[partner]],row[curPos]);                
                count++;
                
                holder = row[Pos[partner]];
                int holder_pos = Pos[partner];
                
                curPos = (holder_pos%2==0) ? holder_pos+1:holder_pos-1;
                partner = coupleID[holder]*2==holder? holder+1:holder-1;
                                
                flag = row[curPos]==partner;
            }
            
        }
        
        return count;
    }

	vector<int>Father;
public:
    int minSwapsCouples(vector<int>& row) 
    {
        int N = row.size();
        Father.resize(N);
        
        for (int i=0; i<N; i+=2)
        {
            Father[i] = i;
            Father[i+1] = i;
        }
        
        for (int i=0; i<N; i+=2)
        {
            int a = row[i];
            int b = row[i+1];
            if (FindFather(a)!=FindFather(b))
                Union(a,b);
        }
        
        unordered_map<int,int>count;
        for (int i=0; i<N; i++)
            count[FindFather(i)] += 1;
        
        int ret = 0;
        for (auto x: count)
           ret += x.second/2-1;
        
        return ret;
    }
    
    int FindFather(int x)
    {
        if (Father[x]!=x)
            Father[x] = FindFather(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y)
            Father[y] = x;
        else
            Father[x] = y;
    }

public:

	int doit(vector<int>&& row) {

		unordered_map<int, int> pos;
		for (auto i = 0; i < row.size(); i++)
			pos[row[i]] = i;

		int step = 0;
		for (auto i = 0; i < row.size(); i += 2) {

			int one = row[i], two = -1;

			if (one % 2 == 1) {
				two = one - 1;
			}
			else {
				two = one + 1;
			}

			if (two == row[i + 1])
				continue;

			int old = row[i + 1];
			int twoPos = pos[two];

			swap(row[i+1], row[twoPos]);
			pos[two] = i + 1;
			pos[old] = twoPos;

			step++;
		}

		return step;
	}
};