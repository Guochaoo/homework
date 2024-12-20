#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

// 二叉排序树节点定义
struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// 插入节点到二叉排序树
TreeNode* insert(TreeNode* root, int value) {
    if (!root) return new TreeNode(value);
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    return root;
}

// 中序遍历二叉排序树
void inOrderTraversal(TreeNode* root, vector<int>& result) {
    if (root) {
        inOrderTraversal(root->left, result);
        result.push_back(root->value);
        inOrderTraversal(root->right, result);
    }
}

// 查找并删除指定节点
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->value)
        root->left = deleteNode(root->left, key);
    else if (key > root->value)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode* successor = root->right;
        while (successor->left) successor = successor->left;
        root->value = successor->value;
        root->right = deleteNode(root->right, successor->value);
    }
    return root;
}

// 计算平均查找长度（递归遍历树并累加深度）
void calculateASL(TreeNode* root, int depth, int& totalDepth, int& nodeCount) {
    if (root) {
        totalDepth += depth;
        nodeCount++;
        calculateASL(root->left, depth + 1, totalDepth, nodeCount);
        calculateASL(root->right, depth + 1, totalDepth, nodeCount);
    }
}

int main() {
    ifstream inputFile("7_input.txt");
    ofstream outputFile("7_output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "文件打开失败！" << endl;
        return 1;
    }

    string line;
    getline(inputFile, line);
    istringstream iss(line);
    vector<int> numbers;
    int num;

    // 读取输入文件中的数列
    while (iss >> num) {
        numbers.push_back(num);
    }

    // 构建二叉排序树
    TreeNode* root = nullptr;
    for (int n : numbers) {
        root = insert(root, n);
    }

    // 中序遍历并输出结果
    vector<int> inOrderResult;
    inOrderTraversal(root, inOrderResult);
    outputFile << "中序遍历结果: ";
    for (int n : inOrderResult) {
        outputFile << n << " ";
    }
    outputFile << endl;

    // 计算平均查找长度
    int totalDepth = 0, nodeCount = 0;
    calculateASL(root, 1, totalDepth, nodeCount);
    double averageSearchLength = static_cast<double>(totalDepth) / nodeCount;
    outputFile << "平均查找长度: " << fixed << setprecision(2) << averageSearchLength << endl;

    // 查找并删除指定节点
    int x;
    cout << "请输入要删除的元素x: ";
    cin >> x;

    TreeNode* tempRoot = root;
    bool found = false;
    while (tempRoot) {
        if (x == tempRoot->value) {
            found = true;
            break;
        } else if (x < tempRoot->value) {
            tempRoot = tempRoot->left;
        } else {
            tempRoot = tempRoot->right;
        }
    }

    if (found) {
        root = deleteNode(root, x);
        inOrderResult.clear();
        inOrderTraversal(root, inOrderResult);
        outputFile << "删除节点" << x << "后中序遍历结果: ";
        for (int n : inOrderResult) {
            outputFile << n << " ";
        }
        outputFile << endl;
    } else {
        outputFile << "无" << x << endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}
