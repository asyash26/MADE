#include <iostream>
#include <string>
using namespace std;

struct node {
    int key, prior;
    node *left, *right;
    node(int k) {
        key = k;
        prior = rand();
        left = right = NULL;
    }
};

node *tree;

node *merge(node *a, node *b) {
    if (!a || !b)
        return a ? a : b;
    if (a->prior > b->prior) {
        a->right = merge(a->right, b);
        return a;
    } else {
        b->left = merge(a, b->left);
        return b;
    }
}

void split(node *tree, int key, node *&a, node *&b) {
    if (!tree)
        a = b = NULL;
    else if (tree->key < key) {
        split(tree->right, key, tree->right, b);
        a = tree;
    } else {
        split(tree->left, key, a, tree->left);
        b = tree;
    }
}

void insert(int key) {
    node *tn = new node(key), *t1, *t2;
    split(tree, key, t1, t2);
    tree = merge(t1, tn);
    tree = merge(tree, t2);
}

void dispose(node *tree) {
    if (tree == NULL)
        return;
    dispose(tree->left);
    dispose(tree->right);
    delete tree;
}

void remove(int key) {
    node *t1, *t2, *t3;
    split(tree, key, t1, t2);
    split(t2, key + 1, t2, t3);
    tree = merge(t1, t3);
    dispose(t2);
}

node* exists(node*& tree, int x) {
    if (tree == NULL || x == tree->key)
        return tree;
    if (x < tree->key)
        return exists(tree->left, x);
    else
        return exists(tree->right, x);
}

node* next(int x) {
    node* cur = tree;
    node* need = NULL;
    while (cur != NULL) {
        if (cur->key > x) {
            need = cur;
            cur = cur->left;
        }
        else
            cur = cur->right;
    }
    return need;
}

node* prev(int x) {
    node* cur = tree;
    node* need = NULL;
    while (cur) {
        if (x > cur->key) {
            need = cur;
            cur = cur->right;
        }
        else
            cur = cur->left;
    }
    return need;
}

int main() {
    string action;
    int x;
    node *prevNode, *nextNode;

    while (cin >> action) {
        cin >> x;

        if (action == "insert") {
            if (!exists(tree, x))
                insert(x);
        }
        else if (action == "delete") {
            if (exists(tree, x))
                remove(x);
        }
        else if (action == "exists") {
            if (exists(tree, x))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }
        else if (action == "next") {
            nextNode = next(x);
            if (nextNode)
                cout << nextNode->key << endl;
            else
                cout << "none" << endl;
        }
        else if (action == "prev") {
            prevNode = prev(x);
            if (prevNode)
                cout << prevNode->key << endl;
            else
                cout << "none" << endl;
        }
    }
    return 0;
}
