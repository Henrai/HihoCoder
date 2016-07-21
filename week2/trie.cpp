#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class Node {
public:
	char c;
	int count;
	Node *left;
	Node *right;
	Node *mid;
	Node(char chr) {
		c = chr;
		count = 0;
		left = NULL;
		right = NULL;
		mid = NULL;
	}
};
class TST {
public:
	Node *root;;
	TST(){
		root = NULL;
	}
	~TST() {
		clear(root);
	}
	void clear(Node*& x){
		if (x->left != NULL)
			clear(x->left);
		if(x->right != NULL)
			clear(x->right);
		if(x->mid != NULL)
			clear(x->mid);
		delete x;
		x = NULL;
	}
	void insert(string s) {
		root = insert(root, s,0);
	}
	Node* insert(Node* x, string s, int depth) {
		char c = s[depth];
		if(x == NULL) {
			x = new Node(c);
		}
		if(c < x->c) {
			x->left = insert(x->left, s, depth);
		}
		else if(c > x->c) {
			x->right = insert(x->right, s, depth);
		}
		else if(depth < s.length()-1) {
			x->count++;
			x->mid = insert(x->mid, s, depth+1);
		}
		else x->count++;
		return x;
	}
	int ask(string s) {
		Node *x = ask(root, s ,0);
		if(x == NULL)
			return 0;
		else
			return x->count;
	}
	Node* ask(Node *x, string s, int d) {
		char c = s[d];
		if(x == NULL)
			return NULL;
		if(c < x->c) return ask(x->left, s, d);
		else if(c > x->c) return ask(x->right, s, d);
		else if(d < s.length() - 1) return ask(x->mid, s, d+1);
		else return x;
	}
};
int main() {
	int n;
	TST *trie = new TST();
	cin>>n;
	for(int i = 0; i < n; i++) {
		string s;
		cin>>s;
		trie->insert(s);
	}
	cin>>n;
	for(int i = 0; i < n; i++) {
		string s;
		cin>>s;
		cout<<trie->ask(s)<<endl;
	}
	delete trie;
}