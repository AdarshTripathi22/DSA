#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define display(A) for(auto x : A) cout << x <<" "; cout <<"\n";
#define displayP(A) for(auto x : A) display(x);
#define debug(x) cout << (#x) <<" is " << x <<"\n";
#define endl "\n";

struct Node {
	int data;
	Node *right; Node *left;

	Node(int val){
		data = val;
		right = left = NULL;
	}
};

Node *createTree(Node *root, vector<string> v, int n){
	queue<Node *> q;
	Node *p; int i = 0;

	while(i<n){
		p = (v[i]!="null") ? new Node(stoi(v[i])) : new Node(INT_MIN);
		if(root == NULL) {root = p;}
		else if(q.front()->left == NULL) {q.front()->left = p;}
		else {q.front()->right = p; q.pop();}

		if(v[i]!="null"){q.push(p);} i++;
	}

	if(root == NULL || root->data == INT_MIN) return NULL;

	stack<Node *> s;
	s.push(root);

	while(!s.empty()){
		p = s.top(); s.pop();
		if(p->left) {if(p->left->data == INT_MIN){p->left = NULL;}else{s.push(p->left);}}
		if(p->right) {if(p->right->data == INT_MIN){p->right = NULL;}else{s.push(p->right);}}
	}
	return root;
}

int Max = 0,Mode = 0,Count = 0, Prev = -1;

void mode(Node *root){
	if(root){
		mode(root->left);

		if(Prev != -1){
			if(Prev == root->data){
				Count++;
			}else{
				Count = 1;
			}
		}
		else {Count = 1;}
		if(Count > Max){
			Max = Count;
			Mode = root->data;
		}
		Prev = root->data;

		mode(root->right);
	}
}

void inorder_traversal(Node *root){
	if(root){
		inorder_traversal(root->left); cout<<root->data<<" "; inorder_traversal(root->right);
	}
}

void level_and_parent(Node *root,int key,int &level1,int &parent1){
	if(root == NULL) return;
	while(root != NULL){
		if(root->data > key){
			parent1 = root->data;
			level1++;
			root = root->left;
		}
		else if(root->data < key){
			parent1 = root->data;
			level1++;
			root = root->right;
		}
		else{
			return;
		}
	}
	return;
}

void check_for_cousins(){
	Node *root = nullptr;
	vector<string> v; string k;

	int n1,n2; cin>>n1>>n2;

	while(cin>>k && k!="-1") v.push_back(k);

	root = createTree(root,v,v.size());

	int level1=0,parent1=root->data,level2=0,parent2=root->data;

	level_and_parent(root,n1,level1,parent1);

	level_and_parent(root,n2,level2,parent2);

	if(level1 == level2 && parent1 != parent2) {cout<<1<<endl;}
	else {cout<<0<<endl;}
}

bool isBST(Node *root,int lo, int hi){
	if(root == NULL) return 1;

	if(root->data > hi || root->data < lo) return 0;

	return isBST(root->left,lo,root->data-1) && isBST(root->right,root->data+1,hi);

}

void check_for_BST(){
	Node *root = nullptr;

	vector<string> v; string k;

	while(cin>>k && k!="-1") v.push_back(k);

	root = createTree(root,v,v.size());

	if(isBST(root,INT_MIN,INT_MAX)) {cout<<1<<endl;}
	else {cout<<0<<endl;}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	// vector<string> v; string k;
	// while(cin>>k) v.push_back(k);

	// Node *root = nullptr;

	// root = createTree(root,v,v.size());
	// mode(root);
	// cout<<Mode<<endl;
	int t; cin>>t;
	while(t--){
		check_for_BST();
	}
}
