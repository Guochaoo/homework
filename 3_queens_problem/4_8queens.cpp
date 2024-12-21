/* 1.问题描述
       设在初始状态下在国际象棋的棋盘上没有任何棋子（这里的棋子指皇后棋子）。然后顺序在第1行，第2行……第8行上布放棋子。在每一行中共有8个可选择的位置，但在任一时刻棋盘的合法布局都必须满足3个限制条件（1）任意两个棋子不得放在同一行（2）任意两个棋子不得放在同一列上（3）任意棋子不得放在同一正斜线和反斜线上。
2.基本要求
        编写求解并输出此问题的一个合法布局的程序。
3、实现提示：
       在第i行布放棋子时，从第1列到第8列逐列考察。当在第i行第j列布放棋子时，需要考察布放棋子后在行方向、列方向、正斜线和反斜线方向上的布局状态是否合法，若该棋子布放合法，再递归求解在第i+1行布放棋子；若该棋子布放不合法，移去这个棋子，恢复布放该棋子前的状态，然后再试探在第i行第j+1列布放棋子。
 */
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int N = 8;

// 列
vector<bool> col(N, false);
// 正斜线
vector<bool> diag1(2 * N - 1, false);
// 反斜线
vector<bool> diag2(2 * N - 1, false);
// 存储每行皇后放置的列位置
vector<int> result(N, -1);

// 检查是否可以放置
bool can_place(int i, int j)
{
    return !col[j] && !diag1[i + j] && !diag2[i - j + N - 1];
}

// 放置皇后
void place_queen(int i, int j)
{
    col[j] = true;
    diag1[i + j] = true;
    diag2[i - j + N - 1] = true;
    result[i] = j;
}

// 移除皇后
void remove_queen(int i, int j)
{
    col[j] = false;
    diag1[i + j] = false;
    diag2[i - j + N - 1] = false;
    result[i] = -1;
}

// 将结果输出为图形格式
void write_output(vector<int> &result)
{
    ofstream outFile("4_output.txt");
    if (!outFile.is_open())
    {
        cerr << "无法打开输出文件" << endl;
        return;
    }

    outFile << "一个合法布局：" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (result[i] == j)
            {
                outFile << "Q "; // 皇后位置
            }
            else
            {
                outFile << ". "; // 空位
            }
        }
        outFile << endl;
    }
    outFile << endl;
}

// 求解
bool solve(int row)
{
    if (row == N)
    {
        // 如果所有行都放置了皇后，输出结果
        write_output(result);
        return true;
    }

    for (int colIdx = 0; colIdx < N; colIdx++)
    {
        if (can_place(row, colIdx))
        {
            place_queen(row, colIdx);
            if (solve(row + 1))
            {
                return true; // 找到一个合法解就返回
            }
            remove_queen(row, colIdx); // 回溯
        }
    }

    return false; // 如果这一行的所有列都无法放置皇后，返回false
}

int main()
{
    if (!solve(0))
    {
        cout << "no solution" << endl;
    }
    return 0;
}