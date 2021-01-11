#include <iostream>
#include <vector>
#include <stack>
using namespace std;
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long n, k, coins, index, count, max, i, j;
	vector<pair<long, long>> dp;
	stack<long> result;
	dp.push_back(make_pair(0, -1));
	cin >> n >> k;
	for (i = 0; i < n - 1; i++) {
		if (i != n - 2)
			cin >> coins;
		else
			coins = 0;
		max = dp[i].first;
		index = i;
		for (j = 1; j < k; j++) {
			if (((i - j) >= 0) && (dp[i - j].first > max)) {
				max = dp[i - j].first;
				index = i - j;
			}
		}
		dp.push_back(make_pair(max + coins, index));
	}
	cout << dp[n - 1].first << endl;
	index = n - 1;
	while (index > 0) {
		result.push(index + 1);
		index = dp[index].second;
	}
	result.push(1);
	count = result.size();
	cout << count - 1 << endl;
	for (i = 0; i < count; i++) {
		cout << result.top() << " ";
		result.pop();
	}
	return 0;
}