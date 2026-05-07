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
#define rall(x) x.rbegin(),x.rend()

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
#define pll pair<ll, ll>

#ifdef LOCAL
template<class... T> void dbg(T...x) {
    char e{};
    ((cerr << e << x, e = ' '),...);
}
#define debug(x...) dbg(#x, '=',x,'\n')
#else 
#define debug(...) ((void)0)
#endif

void dfs(vec<vec<int>> &g, vec<ll> &score, vec<ll> &sub, int now, int parent, ll depth) {
    sub[now] = 1LL;
    for (int nxt:g[now]) {
        if (nxt==parent) continue;
        dfs(g, score, sub, nxt, now, depth+1LL);
        sub[now]+=sub[nxt];
    }

    score[now]=depth-(sub[now]-1LL);
}

void solve(){
    int n, k; cin>>n>>k;
    vec<vec<int>> g(n+1);
    for(int i=0;i<n-1;i++) {
        int u, v; cin>>u>>v;
        g[u].EB(v);
        g[v].EB(u);
    }
    vec<ll> subtree(n+1), score(n+1);
    dfs(g, score, subtree, 1LL, -1LL, 0);
    score[0] = -MXN;
    sort(rall(score));
    ll ans = 0;
    for (int i = 0; i < k; i++) ans += score[i];
    cout<<ans<<endl;
}

signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}