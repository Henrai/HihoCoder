#include <iostream>
#include <algorithm>
using namespace std;

double card[4];
int visit[4];

bool dfs(int depth, double number){
	if(depth == 4){
		if(number == 24)
			return true;
		else return false;
	}
	else {
		bool ans = dfs(depth+1, number * card[depth]) || dfs(depth+1, number + card[depth]) 
			|| dfs(depth+1, number - card[depth]) || dfs(depth+1, -1*number + card[depth]);
		if(number != 0)
			ans = ans || dfs(depth+1, card[depth] / number);
		if((int)(number / card[depth]) != 0)
			ans = ans || dfs(depth+1, number / card[depth]); 
		return ans;
	}
}

int main()
{
	int n;
	cin>>n;
	for(int i = 0; i < n; i++) 
	{
		int flag = 0;
		for(int j = 0; j < 4; j++)
			cin >> card[j];
		sort(card, card+4);
		do{
			if(dfs(1, card[0])){
				flag = 1;
				break;
			}
		}while(next_permutation(card, card+4));
		if(flag) {
			cout <<"Yes\n";
		}
		else {
			cout<<"No\n";
		}
	}

}
