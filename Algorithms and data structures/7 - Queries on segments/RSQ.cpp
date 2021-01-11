#include <iostream>
#include <string>
using namespace std;


class FenvicTree {
public:
	long long* fenvicTree;
	long long size;
	long long* numbers;

	FenvicTree(long long* numbers_, long long arraySize) {
		numbers = numbers_;
		size = arraySize;
		fenvicTree = new long long[size];
		for (long long i = 0; i < size; i++)
			fenvicTree[i] = 0;
		for (long long i = 0; i < size; i++)
			add(i, numbers[i]);
	}

	~FenvicTree() {
		delete[] fenvicTree;
		delete[] numbers;
	}

	long long f(long long index) {
		index = index;
		return index & (index + 1);
	}

	long long get(long long index) {
		long long result = 0;
		while (index >= 0) {
			result += fenvicTree[index];
			index = f(index) - 1;
		}
		return result;
	}

	long long sum(long long left, long long right) {
		if (left == 0)
			return get(right);
		return get(right) - get(left - 1);
	}

	void add(long long index, long long value) {
		while (index < size) {
			fenvicTree[index] += value;
			index = index | (index + 1);
		}
	}

	void set(long long index, long long value) {
		long long d = value - numbers[index];
		numbers[index] = value;
		add(index, d);
	}
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long long arraySize, i, a, b, j;
	string operation;
	cin >> arraySize;
	long long* numbers = new long long[arraySize];
	for (i = 0; i < arraySize; i++) {
		cin >> numbers[i];
	}
	FenvicTree tree = FenvicTree(numbers, arraySize);
	while (cin >> operation >> a >> b) {
		if (operation == "sum") {
			cout << tree.sum(--a, --b) << endl;
		}
		else {
			tree.set(--a, b);
		}
	}
	return 0;
}