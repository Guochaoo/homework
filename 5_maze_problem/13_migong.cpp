#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// 四个方向的偏移量：右、下、左、上
int dx[4] = {0, 1, 0, -1}; // 右，下，左，上
int dy[4] = {1, 0, -1, 0}; // 右，下，左，上

// 判断位置是否合法，是否在迷宫内且没有障碍物
bool is_safe(int x, int y, int m, int n, vector<vector<int>>& maze, vector<vector<bool>>& visited) {
    return (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0 && !visited[x][y]);
}

// 深搜
bool dfs(int x, int y, int m, int n, vector<vector<int>>& maze, vector<vector<bool>>& visited, vector<pair<int, int>>& path) {
    // 找到出口
    if (x == m - 1 && y == n - 1) {
        path.push_back({x, y});
        return true;
    }

    // 标记当前位置状态
    visited[x][y] = true;
    path.push_back({x, y});

    // 按右、下、左、上的顺序尝试移动
    for (int i = 0; i < 4; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (is_safe(newX, newY, m, n, maze, visited)) {
            if (dfs(newX, newY, m, n, maze, visited, path)) {
                return true;
            }
        }
    }

    // 没有找到路径则回溯，撤销当前位置
    path.pop_back();
    visited[x][y] = false;
    return false;
}

// 输出
void write_output(int m, int n, vector<vector<int>>& maze, vector<pair<int, int>>& path, ofstream& outputFile) {
    vector<vector<char>> output_maze(m, vector<char>(n, '.')); 

    // 标记障碍物
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (maze[i][j] == 1) {
                output_maze[i][j] = '#'; // 障碍用#表示
            }
        }
    }

    // 标记路径
    for (auto& p : path) {
        output_maze[p.first][p.second] = '*'; // 路径用*表示
    }

    output_maze[0][0] = 'S'; // 起点用S表示
    output_maze[m - 1][n - 1] = 'E'; // 终点用E表示

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            outputFile << output_maze[i][j] << " ";
        }
        outputFile << endl;
    }
}

int main() {
    int m, n;
    vector<vector<int>> maze(m, vector<int>(n));
    vector<vector<bool>> visited(m, vector<bool>(n, false)); // 记录访问情况
    vector<pair<int, int>> path;                             // 记录路径

    //输入
    ifstream inputFile("13_input.txt");
    if (!inputFile) {
        cerr << "无法打开输入文件！" << endl;
        return 1;
    }

    inputFile >> m >> n;

    //读取障碍位置
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> maze[i][j];
        }
    }

    inputFile.close();

    //输出
    ofstream outputFile("13_output.txt");
    if (!outputFile) {
        cerr << "无法打开输出文件！" << endl;
        return 0;
    }
    //深搜
    if (dfs(0, 0, m, n, maze, visited, path)) {
        outputFile << "找到从入口到出口的路径: " << endl;
        write_output(m, n, maze, path, outputFile);
    } else {
        outputFile << "没有找到从入口到出口的路径！" << endl;
    }

    outputFile.close();

    return 0;
}
