#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

// AVL树节点结构
struct TreeNode {
    int value;
    TreeNode *left, *right;
    int height;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};

// 获取节点的高度
int height(TreeNode* node) {
    return node ? node->height : 0;
}

// 获取节点的平衡因子
int getBalanceFactor(TreeNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// 更新节点的高度
void updateHeight(TreeNode* node) {
    node->height = max(height(node->left), height(node->right)) + 1;
}

// 右旋操作
TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    // 旋转
    x->right = y;
    y->left = T2;

    // 更新高度
    updateHeight(y);
    updateHeight(x);

    return x;
}

// 左旋操作
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    // 旋转
    y->left = x;
    x->right = T2;

    // 更新高度
    updateHeight(x);
    updateHeight(y);

    return y;
}

// 插入节点并进行平衡操作
TreeNode* insert(TreeNode* node, int value) {
    if (!node) return new TreeNode(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else
        return node; // 不允许重复值

    // 更新当前节点的高度
    updateHeight(node);

    // 检查当前节点是否平衡
    int balance = getBalanceFactor(node);

    // 左侧不平衡
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    // 右侧不平衡
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    // 左右子树不平衡
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // 右左子树不平衡
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// 中序遍历二叉排序树
void inOrderTraversal(TreeNode* root, vector<int>& result) {
    if (root) {
        inOrderTraversal(root->left, result);
        result.push_back(root->value);
        inOrderTraversal(root->right, result);
    }
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
    ofstream outputFile("7_output3.txt");

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

    // 构建平衡的二叉排序树
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

    inputFile.close();
    outputFile.close();
    return 0;
}
