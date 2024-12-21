/* 1.问题描述
     分别采用二叉链表和顺序表作存储结构，实现对二叉排序树与平衡
 二叉树的操作。
2.基本要求
     (1)用二叉链表作存储结构实现二叉排序树。
      1)以回车符(‘\n’)为输入结束标志，输入数列L，生成一棵二叉排序
 树T；
      2)对二叉排序树T作中序遍历，输出结果；
      3)计算二叉排序树T查找成功的平均查找长度，输出结果；
      4)输入元素x，查找二叉排序树T，若存在含x的结点，则删除该结
 点，并作中序遍历(执行操作2)；否则，输出信息“无x”； */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

// 节点结构
struct TreeNode
{
    int value;
    TreeNode *left, *right;
    TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
};
class BST
{
public:
    TreeNode *root;
    BST() : root(nullptr) {}

    // 插入节点
    void insert(int x)
    {
        root = insertRec(root, x);
    }

    // 中序遍历
    void inorder()
    {
        inorderRec(root);
    }

    // 计算平均查找长度
    double averageSearchLength()
    {
        int totalLength = 0, count = 0;
        calcSearchLength(root, 1, totalLength, count);
        return count > 0 ? (double)totalLength / count : 0.0;
    }

    // 查找并删除节点
    bool deleteNode(int x)
    {
        root = deleteRec(root, x);
        return root != nullptr;
    }

private:
    TreeNode *insertRec(TreeNode *node, int x)
    {
        if (node == nullptr)
            return new TreeNode(x);
        if (x < node->value)
            node->left = insertRec(node->left, x);
        else if (x > node->value)
            node->right = insertRec(node->right, x);
        return node;
    }

    void inorderRec(TreeNode *node)
    {
        if (node == nullptr)
            return;
        inorderRec(node->left);
        cout << node->value << " ";
        inorderRec(node->right);
    }

    void calcSearchLength(TreeNode *node, int depth, int &totalLength, int &count)
    {
        if (node == nullptr)
            return;
        totalLength += depth;
        count++;
        calcSearchLength(node->left, depth + 1, totalLength, count);
        calcSearchLength(node->right, depth + 1, totalLength, count);
    }

    TreeNode *deleteRec(TreeNode *root, int key)
    {
        if (root == nullptr)
            return root;
        if (key < root->value)
            root->left = deleteRec(root->left, key);
        else if (key > root->value)
            root->right = deleteRec(root->right, key);
        else
        {
            if (root->left == nullptr)
            {
                TreeNode *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                TreeNode *temp = root->left;
                delete root;
                return temp;
            }
            TreeNode *temp = minValueNode(root->right);
            root->value = temp->value;
            root->right = deleteRec(root->right, temp->value);
        }
        return root;
    }

    TreeNode *minValueNode(TreeNode *node)
    {
        TreeNode *current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
};

// 从文件中读取数据
void readInputFile(const string &filename, BST &tree)
{
    ifstream infile(filename);
    int x;
    while (infile >> x)
    {
        tree.insert(x);
    }
}

// 输出树的中序遍历到文件
void writeOutputFile(const string &filename, BST &tree)
{
    ofstream outfile(filename);
    tree.inorder();
    outfile << endl;
}

int main()
{
    BST tree;
    readInputFile("7_input.txt", tree);

    cout << "中序遍历结果: ";
    writeOutputFile("7_output.txt", tree);

    double avgLength = tree.averageSearchLength();
    cout << "平均查找长度: " << avgLength << endl;

    // 删除元素
    int x;
    cout << "输入要删除的元素: ";
    cin >> x;
    if (tree.deleteNode(x))
    {
        cout << "删除元素后的中序遍历: ";
        writeOutputFile("7_output.txt", tree);
    }
    else
    {
        cout << "无x" << endl;
    }

    return 0;
}
