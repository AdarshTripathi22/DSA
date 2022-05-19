#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define display(A) for(auto x : A) cout << x <<" "; cout <<"\n";
#define displayP(A) for(auto x : A) display(x);
#define debug(x) cout << (#x) <<" is " << x <<"\n";
#define endl "\n";

struct Node{
	int data;
	Node *left;
	Node *right;

	Node(int val){
		data = val;
		left = right = NULL;
	}
};

Node *createdNode(Node *root){
	root = new Node(10);
	root->left = new Node(5);
	root->right = new Node(15);
	root->left->left = new Node(2);
	root->left->right = new Node(8);
	root->right->left = new Node(12);
	root->right->right = new Node(17);

	return root;
}

void InorderPrint(Node *root){
	if(root){
		InorderPrint(root->left);
		cout<<root->data<<" ";
		InorderPrint(root->right);
	}
}

int IgetMax(Node *root){
	if(root == NULL) return 0;
	Node *temp = root;
	while(temp->right != NULL){
		temp = temp->right;
	}
	return temp->data;
}

int IgetMin(Node *root){
	if(root == NULL) return 0;

	Node *temp = root;
	while(temp->left != NULL) {temp = temp->left;}

	return temp->data;
}

Node *insertNode(Node *root, int value){
	
	if(root == NULL) {root = new Node(value); return root;}

	Node *p = root,*q = root;
	while(p!=NULL){
		if(p->data > value) {q = p; p = p->left;}
		else {q = p; p = p->right;}
	}

	if(q->data > value) {q->left = new Node(value);}
	else {q->right = new Node(value);}

	return root;
}

void search(Node *&root, Node *&parent, int key){
	if(root == NULL) return;
	parent = root;

	while(root!=NULL){
		if(root->data == key) {return;}
		else if(root->data > key) {parent = root; root = root->left;}
		else {parent = root; root = root->right;}
	}
	return;
}

Node *getMin(Node *root, Node *&successorParent){
	if(root == NULL) return NULL;

	while(root->left != NULL){
		successorParent = root;
		root = root->left;
	}
	return root;
}

Node *getMax(Node *root, Node *predecessorParent){
	if(root == NULL) {return NULL;}

	while(root->right != NULL){predecessorParent = root; root = root->right;}

	return root;
}

void Delete(Node *&root, int key){
	if(root == NULL) return;

	Node *parent = nullptr;
	Node *curr = root;

	search(curr,parent,key);

	if(curr == NULL) {return;}

	//Case 1
	if(curr->left == NULL && curr->right == NULL) {
		if(curr == root) {root = nullptr; }
		else if(parent->left == curr) {parent->left = NULL; }
		else {parent->right = NULL; }
		free(curr); return;
	}

	//Case 2
	if(curr->left != NULL && curr->right != NULL){
		Node *predecessorParent = curr;
		Node *predecessor = getMax(curr->left, predecessorParent);

		curr->data = predecessor->data;
		if(predecessor->right == NULL) {
			if(predecessorParent->left == predecessor){predecessorParent->left = nullptr;}
			else {predecessorParent->right = nullptr;}
		}
		else {
			if(predecessorParent->left == predecessor){predecessorParent->left = predecessor->right;}
			else{predecessorParent->right = predecessor->right;}
		}
		free(predecessor);
		return;
	}

	//Case 3
	Node *child = (curr->left)? curr->left: curr->right;
	if(curr == root) {root = child; free(curr);}
	else if(parent->left == curr) {parent->left = child; free(curr);}
	else {parent->right = child; free(curr);}

	return;
}

bool isBST(Node *root,int min,int max){
	if(root == NULL) return true;

	if(root->data > max || root->data < min) {return false;}

	return isBST(root->left,min,root->data-1) && isBST(root->right,root->data+1,max);
}

Node *create(Node* root,int k){
	if(root == nullptr) {root = new Node(k); return root;}
	Node *p = root,*q = root;
	while(q!=NULL){
		if(q->data > k) {p = q; q = q->left;}
		else {p = q; q = q->right;}
	}

	if(p->data > k) {p->left = new Node(k);}
	else {p->right = new Node(k);}

	return root;
}

void postOrder(Node *p){
	if(p){
		postOrder(p->left); postOrder(p->right); cout<<p->data<<" ";
	}
}

Node *createNode(Node *root, vector<string> v, int n){
	queue<Node *> q;
	int i = 0; Node *p;

	while(i<n){
		p = (v[i] == "null") ? new Node(INT_MIN): new Node(stoi(v[i]));
		if(root == NULL) {root = p;}
		else if(q.front()->left == NULL) {q.front()->left = p;}
		else {q.front()->right = p; q.pop();}
		if(p->data != INT_MIN){q.push(p);} i++;
	}
	stack<Node *> s;
	s.push(root); Node *vacate;

	while(!s.empty()){
		p = s.top(); s.pop(); 
		if(p->left) {
			if(p->left->data == INT_MIN){
				vacate = p->left;
				p->left = nullptr; free(vacate);
			}else{
				s.push(p->left);
			}
		}
		if(p->right){
			if(p->right->data == INT_MIN){
				vacate = p->right;
				p->right = nullptr; free(vacate);
			}else{
				s.push(p->right);
			}
		}
	}
	return root;
}

int previous = -1,number = 0, Max = 0, Mode = 0;

void mode(Node *root){
	if(root){
		mode(root->left);

		if(previous != -1){
			if(previous == root->data){
				number++;
			}
			else{
				number = 1;
			}
		}

		if(number > Max){
			Max = number;
			Mode = root->data;
		}

		prev = root->data;

		mode(root->right);
	}
}

void preOrder(Node *root){
	if(root){
		cout<<root->data<<" ";
		preOrder(root->left);
		preOrder(root->right);
	}
	return;
}

Node *searchNode(Node *root, Node * &parent, int key){
	if(root == NULL) {return nullptr;}

	while(root!=NULL){
		if(root->data == key){return root;}
		else if(root->data > key){parent = root; root = root->left;}
		else {parent = root; root = root->right;}
	}
	return root;
}

void deleteNode(Node * &root, int key){
	if(root == NULL) {return;}

	if(root->data > key) {
		deleteNode(root->left, key);
	}
	else if(root->data < key){
		deleteNode(root->right, key);
	}

	else {
		if(root->right == NULL && root->left == NULL){
			delete root;
			root = NULL;
		}
		else if(root->left && root->right){
			Node *predecessor = root->left;
			while(predecessor->right != NULL){
				predecessor = predecessor->right;
			}
			root->data = predecessor->data;
			deleteNode(predecessor,key);
		}
	}
}

int find_pos(vector<int> preorder,int key,int start,int end){
	for(int i=start;i<=end;i++){
		if(preorder[i]>key){return i-1;}
	}
	return preorder.size()-1;
}

Node *tree_preorder(vector<int> preorder,int start, int end){	
	if(start > end) return NULL;

	Node *curr = new Node(preorder[start]);

	if(start == end) return curr;

	int pos = find_pos(preorder,curr->data,start+1,end);

	curr->left = tree_preorder(preorder,start+1, pos);
	curr->right = tree_preorder(preorder,pos+1,end);

	return curr;
}

int main(){
	// ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int T; cin>>T;
	// for(int tc = 1; tc <= T; tc++){
	// 	// cout << "Case #" << tc <<": ";
	// 	solve();
	// }
	// Node *root = nullptr; int deleteNode; cin>>deleteNode;
	// vector<string> v; string k;
	// while(cin>>k) v.push_back(k);
	// root = createNode(root,v,v.size());
	// Delete(root,deleteNode);
	// postOrder(root);

	vector<int> preorder; int k;
	while(cin>>k){
		preorder.push_back(k);
	}

	Node *root = tree_preorder(preorder,0,preorder.size()-1);

	postOrder(root);
}
