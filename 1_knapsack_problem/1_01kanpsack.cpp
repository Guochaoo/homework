/*  进一步考虑：如果每件物品都有体积和价值，背包又有大小限制，求解背包中存放物品总价值最大的问题解-- - 最优解或近似最优解。
    有两种方法，一种是刚刚提示中的回溯法，但此法时间复杂度较高，所以可采用动态规划法*/
#include <iostream>
#include <vector>
#include <fstream>   
#include <sstream>   
#include <algorithm> 

using namespace std;
vector<vector<int>> solve(int n, int T, vector<int> volumes, vector<int> values)
{
    vector<vector<int>> dp(n + 1, vector<int>(T + 1, 0));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= T; ++j)
        {
            if (j < volumes[i - 1])
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - volumes[i - 1]] + values[i - 1]);//状态转移方程
            }
        }
    }
    return dp;
}

void read_input(int &T, vector<int> &volumes, vector<int> &values)
{
    ifstream inputFile("1_input2.txt");
    if (!inputFile.is_open())
    {
        cerr << "打开输入文件失败" << endl;
        return;
    }

    string line;
    if (getline(inputFile, line))
    {
        stringstream ss(line);
        ss >> T;
    }

    if (getline(inputFile, line))
    {
        stringstream ss(line);
        int volume;
        while (ss >> volume)
        {
            volumes.push_back(volume);
        }
    }

    if (getline(inputFile, line))
    {
        stringstream ss(line);
        int value;
        while (ss >> value)
        {
            values.push_back(value);
        }
    }

    inputFile.close(); 
}
void write_output(int &n, int &T, vector<int> &volumes, vector<vector<int>> &dp)
{
    ofstream outputFile("1_output2.txt");
    if (!outputFile.is_open())
    {
        cerr << "打开输出文件失败" << endl;
        return;
    }

    outputFile << "最大价值为 " << dp[n][T] << endl;
    vector<int> selectedItems;
    int j = T;
    for (int i = n; i > 0; --i)
    {
        if (dp[i][j] != dp[i - 1][j])
        {
            selectedItems.push_back(i - 1);
            j -= volumes[i - 1];
        }
    }
    outputFile << "索引为:";
    for (int i = selectedItems.size() - 1; i >= 0; --i)
    {
        outputFile << selectedItems[i] << (i > 0 ? ", " : "");
    }
    outputFile << endl;

    outputFile.close(); 
}


int main()
{
    int T;               
    vector<int> volumes; 
    vector<int> values;
    // 输入
    read_input(T, volumes, values);
    int n = volumes.size();

    // dp
    vector<vector<int>> dp(n + 1, vector<int>(T + 1, 0));
    dp=solve(n, T, volumes, values);

    // 输出
    write_output(n, T, volumes, dp);

    return 0;
}
