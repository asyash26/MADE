#include <iostream>
#include <cmath>
using namespace std;
 
long long fieldSpeed, forestSpeed;
double border;
const double EPS = pow(10, -4);
 
double calculateTime(double entryPoint) {
	return sqrt(pow(1 - border, 2) + pow(entryPoint, 2)) / fieldSpeed +
		sqrt(pow(border, 2) + pow(1 - entryPoint, 2)) / forestSpeed;
}
 
double ternarySearch(double left, double right) {
	double m1, m2;
	int iterCount = ceil(2 * log((right - left) / EPS) / log(3.0 / 2.0));
	for (int i = 0; i < iterCount; i++) {
		m1 = (left * 2 + right) / 3;
		m2 = (left + right * 2) / 3;
		if (calculateTime(m1) < calculateTime(m2))
			right = m2;
		else
			left = m1;
	}
	return right;
}
 
int main() {
	cin >> fieldSpeed >> forestSpeed >> border;
	cout << ternarySearch(0, 1);
}