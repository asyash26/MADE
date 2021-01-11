#include <iostream>
#include <string>
using namespace std;

struct node {
    int key;
    node* left;
    node* right;
};

node* tree;

node* min(node*& tree) {
    if (tree->left == NULL)
        return tree;
    return min(tree->left);
}

void insert(node*& tree, int x) {
    if (tree == nullptr) {
        tree = new node();
        tree->key = x;
        tree->left = NULL;
        tree->right = NULL;
        return;
    }
    else if (x < tree->key)
        insert(tree->left, x);
    else if (x > tree->key)
        insert(tree->right, x);
}

void delete_(node*& tree, int x) {
    if (tree == NULL)
        return;
    if (x < tree->key)
        delete_(tree->left, x);
    else if (x > tree->key)
        delete_(tree->right, x);
    else if (tree->right != NULL && tree->left != NULL) {
        tree->key = min(tree->right)->key;
        delete_(tree->right, tree->key);
    }
    else {
        if (tree->left != NULL)
            tree = tree->left;
        else tree = tree->right;
    }
}

node* exists(node*& tree, int x)
{
    if (tree == NULL || x == tree->key)
        return tree;
    if (x < tree->key)
        return exists(tree->left, x);
    else
        return exists(tree->right, x);
}

node* next(int x)
{
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
                insert(tree, x);
        }
        else if (action == "delete") {
            if (exists(tree, x))
                delete_(tree, x);
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