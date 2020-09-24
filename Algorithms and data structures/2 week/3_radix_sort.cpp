#include <vector>
#include <string>
#include <iostream>
using namespace std;
 
const int CNT_LENGTH = 27;
 
int getDigit(string str, int strLength, int digitNumber) {
	return int(str.substr(strLength - digitNumber - 1, strLength - digitNumber)[0]) - 97;
}
 
vector<string> radixSort(vector<string> a, int n, int m, int k) {
	int j, temp, digit, count;
	for (int digitNumber = 0; digitNumber < k; digitNumber++) {
		vector<int> cnt(CNT_LENGTH, 0);
		vector<string> currentResult(n, "");
		count = 0;
		for (j = 0; j < n; j++) {
			cnt[getDigit(a[j], m, digitNumber)]++;
		}
		for (j = 0; j < CNT_LENGTH; j++) {
			temp = cnt[j];
			cnt[j] = count;
			count += temp;
		}
		for (j = 0; j < n; j++) {
			digit = getDigit(a[j], m, digitNumber);
			currentResult[cnt[digit]] = a[j];
			cnt[digit]++;
		}
		a = currentResult;
	}
	return a;
}
 
int main() {
	int i, n, m, k;
	string buf;
	cin >> n >> m >> k;
	vector<string> a;
	for (i = 0; i < n; i++) {
		cin >> buf;
		a.push_back(buf);
	}
	a = radixSort(a, n, m, k);
	for (i = 0; i < n; i++) {
		cout << a[i] << endl;
	}
}
