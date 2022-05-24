#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define display(A) for(auto x : A) cout << x <<" "; cout <<"\n";
#define displayP(A) for(auto x : A) display(x);
#define debug(x) cout << (#x) <<" is " << x <<"\n";
#define endl "\n";

void pairs(){
	ll k; cin>>k;

	vector<int> v1,v2; string s;

	while(cin>>s && s!="-1") {
		if(s!="null"){
			v1.push_back(stoi(s));
		}
	}

	while(cin>>s && s!="-1"){
		if(s!="null"){
			v2.push_back(stoi(s));
		}
	}

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	int ans = 0; ll sum = 0;

	for(int i=0; i<v1.size(); i++){
		ans += v2.size()-(upper_bound(v2.begin(),v2.end(),k-v1[i])-v2.begin()); 
	}
	cout<<ans<<endl;
}

struct Node{
	int data;
	Node *right,*left;

	Node(int val){
		data = val;
		left = right = NULL;
	}
};

Node *create(Node *root, vector<string> v, int n){
	queue<Node *> q;
	Node *p; int i = 0;

	while(i<n){
		p = (v[i]!="null") ? new Node(stoi(v[i])) : new Node(INT_MIN);
		if(root == NULL) {root = p;}
		else if(q.front()->left == NULL) {q.front()->left = p;}
		else {q.front()->right = p; q.pop();}
		if(v[i]!="null"){q.push(p);} i++;
	}

	if(root == NULL) return root;

	stack<Node *> s;
	s.push(root);
	while(!s.empty()){
		p = s.top(); s.pop();
		if(p->left){
			if(p->left->data == INT_MIN){
				p->left = NULL;
			}
			else{
				s.push(p->left);
			}
		}
		if(p->right){
			if(p->right->data == INT_MIN){
				p->right = NULL;
			}
			else{
				s.push(p->right);
			}
		}
	}

	return root;
}

void preorder(Node *root){
	if(root){
		cout<<root->data<<" "; preorder(root->left); preorder(root->right);
	}
}

int val = 0; 

void do_greater(Node * root){
	if(root == NULL) return;

	do_greater(root->right);

	val += root->data;
	root->data = val;

	do_greater(root->left);
}

void greater_sum_tree(){
	Node *root = nullptr;

	vector<string> v; string k;

	while(cin>>k && k!="-1") v.push_back(k);

	root = create(root,v,v.size());

	do_greater(root);

	preorder(root);
}

vector<pair<int,int>> ans; int node;

void inorder(Node *root){
	if(root){
		inorder(root->left);
		ans.push_back({abs(root->data - node),root->data});
		inorder(root->right);
	}
}

bool cmp(pair<int,int> &a,pair<int,int> &b){
	return a.first < b.first;
}

void k_closest_nodes(){
	Node *root = NULL;
	vector<string> v; string s;
	int k; cin>>node>>k;

	while(cin>>s) v.push_back(s);
	root = create(root,v,v.size()); inorder(root);

	sort(ans.begin(),ans.end(),cmp);

	for(int i=0;i<k;i++){
		cout<<ans[i].second<<" ";
	}
	return;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	pairs();	
}
