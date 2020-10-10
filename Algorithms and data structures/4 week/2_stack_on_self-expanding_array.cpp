#include <iostream>
using namespace std;
 
class Vector {
public:
	int size;
	int capacity;
	int* elements;
 
	Vector() {}
 
	Vector(int n) {
		size = 0;
		capacity = n;
		elements = new int[capacity];
	}
	void add(int value) {
		if (size + 1 > capacity)
			ensureCapacity();
		elements[size] = value;
		size++;
	}
	void erase() {
		if (size == ceil(capacity / 4))
			decreaseCapacity();
		size--;
	}
	void decreaseCapacity() {
		capacity /= 2;
		int* newElements = new int[capacity];
		memcpy(newElements, elements, sizeof(int) * capacity);
		delete[] elements;
		elements = newElements;
	}
	void ensureCapacity() {
		capacity *= 2;
		int* newElements = new int[capacity];
		memcpy(newElements, elements, sizeof(int) * capacity);
		delete[] elements;
		elements = newElements;
	}
	int get(int index) {
		return elements[index];
	}
};
 
class Stack {
	const int initialCapacity = 10;
public:
	Vector vector;
 
	Stack() {
		vector = Vector(initialCapacity);
	}
	void push(int value) {
		vector.add(value);
	}
	int pop() {
		vector.erase();
		return vector.get(vector.size);
	}
};
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	char buf;
	int a, b;
	Stack stack;
	while (cin.peek() != '\n') {
		cin >> buf;
		if (isdigit(buf))
			stack.push((int)buf - '0');
		else {
			b = stack.pop();
			a = stack.pop();
			switch (buf) {
			case '+':
				stack.push(a + b);
				break;
			case '-':
				stack.push(a - b);
				break;
			case '*':
				stack.push(a * b);
				break;
			}
		}
	}
	cout << stack.pop();
	return 0;
}