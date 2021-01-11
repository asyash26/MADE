#include <iostream>
#include <algorithm> 
using namespace std;
 
long long copiesNumber, firstXeroxCopyTime, secondXeroxCopyTime;
 
bool isTimeAcceptable(long long time) {
	long long minCopyTime = min(firstXeroxCopyTime, secondXeroxCopyTime);
	long long madeCopiesNumber = 0;
	if (time >= minCopyTime)
		madeCopiesNumber++;
	madeCopiesNumber += (time - minCopyTime) / firstXeroxCopyTime + (time - minCopyTime) / secondXeroxCopyTime;
	return madeCopiesNumber >= copiesNumber;
}
 
long long binSearch(long long left, long long right) {
	if (left == right - 1)
		if (isTimeAcceptable(left))
			return left;
		else
			return right;
	long long middle = (left + right) / 2;
	if (isTimeAcceptable(middle))
		return binSearch(left, middle);
	else
		return binSearch(middle, right);
}
 
int main() {
	cin >> copiesNumber >> firstXeroxCopyTime >> secondXeroxCopyTime;
	cout << binSearch(1, copiesNumber * min(firstXeroxCopyTime, firstXeroxCopyTime));
}
