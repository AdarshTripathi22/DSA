#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define display(A) for(auto x : A) cout << x <<" "; cout <<"\n";
#define displayP(A) for(auto x : A) display(x);
#define debug(x) cout << (#x) <<" is " << x <<"\n";
#define endl "\n";
#define all(v) v.begin(),v.end()

int dp[10100][10100];

int Knapsack_01(int weight[], int val[], int max_weight, int i){
	// Base Case 
	if(max_weight == 0 || i == 0) {return dp[max_weight][i] = 0;}
	if(dp[max_weight][i+1] != -1) {return dp[max_weight][i+1];}

	//Diagram

	if(weight[i] <= max_weight) {
		return dp[max_weight][i+1] = max( Knapsack_01(weight,val,max_weight-weight[i],i-1)+val[i] , Knapsack_01(weight,val,max_weight,i-1));
	}else{
		return dp[max_weight][i+1] = Knapsack_01(weight,val,max_weight,i-1);
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int T; cin>>T;
	// for(int tc = 1; tc <= T; tc++){
	// 	// cout << "Case #" << tc <<": ";
	// 	solve();
	// }
	int n; cin>>n;
	int weight[n]; int val[n];
	for(int i = 0; i<n; i++) cin>>weight[i];
	for(int i = 0; i<n; i++) cin>>val[i];

	int max_weight; cin>>max_weight;
	memset(dp,-1,sizeof(dp));
	cout<< Knapsack_01(weight,val,max_weight,n-1) <<endl;
}
