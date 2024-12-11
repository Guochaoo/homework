/* 1.问题描述
       假设有一个能装入总体积为T的背包和n件体积分别为w1,w2,…wn的物品，能否从n件物品中挑选若干件恰好装满背包，即使w1+w2+…+wm=T，要求找出所有满足上述条件的解。 
      例如：当T=10，各件物品的体积{1,8,4,3,5,2}时，可找到下列4组解：
    	(1,4,3,2)
     	(1,4,5)
     	(8,2)
     	(3,5,2)。
 2.实现提示
       可利用回溯法的设计思想来解决背包问题。首先，将物品排成一列，然后，顺序选取物品装入背包，若已选取第i件物品后未满，则继续选取第i+1件，若该件物品“太大”不能装入，则弃之，继续选取下一件，直至背包装满为止。
       如果在剩余的物品中找不到合适的物品以填满背包，则说明“刚刚”装入的物品“不合适”，应将它取出“弃之一边”，继续再从“它之后”的物品中选取，如此重复，直到求得满足条件的解，或者无解。
       由于回溯求解的规则是“后进先出”，自然要用到“栈” */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<int> current;
vector<vector<int>> solutions;

void find_solution(vector<int> &items, int target, vector<int> &current, int index);
int main()
{
    ifstream inputFile("1_test1.txt");
    if (!inputFile.is_open())
    {
        cerr << "error" << endl;
        return 1;
    }

    int T;             
    vector<int> items; 

    string line;
    if (getline(inputFile, line))
    {
        stringstream ss(line);
        ss >> T;
    }

    if (getline(inputFile, line))
    {
        stringstream ss(line);
        int item;
        while (ss >> item)
        {
            items.push_back(item);
        }
    }

    inputFile.close();

    find_solution(items, T, current, 0);
    for (const auto &solution : solutions)
    {
        for (size_t i = 0; i < solution.size(); ++i)
        {
            cout << solution[i];
            if (i < solution.size() - 1)
            {
                cout << ",";
            }
        }
        cout << endl;
    }

    return 0;
}
void find_solution(vector<int> &items, int target, vector<int> &current, int index)
{
    if (target == 0)
    {
        solutions.push_back(current);
        return;
    }
    if (index >= items.size() || target < 0)
    {
        return;
    }
    // no
    find_solution(items, target, current, index + 1);
    // yes
    current.push_back(items[index]);
    find_solution(items, target - items[index], current, index + 1);
    current.pop_back();
}