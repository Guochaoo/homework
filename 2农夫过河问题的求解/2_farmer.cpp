/* 1.问题描述
    一个农夫带着一只狼、一只羊和一棵白菜，身处河的南岸。他要把这些东西全部运到北岸。他面前只有一条小船，船只能容下他和一件物品，另外只有农夫才能撑船。如果农夫在场，则狼不能吃羊，羊不能吃白菜，否则狼会吃羊，羊会吃白菜，所以农夫不能留下羊和白菜自己离开，也不能留下狼和羊自己离开，而狼不吃白菜。请求出农夫将所有的东西运过河的方案。
2.实现提示
     求解这个问题的简单方法是一步一步进行试探，每一步搜索所有可能的选择，对前一步合适的选择后再考虑下一步的各种方案。要模拟农夫过河问题，首先需要对问题中的每个角色的位置进行描述。可用4位二进制数顺序分别表示农夫、狼、白菜和羊的位置。用0表在南岸，1表示在北岸。例如，整数5 (0101)表示农夫和白菜在南岸，而狼和羊在北岸。

     现在问题变成：从初始的状态二进制0000(全部在河的南岸)出发，寻找一种全部由安全状态构成的状态序列，它以二进制1111(全部到达河的北岸)为最终目标。总状态共16种(0000到1111)，(或者看成16个顶点的有向图)可采用广度优先或深度优先的搜索策略---得到从0000到1111的安全路径。

     以广度优先为例：整数队列---逐层存放下一步可能的安全状态；Visited[16]数组标记该状态是否已访问过，若访问过，则记录前驱状态值---安全路径。
     最终的过河方案应用汉字显示出每一步的两岸状态。
 */
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool isSafe(int state)
{
    int farmer = (state >> 3) & 1;
    int wolf = (state >> 2) & 1;
    int sheep = (state >> 1) & 1;
    int cabbage = state & 1;

    // 如果农夫不在场，狼和羊不能在一起
    if (farmer != wolf && wolf == sheep)
        return false;

    // 如果农夫不在场，羊和白菜不能在一起
    if (farmer != sheep && sheep == cabbage)
        return false;

    return true;
}

// 打印当前状态
string stateToString(int state)
{
    string south = "南岸: ", north = "北岸: ";
    if (((state >> 3) & 1) == 0)
        south += "农夫 ";
    else
        north += "农夫 ";
    if (((state >> 2) & 1) == 0)
        south += "狼 ";
    else
        north += "狼 ";
    if (((state >> 1) & 1) == 0)
        south += "羊 ";
    else
        north += "羊 ";
    if ((state & 1) == 0)
        south += "白菜 ";
    else
        north += "白菜 ";

    return south + "\t" + north;
}

// 广搜
void solve()
{
    queue<int> q;
    unordered_map<int, int> visited; // 用于记录前驱状态

    int startState = 0b0000; // 初始状态
    int endState = 0b1111;   // 目标状态

    q.push(startState);
    visited[startState] = -1; // 起始状态的前驱标记为-1

    // 广度优先搜索
    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        // 如果到达目标状态，输出路径
        if (current == endState)
        {
            vector<int> path;
            while (current != -1)
            {
                path.push_back(current);
                current = visited[current];
            }

            reverse(path.begin(), path.end());

            for (int state : path)
            {
                cout << stateToString(state) << endl;
            }
            return;
        }

        // 尝试所有可能的移动
        for (int i = 0; i < 4; ++i)
        {
            int next = current ^ (1 << 3); // 农夫移动

            if (i < 3 && ((current >> i) & 1) == ((current >> 3) & 1))
            {
                next ^= (1 << i); // 带上狼、羊或白菜
            }

            if (isSafe(next) && visited.find(next) == visited.end())
            {
                q.push(next);
                visited[next] = current; // 记录前驱状态
            }
        }
    }

    cout << "没有找到解决方案。" << endl;
}

int main()
{
    cout << "解决方案如下\n"<< endl;
    solve();
    return 0;
}
