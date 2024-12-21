#include <iostream>
#include <fstream>
#include <list>

using namespace std;

// 输入
void read_input(const string &filename, int &n, int &m, list<pair<int, int>> &people)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "无法打开输入文件：" << filename << endl;
        exit(1);
    }

    infile >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        int password;
        infile >> password;
        people.emplace_back(i, password);
    }
    infile.close();
}

// 输出
void write_output(const string &filename, const list<int> &result)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cerr << "无法打开输出文件：" << filename << endl;
        exit(1);
    }

    for (auto id : result)
    {
        outfile << id << " ";
    }
    outfile << endl;
    outfile.close();
}

// 模拟出列
void solve(int m, list<pair<int, int>> &people, list<int> &result)
{
    auto it = people.begin();

    while (!people.empty())
    {
        // 按m报数
        int count = 1;
        while (count < m)
        {
            ++it;
            if (it == people.end())
            {
                it = people.begin();
            }
            ++count;
        }

        //报数为m的人出列
        result.push_back(it->first);
        m = it->second; // 更新m值
        it = people.erase(it);

        if (it == people.end())
        {
            it = people.begin();
        }
    }
}

int main()
{

    int n, m;                  
    list<pair<int, int>> people; 
    list<int> result;           
    // 输入
    read_input("5_input.txt", n, m, people);
    // 模拟出列
    solve(m, people, result);
    // 输出
    write_output("5_output.txt", result);

    return 0;
}
