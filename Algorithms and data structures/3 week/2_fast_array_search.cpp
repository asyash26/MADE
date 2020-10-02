#include <iostream>
#include <algorithm> 
using namespace std;
 
int arrayLength;
 
int lowerBound(int x, long long* array) {
	int left = -1, right = arrayLength, middle;
	while (left < right - 1) {
		middle = (left + right) / 2;
		if (x <= array[middle])
			right = middle;
		else
			left = middle;
	}
	return right;
}
 
int main() {
	int i, requestsAmount, left, right;
	cin >> arrayLength;
	long long* array = new long long[arrayLength];
	for (i = 0; i < arrayLength; i++)
		cin >> array[i];
	sort(array, array + arrayLength);
	cin >> requestsAmount;
	for (i = 0; i < requestsAmount; i++) {
		cin >> left >> right;
		cout << lowerBound(right + 1, array) - lowerBound(left, array) << endl;
	}
}