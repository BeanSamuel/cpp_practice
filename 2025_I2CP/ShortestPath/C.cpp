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

const ll MXN = 1e17; const ll N = MXN + 10;
#define pii pair<int,int>

void solve(){
    int n, m, q; cin>>n>>m>>q;
    vec<vec<ll>> dp(n+1, vec<ll>(n+1, MXN));
    for(int i=0;i<m;i++) {
        ll u,v,w; cin>>u>>v>>w;
        chmin(dp[u][v], w);
        chmin(dp[v][u], w);
    }
    for(int i=1;i<=n;i++) dp[i][i] = 0;
    for(int k=1;k<=n;k++) {
        for(int u=1;u<=n;u++) {
            for(int v=1;v<=n;v++) {
                dp[u][v] = min(dp[u][v], dp[u][k] + dp[k][v]);
            }
        }
    }
    while(q--) {
        int u, v; cin>>u>>v;
        cout<<(dp[u][v]<MXN?dp[u][v]:-1)<<endl;
    }
}



signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}