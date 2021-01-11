#include <iostream>
#include <vector>
using namespace std;

int partition(long long* a, int l, int r) {
	int v = a[(l + r) / 2];
	int i = l, j = r;
	while (i <= j) {
		while (a[i] < v) {
			i++;
		}
		while (a[j] > v) {
			j--;
		}
		if (i >= j) {
			break;
		}
		swap(a[i++], a[j--]);
	}
	return j;
}

void quickSort(long long* a, int l, int r) {
	if (l < r) {
		int q = partition(a, l, r);
		quickSort(a, l, q);
		quickSort(a, q + 1, r);
	}
}

int main() {
	int i, n;
	cin >> n;
	long long* a = new long long[n];
	for (i = 0; i < n; i++)
		cin >> a[i];
	quickSort(a, 0, n - 1);
	for (i = 0; i < n; i++)
		cout << a[i] << " ";
	delete[]a;
}

