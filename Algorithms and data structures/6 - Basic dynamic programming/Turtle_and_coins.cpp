#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
 
void main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, i, j, max_;
	cin >> n >> m;
	stack <bool> answer;
	vector <vector <int>> dp(n + 1, vector <int>(m + 1));
	vector <vector <int>> field(n, vector <int>(m));
	for (i = 0; i < n + 1; i++)
		dp[i][0] = INT_MIN;
	for (j = 0; j < m + 1; j++)
		dp[0][j] = INT_MIN;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> field[i][j];
	dp[1][1] = field[0][0];
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			if (!(i == 1 && j == 1))
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + field[i - 1][j - 1];
	i = n, j = m;
	while (i > 1 || j > 1)
		if (dp[i - 1][j] > dp[i][j - 1]) {
			answer.push(true);
			i--;
		}
		else {
			answer.push(false);
			j--;
		}
	cout << dp[n][m] << endl;
	while (!answer.empty()) {
		if (answer.top())
			cout << "D";
		else
			cout << "R";
		answer.pop();
	}
}