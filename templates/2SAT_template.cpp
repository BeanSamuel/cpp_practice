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


struct TwoSat {
    int n;
    vec<vec<int>> G;
    vec<bool> ans;
    vec<int> id, dfn, low, stk;
    TwoSat(int n) : n(n), G(2*n), ans(n), id(2*n,-1), dfn(2*n,-1), low(2*n,-1) {}
    void addClause(int u, bool f, int v, bool g) {
        G[2*u + !f].PB(2*v+g);
        G[2*v + !g].PB(2*u+f);
    }
    void addImply(int u, bool f, int v, bool g) {
        G[2*u + f].PB(2*v+g);
        G[2*v + !g].PB(2*u+!f);
    }
    int cur = 0, scc = 0;
    void dfs(int u) {
        stk.PB(u);
        dfn[u] = low[u] = cur++;
        for(int v: G[u]) {
            if(dfn[v] == -1) {
                dfs(v);
                chmin(low[u], low[v]);
            } else if(id[v]==-1){
                chmin(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u]) {
            int x;
            do {
                x = stk.back();
                stk.pop_back();
                id[x] = scc;
            } while ( x!= u );
            scc++;
        }
    }
    bool satisfiable() {
        for(int i=0;i<n*2;i++) {
            if(dfn[i] == -1) {
                dfs(i);
            }
        }
        for(int i=0;i<n;i++) {
            if(id[2*i] == id[2*i + 1]) {
                return false;
            }
            ans[i] = id[2*i] > id[2*i+1];
        }
        return true;
    }
};