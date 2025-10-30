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

void solve(){
    int n, m; cin>>n>>m;
    vec<int> g[100005];
    vec<bool> vis(100005, false);
    vec<int> parent(100005, -1);
    for(int i=0;i<m;i++) {
        int u, v; cin>>u>>v;
        g[u].EB(v);
        g[v].EB(u);
    }
    vec<int> ans;
    auto dfs = [&] (auto self, int now, int last) -> bool {
        vis[now] = 1;
        for(auto v: g[now]) {
            if(v==last) continue;
            if(!vis[v]) {
                parent[v] = now;
                if(self(self, v, now)) return true;
            } else {
                int x = now;
                ans.EB(v);
                while(x != v) {
                    ans.EB(x);
                    x = parent[x];
                }
                ans.EB(v);
                reverse(ALL(ans));
                return true;
            }
        }
        return false;
    };

    for(int i=1;i<=n;i++) {
        if(!vis[i]) {
            parent[i] = -1;
            if(dfs(dfs, i, -1)) {
                cout<<siz(ans)<<endl;
                for(auto x : ans) cout<<x<<" ";
                cout<<endl;
                return;
            }
        }
    }
    cout<<"IMPOSSIBLE"<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}