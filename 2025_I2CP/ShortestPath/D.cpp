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
    int n, m; cin>>n>>m;
    vec<tuple<int,ll,int>> graph[n+1];
    for(int i=1;i<=m;i++) {
        int u, v; ll w; cin>>u>>v>>w;
        graph[u].EB(v,w,i);
        graph[v].EB(u,w,i);
    }
    vec<ll> dis(n+1, MXN); 
    vec<int> from(n+1, -1);
    priority_queue<tuple<ll,int,int>, vec<tuple<ll,int,int>>, greater<tuple<ll,int,int>>> pq;
    pq.emplace(0,1,-1);
    while(!pq.empty()) {
        auto [now, u, idx] = pq.top(); pq.pop();
        if(now >= dis[u]) continue;
        dis[u] = now;
        from[u] = idx;
        for(auto [v,w,i]: graph[u]) {
            if(dis[u] + w < dis[v]) {
                pq.emplace(dis[u] + w, v, i);
            }
        }
    }
    from.erase(unique(ALL(from)), from.end());
    for(int i:from)  if(i!=-1) cout<<i<<" ";
    cout<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}