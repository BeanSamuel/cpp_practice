/*
Question: A. Shortest path
Link: https://codeforces.com/group/jtU6D2hVEi/contest/533284/problem/A
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

const ll MXN = 1e18;
#define pii pair<int,int>

ll dijkstra(int n, vector<pii> graph[], int start, int target){
    vector<ll> distance(n+1, MXN);
    distance[start] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [dist,u] = pq.top();
        pq.pop();
        if (dist > distance[u]) continue;
        for (auto [v,w] : graph[u]) {
            if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                pq.push({distance[v], v}); 
            }
        }
    }
    if(distance[target] == MXN) return -1;
    return distance[target];
}

void solve(){
    int n, s, f; cin>>n>>s>>f;
    vec<pii> g[n+1];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            int input; cin>>input;
            if(input == -1) continue;
            if(i!=j) g[i].EB(j, input);
        }
    }
    cout<<dijkstra(n, g, s, f)<<endl;;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}