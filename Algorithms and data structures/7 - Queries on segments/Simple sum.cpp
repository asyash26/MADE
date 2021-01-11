#include <iostream>
#include <math.h>
using namespace std;

const long long NUMBERS_ARRAY_CONST = pow(2, 16);
const long long QUERY_ARRAY_CONST = pow(2, 30);

long long mod(long long x, long long y) {
	long long result = x % y;
	return result < 0 ? result + y : result;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long long arraySize, x, y, queryCount, z, t, prev, i, left, right, number;
	long long resultSum = 0;

	cin >> arraySize >> x >> y >> number;
	cin >> queryCount >> z >> t >> prev;

	long long* sum = new long long[arraySize + 1];
	sum[0] = 0;
	sum[1] = number;
	for (i = 1; i < arraySize; i++) {
		number = (x * number + y) % NUMBERS_ARRAY_CONST;
		sum[i + 1] = sum[i] + number;
	}

	for (i = 0; i < queryCount; i++) {
		left = prev % arraySize;
		prev = mod(z * prev + t, QUERY_ARRAY_CONST);
		right = prev % arraySize;
		prev = mod(z * prev + t, QUERY_ARRAY_CONST);
		if (left > right)
			swap(left, right);
		resultSum += sum[right + 1] - sum[left];
	}
	cout << resultSum;
	return 0;
}