/*
Question: 血緣關係
Link: https://zerojudge.tw/ShowProblem?problemid=b967
*/

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

pii dfs(vec<vec<int>> &g, int node, int pre, int depth) {
    pii ret = {node, depth};
    for(auto i: g[node]) {
        if(pre != i) {
            pii tmp = dfs(g, i, node, depth+1);
            if(tmp.S > ret.S) ret = tmp;
        }
    }
    return ret;
}


void solve(){
    int n; cin>>n;
    vec<vec<int>> g(n);
    for(int i=1;i<n;++i){
        int u, v; cin>>u>>v;
        g[u].EB(v);
        g[v].EB(u);
    }
    auto [start, depth] = dfs(g, 0, -1, 0);
    auto [_, ans] = dfs(g, start, -1, 0);
    cout<<ans<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}
