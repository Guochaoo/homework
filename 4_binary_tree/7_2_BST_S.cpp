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
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// 插入
TreeNode *insert(TreeNode *root, int value)
{
    if (!root)
        return new TreeNode(value);
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
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

// 删除
TreeNode *delete_node(TreeNode *root, int key)
{
    if (!root)
        return nullptr;
    if (key < root->value)
        root->left = delete_node(root->left, key);
    else if (key > root->value)
        root->right = delete_node(root->right, key);
    else
    {
        if (!root->left)
        {
            TreeNode *temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right)
        {
            TreeNode *temp = root->left;
            delete root;
            return temp;
        }
        TreeNode *successor = root->right;
        while (successor->left)
            successor = successor->left;
        root->value = successor->value;
        root->right = delete_node(root->right, successor->value);
    }
    return root;
}

// 计算平均查找长度
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
void read_input(const string &filename, TreeNode *&root, int &x)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cerr << "文件打开失败！" << endl;
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
    if (getline(inputFile, line))
    {
        x = stoi(line);
    }

    inputFile.close();
}

// 输出
void write_output(const string &filename, TreeNode *root, int x, bool afterDeletion)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open())
    {
        cerr << "输出文件打开失败" << endl;
        exit(1);
    }

    vector<int> inOrderResult;
    inorder(root, inOrderResult);

    if (!afterDeletion)
    {
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
    }
    else
    {
        outputFile << "删除节点" << x << "后中序遍历结果: ";
        for (int n : inOrderResult)
        {
            outputFile << n << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
}

int main()
{
    TreeNode *root = nullptr;
    int x;

    // 输入
    read_input("7_input.txt", root, x);
    //输出
    write_output("7_output2.txt", root, x, false);

    //删除指定节点
    root = delete_node(root, x);
    //输出
    write_output("7_output2.txt", root, x, true);

    return 0;
}
