#include <iostream>
using namespace std;

#define N 10005
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int item[N];

struct Node {
	int l,r,weight;
}tree[N<<2];

void build(int l , int r, int x = 1) {
	tree[x].l = l; tree[x].r = r;
	if(l == r) {
		tree[x].weight = item[l];
		return;
	}
	int mid = l + ((r - l)>>1);
	build(l, mid, lson(x));
	build(mid + 1, r, rson(x));
	tree[x].weight = min(tree[lson(x)].weight, tree[rson(x)].weight); 
}
void update(int l, int r, int a, int b, int x = 1) {
	if(l == r && l == a) {
		tree[x].weight = b;
		return ;
	}
	int mid = l + ((r - l)>>1);
	if(a <= mid) update(l, mid, a, b, lson(x));
	else update(mid + 1, r, a, b, rson(x));
	tree[x].weight = min(tree[lson(x)].weight, tree[rson(x)].weight);
}
int query(int l, int r, int x = 1) {
	if(r < tree[x].l || tree[x].r < l) return 2147483647;
	if(l <= tree[x].l && tree[x].r <= r)
		return tree[x].weight;
	return min(query(l, r, lson(x)), query(l, r, rson(x)));
}
int main() {
	int n;
	cin>>n;
	for(int i = 1; i <= n; i++)
		cin>>item[i];
	build(1, n);
	int t;
	cin>>t;
	while(t--) {
		int a, b ,c;
		cin>>a>>b>>c;
		if(a){
			update(1, n, b, c);
		}
		else {
			cout<<query(b, c)<<endl;
		}
	}
}
