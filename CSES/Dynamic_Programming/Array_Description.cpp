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

const int MOD =  1000000007;
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

using namespace std;

void solve(){
    int n, m; cin>>n>>m;
    vec<int> v(n);
    for(int &num:v) cin>>num;
    vec<vec<ll>> dp(n, vec<ll>(m+1,0));
    if( v[0]==0 ) {
        for(auto &i:dp[0]) i = 1; 
    } else {
        dp[0][v[0]] = 1;
    }
    for(int i=1;i<n;i++) {
        if(v[i] == 0) {
            for(int j=1;j<=m;j++) {
                if( j-1 > 0) pmod(dp[i][j], dp[i-1][j-1]);
                pmod(dp[i][j], dp[i-1][j]);
                if( j+1 <= m) pmod(dp[i][j], dp[i-1][j+1]);
            }
        } else {
            if(v[i]-1 > 0) pmod(dp[i][v[i]], dp[i-1][v[i]-1]);
            pmod(dp[i][v[i]], dp[i-1][v[i]]);
            if(v[i]+1 <= m) pmod(dp[i][v[i]], dp[i-1][v[i]+1]);
        }
    }
    ll ans = 0;
    for(int i=1;i<=m;i++) {
        pmod(ans, dp[n-1][i]);
    }
    cout<<ans<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}