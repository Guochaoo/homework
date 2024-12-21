#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

//节点定义
struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    int height;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};

// 获取节点高度
int get_height(TreeNode *node)
{
    return node ? node->height : 0;
}

// 更新节点高度
void update_height(TreeNode *node)
{
    if (node)
    {
        node->height = max(get_height(node->left), get_height(node->right)) + 1;
    }
}

// 计算平衡因子
int get_balance(TreeNode *node)
{
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

// 右旋转
TreeNode *right_rotate(TreeNode *y)
{
    TreeNode *x = y->left;
    TreeNode *T = x->right;

    x->right = y;
    y->left = T;

    update_height(y);
    update_height(x);

    return x;
}

// 左旋转
TreeNode *left_rotate(TreeNode *x)
{
    TreeNode *y = x->right;
    TreeNode *T = y->left;

    y->left = x;
    x->right = T;

    update_height(x);
    update_height(y);

    return y;
}

// 插入节点并保持平衡
TreeNode *insert(TreeNode *root, int value)
{
    if (!root)
        return new TreeNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    else
        return root;

    update_height(root);

    int balance = get_balance(root);

    // LL型
    if (balance > 1 && value < root->left->value)
        return right_rotate(root);

    // RR型
    if (balance < -1 && value > root->right->value)
        return left_rotate(root);

    // LR型
    if (balance > 1 && value > root->left->value)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // RL型
    if (balance < -1 && value < root->right->value)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

// 中序遍历
void inorder(TreeNode *root, vector<int> &result)
{
    if (root)
    {
        inorder(root->left, result);
        result.push_back(root->value);
        inorder(root->right, result);
    }
}

//计算平均查找长度
void ASL(TreeNode *root, int depth, int &totalDepth, int &nodeCount)
{
    if (root)
    {
        totalDepth += depth;
        nodeCount++;
        ASL(root->left, depth + 1, totalDepth, nodeCount);
        ASL(root->right, depth + 1, totalDepth, nodeCount);
    }
}

//输入
void read_input(const string &filename, TreeNode *&root)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cerr << "输入文件打开失败" << endl;
        exit(1);
    }

    string line;
    getline(inputFile, line);
    istringstream iss(line);
    int num;

    while (iss >> num)
    {
        root = insert(root, num);
    }

    inputFile.close();
}

//输出
void write_output(const string &filename, TreeNode *root)
{
    ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        cerr << "输出文件打开失败" << endl;
        exit(1);
    }

    vector<int> inOrderResult;
    inorder(root, inOrderResult);

    outputFile << "中序遍历结果: ";
    for (int n : inOrderResult)
    {
        outputFile << n << " ";
    }
    outputFile << endl;

    int totalDepth = 0, nodeCount = 0;
    ASL(root, 1, totalDepth, nodeCount);
    double averageSearchLength = static_cast<double>(totalDepth) / nodeCount;
    outputFile << "平均查找长度: " << fixed << setprecision(2) << averageSearchLength << endl;

    outputFile.close();
}

int main()
{
    TreeNode *root = nullptr;
    // 输入
    read_input("7_input.txt", root);
    // 输出
    write_output("7_output3.txt", root);

    return 0;
}
