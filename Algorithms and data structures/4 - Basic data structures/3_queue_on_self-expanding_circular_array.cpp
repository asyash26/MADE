#include <iostream>
using namespace std;
 
class Queue {
	const int initialCapacity = 2;
public:
	long end;
	long begin;
	long capacity;
	long* elements;
	long size;
 
	Queue() {
		begin = 0;
		end = 0;
		capacity = initialCapacity;
		elements = new long[capacity];
		size = 0;
	}
	~Queue() {
		delete[] elements;
	}
	void push(long value) {
		if (end == begin && size != 0) {
			end = capacity;
			ensureCapacity();
			begin = 0;
		}
		elements[end] = value;
		end = (end + 1) % capacity;
		size++;
	}
	long pop() {
		if ((size == capacity / 4) && size > initialCapacity) {
			decreaseCapacity();
			begin = 0;
			end = size;
		}
		long buf = elements[begin];
		begin = (begin + 1) % capacity;
		size--;
		return buf;
	}
	void decreaseCapacity() {
		rotate(&elements[0], &elements[begin], &elements[capacity]);
		capacity /= 2;
		long* newElements = new long[capacity];
		memcpy(newElements, elements, sizeof(long) * capacity);
		delete[] elements;
		elements = newElements;
	}
	void ensureCapacity() {
		rotate(&elements[0], &elements[begin], &elements[capacity]);
		capacity *= 2;
		long* newElements = new long[capacity];
		memcpy(newElements, elements, sizeof(long) * capacity);
		delete[] elements;
		elements = newElements;
	}
	long get(long index) {
		return elements[index];
	}
};
 
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int operationsNumber;
	long value;
	char operation;
	Queue queue;
	cin >> operationsNumber;
	for (int i = 0; i < operationsNumber; i++) {
		cin >> operation;
		switch (operation) {
		case('+'):
			cin >> value;
			queue.push(value);
			break;
		case('-'):
			cout << queue.pop() << endl;
			break;
		}
	}
	return 0;
}
