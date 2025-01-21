#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Node {
    Node *parent;
    Node *left;
    Node *right;
    int data;
};

Node *root;

void preOrderTravsl(Node *p) {
    if (!p) return;
    cout << p->data;
    preOrderTravsl(p->left);
    preOrderTravsl(p->right);
}

void inOrderTravsl(Node *p) {
    if (!p) return;
    inOrderTravsl(p->left);
    cout << p->data;
    inOrderTravsl(p->right);
}

void postOrderTravsl(Node *p) {
    if (!p) return;
    postOrderTravsl(p->left);
    postOrderTravsl(p->right);
    cout << p->data;
}

void levelOrderTravsl(Node *root) {
    queue<Node *> q;
    q.push(root);

    while(!q.empty()) {
        Node *p = q.front(); q.pop();
        cout << p->data;
        if (p->left) q.push(p->left);
        if (p->right) q.push(p->right);
    }
}

void preOrderTravslStack(Node *root) {  
    stack<Node *> st;
    st.push(root);

    while(!st.empty()) {
        Node *p = st.top(); st.pop();
        cout << p->data;
        if (p->right) st.push(p->right);
        if (p->left) st.push(p->left);
    }
}

int main() {
    
}