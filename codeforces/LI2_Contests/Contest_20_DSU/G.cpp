/*
Question: G. Restructuring Company
Link: https://codeforces.com/group/jtU6D2hVEi/contest/533282/problem/G
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
        vec<int> f, sz, nxt;
        DSU(int n) {
            f.resize(n+1);
            sz.resize(n+1, 1);
            nxt.resize(n+1);
            for(int i=0;i<=n;i++) f[i] = i;
            for(int i=0;i<=n;i++) nxt[i] = i+1;
        }
        int find(int x) {
            if(f[x] == x) return x;
            f[x] = find(f[x]);
            return f[x];
        }
        void merge(int x, int y) {
            x = find(x);
            y = find(y);
            if(x == y) return;
            if(sz[x]<sz[y]) swap(x,y);
            sz[x] += sz[y];
            f[y] = x;
        }
};

void solve(){
    int n, q; cin>>n>>q;
    DSU dsu(n);
    while(q--) {
        int cmd; cin>>cmd;
        if(cmd == 1) {
            int x, y; cin>>x>>y;
            dsu.merge(x,y);
        } else if(cmd == 2) {
            int x, y; cin>>x>>y;
            int now = x;
            while(now <= y) {
                dsu.merge(x, now);
                int tmp = dsu.nxt[now];
                dsu.nxt[now] = max(dsu.nxt[now], y+1);
                now = tmp;
            }
        } else if(cmd == 3) {
            int x, y; cin>>x>>y;
            if(dsu.find(x) == dsu.find(y)) {
                cout<<"YES"<<endl;
            } else {
                cout<<"NO"<<endl;
            }
        }
    }
}
 
signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}