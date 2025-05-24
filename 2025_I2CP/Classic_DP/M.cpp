#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define F first
#define S second
#define EB emplace_back	
#define PB push_back
#define siz(v) ((int)v.size())  
#define ALL(x) x.begin(), x.end()

template<typename T> using vec = vector<T>;
template <class T> bool chmin(T &a, T b) { return (b < a and (a = b, true)); }
template <class T> bool chmax(T &a, T b) { return (a < b and (a = b, true)); }
template <class T> inline constexpr T inf = numeric_limits<T>::max() / 2;

const int MOD =  998244353;
const double PI = 3.14159265358;
const double EPS = 1e-9;
const int xx[8] = {0,1,0,-1,1,1,-1,-1}; const int yy[8] = {1,0,-1,0,1,-1,-1,1};

void pmod(ll &a, ll b) {a = (a+b)%MOD;}
void mmod(ll &a, ll b) {a = (a-b+MOD)%MOD;} 
void tmod(ll &a, ll b) {a = (a*b)%MOD;}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b);}
ll POW(ll a, ll b) {ll res=1; do{if(b%2)tmod(res,a);tmod(a,a);}while(b>>=1); return res;}

const int MXN = 1e8; const int N = MXN + 10;
#define pii pair<int,int>

void solve(){
    int n; cin>>n;
    vec<int> v(n);
    for(int &i:v) cin>>i;
    vec<int> dp;
    vec<int> dp_idx;
    vec<int> pre(n,-1);
    for(int i=0;i<n;i++) {
        auto pos = lower_bound(ALL(dp), v[i]) - dp.begin();
        if(pos == dp.size()) {
            dp.EB(v[i]);
            dp_idx.EB(i);
        } else {
            dp[pos] = v[i];
            dp_idx[pos] = i;
        }
        if(pos>0) pre[i] = dp_idx[pos-1];
    }
    vec<int> ans(dp.size());
    int idx = dp_idx.back();
    for(int i=dp.size()-1;i>=0;i--) {
        ans[i] = idx;
        idx = pre[idx];
    }

    cout<<ans.size()<<endl;
    for(int i:ans) cout<<i<<" ";
    cout<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}