#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
	Node *left, *right, *father;
	int weight, key;
	Node(int key) {
		left = right = father = NULL;
		weight = rand();
		this->key = key;
	}
};
Node * root;
Node* insert(Node *node, int key) {
	if(root == NULL) {
		root = new Node(key);
		return root;
	}
	if(key < node->key) {
		if(node->left == NULL) {
			node->left = new Node(key);
			node->left->father = node;
			return node->left;
		}
		else 
			return insert(node->left, key);
	}
	else if(key > node->key) {
		if(node->right == NULL) {
			node->right = new Node(key);
			node->right->father = node;
			return node->right;
		}
		else 
			return insert(node->right, key);
	}
	else return node;
}
void leftRotate(Node* a) {
	Node* b = a->right;
	b->father = a->father;
	if(a->father != NULL) {
		if(a->father->left == a)
			a->father->left = b;
		else 
			a->father->right = b;
	}
	a->right = b->left;
	if(b->left != NULL)
		b->left->father = a;
	b->left = a;
	a->father = b;
}
void rightRotate(Node* a) {
	Node* b = a->left;
	b->father = a->father;
	if(a->father != NULL){
		if(a->father != NULL && a->father->left == a)
			a->father->left = b;
		else 
			a->father->right = b;
	}
	a->left = b->right;
	if(b->right != NULL)
		b->right->father = a;
	b->right = a;
	a->father = b;	
}
void rotate(Node* a) {
	while(a->father != NULL) {
		Node *fa = a->father;
		if(a->weight < fa->weight) {
			if(fa->left == a)
				rightRotate(fa);
			else 
				leftRotate(fa);
		}
		else
			break;
	}
}

Node* find(Node* cur, int key) {
	if(cur == NULL)
		return NULL;
	if(key < cur->key)
		return find(cur->left, key);
	else if(key > cur->key)
		return find(cur->right, key);
	else
		return cur;
}
void del(int key) {
	Node *node = find(key);
	if(node == NULL) return;
	// two son
	while(node->left != NULL && node->right != NULL) {
		Node * child = node->left;
		if(child->weight > node->right->weight)
			child = node->right;
		if(child == node->left)
			rightRotate(node);
		else 
			leftRotate(node); 
	}
	//one or zero son
	Node* fa = node->father;
	if(node->left != NULL) {
		node->left->father = fa;
		if(node == fa->left)
			fa->left = node->left;
		else
			fa->right = node->left;
	}
	else if(node->right != NULL) {
		node->right->father = fa;
		if(node == fa->right)
			fa->right = node->right;
		else 
			fa->left = node->right;
	}
	else {
		if (node == fa->right)
			fa->right = NULL;
		else 
			fa->left = NULL;
	}
}
int query(int a) {
	Node* cur = root;
	int ans = 0;
	while(cur != NULL) {
		if(cur->key == a) {
			ans = a;
			break;
		}
		else if (cur->key < a) {
			ans = cur->key;
			cur = cur->right;
		}
		else {
			cur = cur->left;
		}

	}
	return ans;		
}
int main() {
	srand(time(0));
	int n;
	cin>>n;
	while(n) {
		char c;
		int a;
		cin>>c>>a;
		if(c == 'I') {
			rotate(insert(root, a));
			while (root->father != NULL)
					root = root->father;
		}
		else if(c == 'D') {
			del(a);
		}
		else {
			cout<<query(a)<<endl;
		}
		n--;
	}
}
