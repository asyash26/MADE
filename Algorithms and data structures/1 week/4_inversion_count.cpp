#include <iostream>
#include <vector>
using namespace std;


vector <long int> readArray() {
	int n;
	long int buf;
	vector <long int> a;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> buf;
		a.push_back(buf);
	}
	return a;
}

void writeArray(vector <long int> a) {
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
}

vector <long int> merge(vector <long int> a, vector <long int> b, long long* count) {
	int n = a.size(), m = b.size();
	int i = 0, j = 0;
	vector <long int> c;
	while ((i + j) < (n + m)) {
		if ((j == m) || ((i < n) && (a[i] < b[j]))) {
			c.push_back(a[i]);
			i++;
		}
		else {
			*count += n - i;
			c.push_back(b[j]);
			j++;
		}
	}
	return c;
}


vector <long int> inversionCount(vector <long int> a, long long* count) {
	int n = a.size();
	if (n == 1)
		return a;
	int mid = n / 2;
	vector<long int> l(a.begin(), a.begin() + mid);
	vector<long int> r(a.begin() + mid, a.end());
	l = inversionCount(l, *&count);
	r = inversionCount(r, *&count);
	return merge(l, r, *&count);
}

int main() {
	long long count = 0;
	vector <long int> a = readArray();
	a = inversionCount(a, &count);
	cout << count;
}

