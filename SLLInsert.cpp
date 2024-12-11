#include<iostream>
using namespace std;
struct Node{
    int data;
    Node* next;
};
int Delete(Node* p, int x){
    if (p == NULL)
    {
        return;
    }
    int i;
        for (i = 0; i < x - 1; i++)
        {
            if (p->next != NULL)
            {
                p = p->next;
            }
    }
    p->next = p->next->next;
    return;
}
void Insert(Node *p, int data, int x)
{
    if (x == 0)
    {
        Node *new_node = new Node;
        new_node->data = data;
        new_node->next = p;
        return;
    }
    for (int i = 0; i < x - 1; i++)
    {
        if (p->next != NULL)
        {
            p = p->next;
        }
    }
    Node *new_node = new Node;
    new_node->data = data;
    new_node->next = p->next;
    p->next = new_node;
    return;
}
int main(){
    Node* new_node = new Node;
    new_node->data = 101;
    new_node->next = NULL;
    Insert(new_node, 202, 1);
    return 0;
}
