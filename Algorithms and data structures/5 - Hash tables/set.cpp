#include <iostream>
#include <string>
using namespace std;

const long M = 1000001;

class Set {
	const long P = 9584017;
	const long A = 265487;

public:
	long* elements;
	bool* empty;

	Set() {
		elements = new long[M];
		empty = new bool[M];
		for (int i = 0; i < M; i++)
			empty[i] = true;
	}

	~Set() {
		delete[] elements;
		delete[] empty;
	}

	void put(long long value) {
		long long i = hashFunction(value);
		while (!empty[i]) {
			if (elements[i] == value)
				return;
			i = (i + 1) % M;
		}
		elements[i] = value;
		empty[i] = false;
	}

	bool exists(long long value) {
		long long i = hashFunction(value);
		while (!empty[i]) {
			if (elements[i] == value)
				return true;
			i = (i + 1) % M;
		}
		return false;
	}

	void del(long long value) {
		long long i = hashFunction(value);
		while (!empty[i]) {
			if (elements[i] == value) {
				empty[i] = true;
				long long j = (i + 1) % M;
				long long a;
				long long b;
				while (!empty[j]) {
					if (j < i)
						a = M + 1 - (i - j);
					else
						a = i - j;
					if (hashFunction(elements[j]) < j)
						b = M + 1 - (j - hashFunction(elements[j]));
					else
						b = hashFunction(elements[j]) - j;
					if (b >= a) {
						swap(elements[i], elements[j]);
						swap(empty[i], empty[j]);
						i = j;
					}
					j = (j + 1) % M;
				}
				break;
			}
			i = (i + 1) % M;
		}
	}

	long long hashFunction(long long x) {
		return A * abs(x) % P % M;
	}
};


void main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string operation;
	long long value;
	Set set;
	while (cin >> operation >> value) {
		if (operation == "insert")
			set.put(value);
		else if (operation == "delete")
			set.del(value);
		else if (operation == "exists")
			cout << (set.exists(value) ? "true" : "false") << endl;
	}
}