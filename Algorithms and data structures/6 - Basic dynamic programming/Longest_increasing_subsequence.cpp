#include <iostream>
#include <stack>
using namespace std;
 
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long n, max, index;
	cin >> n;
	pair<long, long>* dp = new pair<long, long>[n];
	pair<long, long> maxPair;
	stack<long> answer;
	long* mas = new long[n];
	dp[0] = make_pair(1, -1);
	cin >> mas[0];
	for (long i = 1; i < n; i++) {
		cin >> mas[i];
		max = 1;
		index = -1;
		for (long j = i - 1; j >= 0; j--)
			if (mas[j] < mas[i] && dp[j].first >= max) {
				max = dp[j].first;
				index = j;
			}
		if (index >= 0)
			dp[i] = make_pair(max + 1, index);
		else
			dp[i] = make_pair(1, -1);
	}
	maxPair = dp[0];
	index = 0;
	for (long i = 1; i < n; i++) {
		if (dp[i].first > maxPair.first) {
			maxPair = dp[i];
			index = i;
		}
	}
	cout << maxPair.first << endl;
	while (index >= 0) {
		answer.push(mas[index]);
		index = dp[index].second;
	}
	while (!answer.empty()) {
		cout << answer.top() << " ";
		answer.pop();
	}
	return 0;
}