#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
int min(int a, int b, int c) {
	int min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return min;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string a, b;
	int m, n;
	cin >> a >> b;
	m = a.size();
	n = b.size();
	vector <vector <int>> dp(m + 1, vector <int>(n + 1));
	dp[0][0] = 0;
	for (int j = 1; j <= n; j++)
		dp[0][j] = dp[0][j - 1] + 1;
	for (int i = 1; i <= m; i++) {
		dp[i][0] = dp[i - 1][0] + 1;
		for (int j = 1; j <= n; j++) {
			if (a.at(i - 1) != b.at(j - 1))
				dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1);
			else
				dp[i][j] = dp[i - 1][j - 1];
		}
	}
	cout << dp[m][n];
	return 0;
}
