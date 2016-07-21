#include <iostream>
using namespace std;
int value[555];
int cost[555];
int dp[100005];
int main() {
	int n,m;
	cin>>n>>m;
	for(int i = 0; i <= m; i++)
		dp[i] = 0;
	for(int i = 1; i <= n; i++)
		cin>>cost[i]>>value[i];
	for(int i = 1; i <= n; i++)
		for(int j = m; j >= cost[i]; j--)
			dp[j] = max(dp[j], dp[j-cost[i]] + value[i]);
	cout<<dp[m]<<endl;
}