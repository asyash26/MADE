#include <iostream>
using namespace std;
 
class MyStack {
public:
	struct Node {
		long value;
		long min;
		Node* next;
	};
 
	Node* head;
 
	MyStack() :head(NULL) {
	}
	~MyStack() {
		Node* current = head;
		while (current != NULL) {
			current = head->next;
			delete head;
			head = current;
		}
	}
	void push(long value) {
		Node* current = new Node;
		current->value = value;
		current->next = head;
		if ((head != NULL) && (value >= head->min))
			current->min = head->min;
		else
			current->min = value;
		head = current;
	}
	void pop() {
		Node* current = head;
		head = head->next;
		delete current;
	}
	long min() {
		return head->min;
	}
};
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long operationsNumber, number;
	int operation;
	MyStack stack;
	cin >> operationsNumber;
	for (long i = 0; i < operationsNumber; i++) {
		cin >> operation;
		switch (operation) {
		case 1:
			cin >> number;
			stack.push(number);
			break;
		case 2:
			stack.pop();
			break;
		case 3:
			cout << stack.min() << '\n';
			break;
		}
	}
	return 0;
}
