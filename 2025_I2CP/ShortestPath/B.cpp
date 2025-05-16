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

const ll MXN = 1e18; const ll N = MXN + 10;
#define pii pair<int,int>

void solve(){
    int n, m; cin>>n>>m;
    vec<tuple<int,int,ll>> edges;
    vec<ll> dis(n+1,MXN);
    dis[n] = 0;
    for(int i=0;i<m;i++) {
        int u, v; ll w; cin>>u>>v>>w;
        edges.EB(v,u,-w);
    }
    int times = n-1;
    while(times--) {
        for(auto [u,v,w]: edges) {
            if(dis[u] != MXN && dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
            }
        }
    }
    for(auto [u,v,w]: edges) {
        if(dis[u] != MXN && dis[u] + w < dis[v]) {
            cout<<"inf"<<endl;
            return;
        }
    }
    cout<<-dis[1]<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}