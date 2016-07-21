#include <stdio.h>
#define N 1000005
#define M 25
int precal[N][M];
int weight[N];
int n;
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	
	scanf("%d", &n);
	int i, j;
	for(i = 1; i <= n; i++)
		scanf("%d", &weight[i]);
	for(i = 1; i <= n; i++) precal[i][0] = weight[i];
	for(j = 1; (1<<j) <= n; j++) 
		for(i = 1; i + (1<<(j-1)) - 1<= n; i++)
				precal[i][j] = min(precal[i][j-1], precal[i+(1<<(j-1))][j-1]);
	int l,r;
	scanf("%d",&n);
	while(n--) {
		scanf("%d%d", &l, &r);
		int t = 0;
		while((1<<(t+1)) <= (r-l) + 1 ) t++;
		printf("%d\n",  min(precal[l][t], precal[r-(1<<t) + 1][t]));	
	}
}
