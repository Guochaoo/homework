#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void leftinsert(Node* node, int data) {
    if (node == NULL) {
        return;
    }else{
        node->left =newNode(data);
        return;
    }
}
void rightinsert(Node* node, int data) {
    if (node == NULL) {
        return;
    }else{
        node->right =newNode(data);
        return;
    }
}
int leafcount(Node* node) {
    if (node == NULL) {
        return 0;
    }else if (node->left == NULL && node->right == NULL) {
        return 1;
    }else{
        return leafcount(node->left) + leafcount(node->right);
    }
}
void swap(Node* node) {
    if (node == NULL) {
        return;
    }else if(node->left == NULL && node->right == NULL){
        return;
    }else{
        swap(node->left);
        swap(node->right);
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;
        return;
    }
}
int main() {
    Node* root = newNode(1);
    leftinsert(root, 2);
    rightinsert(root->left, 3);
    rightinsert(root, 4);
    rightinsert(root->right, 5);
    leftinsert(root->right, 6);
    rightinsert(root->right->right, 7);
    //构建              1
    //            2          4
    //               3    6     5
    //                               7
    printf("叶结点个数为%d\n", leafcount(root));
    swap(root);
    return 0;
}

