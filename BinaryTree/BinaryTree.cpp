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
		data = val; left = NULL; right = NULL;
	}
};

Node *getCreatedNode(Node *root){
	root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->left->right = new Node(5);
	root->right->left = new Node(6);
	root->right->right = new Node(7);

	return root;
}

Node *createNode(Node *root,vector<string> v,int n){
	queue<Node *> q;
	int i = 0; Node *p;
	while(i<n){
		p = (v[i]=="null")?new Node(-1):new Node(stoi(v[i]));

		if(root == NULL){root=p;}
		else if(q.front()->left==NULL){q.front()->left=p;}
		else{q.front()->right=p; q.pop();}
		if(p->data!=-1){q.push(p);} i++;
	}	
	stack<Node *> s;
	s.push(root);
	while(!s.empty()){
		p=s.top(); s.pop();
		if(p->left){if(p->left->data==-1){p->left=NULL;}else{s.push(p->left);}}
		if(p->right){if(p->right->data==-1){p->right=NULL;}else{s.push(p->right);}}
	}
	return root;
}

void print(Node *p){
	if(p){
		print(p->left);
		print(p->right);
		cout<<p->data<<" ";
	}
}

int preIndex = 0;


Node *create(vector<int> &preOrder,unordered_map<int,int> &mp,int start,int end){

	if(start>end) return NULL;

	Node *p = new Node(preOrder[preIndex++]);

	if(start==end) return p;

	p->left = create(preOrder,mp,start,mp[p->data]-1);
	p->right = create(preOrder,mp,mp[p->data]+1,end);

	return p;
}

// int main(){
// 	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
// 	Node *root = NULL;

// 	vector<int> inOrder,preOrder; int k;

// 	while(cin>>k && k!=-1) preOrder.push_back(k);
// 	while(cin>>k && k!=-1) inOrder.push_back(k);

// 	unordered_map<int,int> mp;

// 	for(int i=0;i<inOrder.size();i++) mp[inOrder[i]]=i;

// 	root = create(preOrder,mp,0,inOrder.size()-1);

// 	print(root);

// }


Node *createNode(Node *root,vector<string> v,int n){
	queue<Node *> q;
	int i = 0; Node *p;
	while(i<n){
		p = (v[i]=="null")?new Node(1e7):new Node(stoi(v[i]));

		if(root == NULL){root=p;}
		else if(q.front()->left==NULL){q.front()->left=p;}
		else{q.front()->right=p; q.pop();}
		if(p->data!=1e7){q.push(p);} i++;
	}	
	stack<Node *> s;
	s.push(root);
	while(!s.empty()){
		p=s.top(); s.pop();
		if(p->left){if(p->left->data==1e7){p->left=NULL;}else{s.push(p->left);}}
		if(p->right){if(p->right->data==1e7){p->right=NULL;}else{s.push(p->right);}}
	}
	return root;
}

int ans = INT_MIN;

int maxSum(Node *root){
	if(root == NULL) return 0;

	int leftSum = maxSum(root->left);
	int rightSum = maxSum(root->right);

	ans = max(ans,max(leftSum,rightSum));
	ans = max(ans,max(leftSum,rightSum)+root->data);

	ans = max(leftSum+rightSum+root->data,ans);

	return root->data+max(leftSum,rightSum);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	Node *root = NULL;
	int a = INT_MIN;
	vector<int> l;
	vector<string> v; string k;
	while(cin>>k){
		a = (k=="null")? a:max(a,stoi(k));
		if(k!="null"){l.push_back(stoi(k));}
		v.push_back(k);
	}

	sort(l.begin(),l.end());

	if(l[l.size()-1]<0){cout<<l[l.size()-1]<<endl; return 0;}

	root = createNode(root,v,v.size());
	maxSum(root);

	cout<<ans<<endl;
}
