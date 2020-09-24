#include <iostream>
#include <vector>
using namespace std;

vector <long int> insertionSort(vector <long int> a) {
	int n = a.size(), j;
	for (int i = 1; i < n; i++) {
		j = i;
		while ((j > 0) & (a[j - 1] > a[j])) {
			swap(a[j - 1], a[j]);
			j--;
		}
	}
	return a;
}

int main() {
	int i, n;
	long int buf;
	vector <long int> array;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> buf;
		array.push_back(buf);
	}
	array = insertionSort(array);
	for (i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
}

