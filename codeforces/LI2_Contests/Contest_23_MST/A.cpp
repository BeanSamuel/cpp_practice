/*
Question: A. Spanning Tree
Link: https://codeforces.com/group/jtU6D2hVEi/contest/533286/problem/A
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
#define pll pair<ll, ll>

void solve(){
    int n; cin>>n;
    vec<pll> v(n);
    for(auto &i:v) cin>>i.F>>i.S;

    vec<double> dist(n, MXN);
    vec<bool> visited(n, false); 
    dist[0] = 0;
    double ans = 0;

    for(int i=0;i<n;i++) {
        int u = -1;
        for(int j=0;j<n;j++) {
            if(!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = true;
        ans += dist[u];
        for(int j = 0;j<n;j++) {
            if(!visited[j]) {
                double w = sqrt( POW(abs(v[j].F-v[u].F),2) + POW(abs(v[j].S-v[u].S),2) );
                dist[j] = min(dist[j], w);
            }
        }
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
}

signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}