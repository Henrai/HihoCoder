#include <cstdio>
#define getSize(t) (t==NULL?0:t->size) 
struct Node
{
    int key, size;
    Node *left, *right;
    Node(int k):key(k),size(1),left(NULL), right(NULL) {}
};
Node *root;
int update(Node* node) {
    node->size = getSize(node->left) + getSize(node->right) + 1;
}
void rightRotate (Node*& rt) {
    Node* k = rt->left;
    rt->left = k->right;
    k->right = rt;
    update(rt);
    update(k);
    rt = k;
}
void leftRotate(Node*& rt) {
    Node* k = rt->right;
    rt->right = k->left;
    k->left = rt;
    update(rt);
    update(k);
    rt = k;
}
void maintain(Node*& rt, bool flag) {
    if(rt == NULL) return;
    if(flag) {
        if(rt->right != NULL && getSize(rt->right->right) > getSize(rt->left)) //case 1'
            leftRotate(rt);
        else if( rt->right != NULL && getSize(rt->right->left) > getSize(rt->left)) { //case 2' 
            rightRotate(rt->right);
            leftRotate(rt);
        }
        else 
            return ;
    }
    else {
        if(rt->left != NULL && getSize(rt->left->left) > getSize(rt->right)) //case 1
            rightRotate(rt);
        else if(rt->left != NULL && getSize(rt->left->right) > getSize(rt->right)) {  //case 2
            leftRotate(rt->left);
            rightRotate(rt);
        }
        else return;
    }
    maintain(rt->left, false);
    maintain(rt->right, true);
    maintain(rt, false);
    maintain(rt, true);
}
Node* insert(Node*& node, int key) {
    if( node == NULL) {
        node = new Node(key);
    }
    else {
        node->size++;
        if(node->key < key) {
            node->right = insert(node->right, key);
        }
        else {
            node->left = insert(node->left, key);
        }
        maintain(node, key >= node->key);
    }
    return node;
}
int query(Node* node, int count, int ask) {
    if(count == ask) return node->key;
    else if(count > ask) return query(node->left, count  - getSize(node->left->right) - 1, ask);
    else if(count < ask) return query(node->right, count + getSize(node->right->left) + 1, ask);
}
int query(int k) {
    if(k > root->size)
        k = root->size;
    return query(root, getSize(root->left)+1, k);
}
void deleteNode(int k) {
    
}
int main() {
    root = NULL;
    int n;
    scanf("%d",&n);
    getchar();
    while(n) {
        char c;
        int a;
        scanf("%c%d",&c,&a);
        getchar();
        if(c == 'I') {
            root = insert(root, a);
        }
        else
            printf("%d\n",query(a));
        n--;
    }
}