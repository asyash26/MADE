#include <iostream>
#include <cmath>
using namespace std;
 
const double EPS = pow(10, -6);
 
double function(double x) {
	return x * x + sqrt(x);
}
 
double binSearch(double left, double right, double y) {
	double middle;
	int iterCount = ceil(log((right - left) / EPS) / log(2));
	for (int i = 0; i < iterCount; i++) {
		middle = (left + right) / 2;
		if (function(middle) < y)
			left = middle;
		else
			right = middle;
	}
	return right;
}
 
int main() {
	long double y, left = 0, right = 1;
	cin >> y;
	while (function(right) < y)
		right *= 2;
	cout.precision(8);
	cout << binSearch(left, right, y);
}