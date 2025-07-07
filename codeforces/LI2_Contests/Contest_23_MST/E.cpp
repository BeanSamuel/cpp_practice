/*
Question: E. Oil Business
Link: https://codeforces.com/group/jtU6D2hVEi/contest/533286/problem/E
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


class DSU {
    public:
        vec<ll> f, sz;
        ll n;
        bool full = false;
        DSU(ll _n) {
            n = _n;
            f.resize(n+1);
            sz.resize(n+1, 1);
            for(ll i=0;i<=n;i++) f[i] = i;
        }
        ll find(ll x) {
            if(f[x] == x) return x;
            f[x] = find(f[x]);
            return f[x];
        }
        void merge(ll x, ll y) {
            x = find(x);
            y = find(y);
            if(x == y) return;
            if(sz[x]<sz[y]) swap(x,y);
            sz[x] += sz[y];
            if(sz[x] == n) full = true;
            f[y] = x;
        }
};

void solve(){
    ll n, m, s; cin>>n>>m>>s;
    DSU dsu(n);
    vec<tuple<ll,ll,ll,ll>> edges;
    for(ll i=1;i<=m;i++) {
        ll u, v, w; cin>>u>>v>>w;
        edges.EB(w,u,v,i);
    }
    sort(ALL(edges), greater<tuple<ll,ll,ll,ll>>());
    vec<tuple<ll,ll,ll,ll>> v2;
    for(auto [w,u,v,id]: edges) {
        if(dsu.full||dsu.find(u) == dsu.find(v)) {
            v2.EB(w,u,v,id);
        } else {
            dsu.merge(u,v);
        }
        
    }
    reverse(ALL(v2));
    ll ans = 0, cnt= 0;
    vec<ll> ans2;
    for(auto [w,u,v,id] : v2) {
        if(cnt + w > s ) break;
        cnt += w; 
        ans2.EB(id);
        ans++;
    }
    cout<<ans<<endl;
    for(auto i : ans2) cout<<i<<" ";
    cout<<endl;
}

signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}