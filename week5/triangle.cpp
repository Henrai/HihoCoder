#include <iostream>
using namespace std;
int main(){
	int n;
	int a[110][110];
	int dp[110][110];
	int ans= -1;
	for(int i = 0; i < 110; i++)
		for(int j = 0; j < 110; j++ ) {
			dp[i][j] = 0;
			a[i][j] = 0;
		}
	cin>>n;	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j<=i; j++)
			cin>>a[i][j];

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j<=i; j++)
		{
			dp[i][j] = max(dp[i-1][j-1], dp[i-1][j])+a[i][j];
			if(i == n && dp[i][j] > ans)
				ans = dp[i][j];
		}
	}
	cout<<ans<<endl;
}