#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// 定义迷宫的大小
const int MAX_M = 10;
const int MAX_N = 10;

// 四个方向的偏移量：右、下、左、上
int dx[4] = {0, 1, 0, -1}; // 右，下，左，上
int dy[4] = {1, 0, -1, 0}; // 右，下，左，上

// 判断位置是否合法，是否在迷宫内且没有障碍物
bool isValid(int x, int y, int m, int n, vector<vector<int>>& maze, vector<vector<bool>>& visited) {
    return (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0 && !visited[x][y]);
}

// 使用深度优先搜索（DFS）来查找路径
bool dfs(int x, int y, int m, int n, vector<vector<int>>& maze, vector<vector<bool>>& visited, vector<pair<int, int>>& path) {
    // 如果到达出口，返回true
    if (x == m - 1 && y == n - 1) {
        path.push_back({x, y});
        return true;
    }

    // 标记当前位置为已访问
    visited[x][y] = true;
    path.push_back({x, y});

    // 尝试四个方向（按照右、下、左、上的顺序）
    for (int i = 0; i < 4; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (isValid(newX, newY, m, n, maze, visited)) {
            if (dfs(newX, newY, m, n, maze, visited, path)) {
                return true;
            }
        }
    }

    // 如果没有找到路径，回溯，撤销当前位置
    path.pop_back();
    visited[x][y] = false;
    return false;
}

// 将迷宫图形输出到文件
void printMazeToFile(int m, int n, vector<vector<int>>& maze, vector<pair<int, int>>& path, ofstream& outputFile) {
    // 创建一个迷宫的副本，用来显示路径
    vector<vector<char>> outputMaze(m, vector<char>(n, '.')); // 默认为通路

    // 标记障碍物
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (maze[i][j] == 1) {
                outputMaze[i][j] = '#'; // 障碍用#表示
            }
        }
    }

    // 标记路径
    for (auto& p : path) {
        outputMaze[p.first][p.second] = '*'; // 路径用*表示
    }

    // 起点和终点标记
    outputMaze[0][0] = 'S'; // 起点用S表示
    outputMaze[m - 1][n - 1] = 'E'; // 终点用E表示

    // 将迷宫写入文件
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            outputFile << outputMaze[i][j] << " ";
        }
        outputFile << endl;
    }
}

int main() {
    int m, n;

    // 从文件13_input.txt读取输入
    ifstream inputFile("13_input.txt");
    if (!inputFile) {
        cerr << "无法打开输入文件！" << endl;
        return 1;
    }

    inputFile >> m >> n;
    vector<vector<int>> maze(m, vector<int>(n));

    // 读取迷宫的障碍信息
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> maze[i][j];
        }
    }

    inputFile.close();

    vector<vector<bool>> visited(m, vector<bool>(n, false)); // 记录访问情况
    vector<pair<int, int>> path; // 记录路径

    // 从入口(0, 0)开始进行深度优先搜索
    ofstream outputFile("13_output.txt");
    if (!outputFile) {
        cerr << "无法打开输出文件！" << endl;
        return 1;
    }

    if (dfs(0, 0, m, n, maze, visited, path)) {
        outputFile << "找到从入口到出口的路径: " << endl;
        // 输出迷宫图形到文件
        printMazeToFile(m, n, maze, path, outputFile);
    } else {
        outputFile << "没有找到从入口到出口的路径！" << endl;
    }

    outputFile.close();

    return 0;
}
