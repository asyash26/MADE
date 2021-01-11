#include <iostream>
using namespace std;
 
int binSearch(int left, int right, int x, long long* array) {
	if (left == right - 1) {
		if (abs(array[left] - x) <= abs(array[right] - x))
			return array[left];
		else 
			return array[right];
	}
	int middle = (left + right) / 2;
	if (x == array[middle])
		return x;
	if (x < array[middle])
		return binSearch(left, middle, x, array);
	else
		return binSearch(middle, right, x, array);
}
 
int main() {
	int i, x, arrayLength, requestsAmount;
	cin >> arrayLength >> requestsAmount;
	long long* array = new long long[arrayLength];
	for (i = 0; i < arrayLength; i++)
		cin >> array[i];
	for (i = 0; i < requestsAmount; i++) {
		cin >> x;
		cout << binSearch(0, arrayLength, x, array) << endl;
	}
}
