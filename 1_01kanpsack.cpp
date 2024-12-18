/*  进一步考虑：如果每件物品都有体积和价值，背包又有大小限制，求解背包中存放物品总价值最大的问题解-- - 最优解或近似最优解。
    有两种方法，一种是刚刚提示中的回溯法，但此法时间复杂度较高，所以可采用动态规划法*/
#include <iostream>
#include <vector>
#include <fstream>   
#include <sstream>   
#include <algorithm> 

using namespace std;

int main()
{
    // 输入
    ifstream inputFile("1_input2.txt");
    if (!inputFile.is_open())
    {
        cerr << "error" << endl;
        return 1;
    }

    int T;               
    vector<int> volumes; 
    vector<int> values;  

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

    int n = volumes.size(); 
    if (n != values.size())
    {
        cerr << "error" << endl;
        return 1;
    }

    // dp
    vector<vector<int>> dp(n + 1, vector<int>(T + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= T; ++j)
        {
            if (volumes[i - 1] <= j)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - volumes[i - 1]] + values[i - 1]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // 输出
    cout << "最大价值为 " << dp[n][T] << endl;

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

    cout << "索引为:";
    for (int i = selectedItems.size() - 1; i >= 0; --i)
    {
        cout << selectedItems[i] << (i > 0 ? ", " : "");
    }
    cout << endl;

    return 0;
}
