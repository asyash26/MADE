#include <vector>
#include <iostream>
using namespace std;
 
const int M = 101;
 
vector <int> countSort(vector <int> a) {
	int i, j = 0;
	vector<int> cnt(M, 0);
	for (i = 0; i < a.size(); i++) {
		cnt[a[i]]++;
	}
	for (i = 0; i < M; i++) {
		while (cnt[i] > 0) {
			a[j++] = i;
			cnt[i]--;
		}
	}
	return a;
}
 
int main() {
	int i, buf;
	vector <int> a;
	while (cin.peek() != '\n') {
		cin >> buf;
		a.push_back(buf);
	}
	a = countSort(a);
	for (i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
}
