#include <iostream>
#include <string>
using namespace std;

struct node {
	int key;
	int height;
	node* left = NULL;
	node* right = NULL;
	node(int keyValue) {
		key = keyValue;
		height = 1;
	}
};

node* tree;

int height(node* root) {
	return root ? root->height : 0;
}

int countBalance(node* root) {
	return height(root->right) - height(root->left);
}

void fix(node* root) {
	int leftNodeHeight = height(root->left);
	int rightNodeHeight = height(root->right);
	root->height = max(leftNodeHeight, rightNodeHeight) + 1;
}

node* rotateRight(node* p) {
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fix(p);
	fix(q);
	return q;
}

node* rotateLeft(node* q) {
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fix(q);
	fix(p);
	return p;
}

node* balance(node* root) {
	fix(root);
	if (countBalance(root) == 2) {
		if (countBalance(root->right) < 0)
			root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	if (countBalance(root) == -2) {
		if (countBalance(root->left) > 0)
			root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	return root;
}

node* insert(node* root, int x) {
	if (!root) return new node(x);
	if (x < root->key)
		root->left = insert(root->left, x);
	else
		root->right = insert(root->right, x);
	return balance(root);
}

node* findMin(node* root) {
	return root->left ? findMin(root->left) : root;
}

node* removeMin(node* root) {
	if (root->left == 0)
		return root->right;
	root->left = removeMin(root->left);
	return balance(root);
}

node* remove(node* root, int x) {
	if (!root) return 0;
	if (x < root->key)
		root->left = remove(root->left, x);
	else if (x > root->key)
		root->right = remove(root->right, x);
	else {
		node* q = root->left;
		node* r = root->right;
		delete root;
		if (!r) return q;
		node* min = findMin(r);
		min->right = removeMin(r);
		min->left = q;
		return balance(min);
	}
	return balance(root);
}

node* next(node* root, int x) {
	node* cur = root;
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

node* prev(node* root, int x) {
	node* cur = root;
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

node* exists(node*& root, int x) {
	if (root == NULL || x == root->key)
		return root;
	if (x < root->key)
		return exists(root->left, x);
	else
		return exists(root->right, x);
}

int main() {
	string action;
	int x;
	node* nextNode, * prevNode;
	while (cin >> action) {
		cin >> x;
		if (action == "insert") {
			if (!exists(tree, x))
				tree = insert(tree, x);
		}
		else if (action == "delete") {
			if (exists(tree, x))
				tree = remove(tree, x);
		}
		else if (action == "exists") {
			if (exists(tree, x))
				cout << "true" << endl;
			else
				cout << "false" << endl;
		}
		else if (action == "next") {
			nextNode = next(tree, x);
			if (nextNode)
				cout << nextNode->key << endl;
			else
				cout << "none" << endl;
		}
		else if (action == "prev") {
			prevNode = prev(tree, x);
			if (prevNode)
				cout << prevNode->key << endl;
			else
				cout << "none" << endl;
		}
	}
	return 0;
}