#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long nextArrayElement(long long prevElement) {
	return (23 * prevElement + 21563) % 16714589;
}

long long nextLeft(long long prevLeft, long long answer, long long arraySize, long long index) {
	return (17 * prevLeft + 751 + answer + 2 * (index + 1)) % arraySize + 1;
}

long long nextRight(long long prevRight, long long answer, long long arraySize, long long index) {
	return (13 * prevRight + 593 + answer + 5 * (index + 1)) % arraySize + 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long long i, j, arraySize, queryCount, firstElement, left, right, answer, k, l, r, size;
	// Read data and fill the array
	cin >> arraySize >> queryCount >> firstElement;
	long long* array = new long long[arraySize];
	array[0] = firstElement;
	for (i = 1; i < arraySize; i++)
		array[i] = nextArrayElement(array[i - 1]);

	// Fill the sparse table
	size = ceil(log2(arraySize)) + 1;
	vector <vector <long long>> st(size, vector <long long>(arraySize));
	for (i = 0; (1 << i) <= arraySize; i++) {
		for (j = 0; j + (1 << i) <= arraySize; j++)
			st[i][j] = (i ? min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]) : array[j]);
	}

	// Fill array with max pows
	long long* maxPow = new long long[arraySize];
	for (i = 0; i <= arraySize; i++)
		maxPow[i] = (i > 1 ? maxPow[i / 2] + 1 : 0);

	// Iterate through all the queries
	cin >> left >> right;
	answer = 0;
	for (i = 0; i < queryCount; i++) {
		l = min(left, right) - 1;
		r = max(left, right) - 1;
		k = maxPow[r - l + 1];
		answer = min(st[k][l], st[k][r - (1 << k) + 1]);
		if (i != queryCount - 1) {
			left = nextLeft(left, answer, arraySize, i);
			right = nextRight(right, answer, arraySize, i);
		}
	}
	cout << left << " " << right << " " << answer;
	return 0;
}