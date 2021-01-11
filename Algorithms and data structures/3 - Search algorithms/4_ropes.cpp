#include <iostream>
using namespace std;
 
long long ropesNumber, housesNumber;
 
long long max(long long* array, long long size) {
	long long max = array[0];
	for (long long i = 1; i < size; i++)
		if (array[i] > max)
			max = array[i];
	return max;
}
 
bool isLengthAcceptable(long long ropeLength, long long* ropes) {
	long long cutRopesCount = 0;
	for (long long i = 0; i < ropesNumber; i++)
		cutRopesCount += ropes[i] / ropeLength;
	return cutRopesCount >= housesNumber;
}
 
long long binSearch(long long left, long long right, long long* ropes) {
	if (left == right - 1)
		if (isLengthAcceptable(right, ropes))
			return right;
		else
			return left;
	long long middle = (left + right) / 2;
	if (isLengthAcceptable(middle, ropes))
		return binSearch(middle, right, ropes);
	else
		return binSearch(left, middle, ropes); 
}
 
int main() {
	cin >> ropesNumber >> housesNumber;
	long long* ropes = new long long[ropesNumber];
	for (long long i = 0; i < ropesNumber; i++)
		cin >> ropes[i];
	if (isLengthAcceptable(1, ropes))
		cout << binSearch(1, max(ropes, ropesNumber), ropes);
	else
		cout << 0;
}
