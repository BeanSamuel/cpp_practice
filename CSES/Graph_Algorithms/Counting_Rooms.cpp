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
        vec<vec<pii>> f;
        vec<vec<int>> sz;
        DSU(int n, int m) {
            f.resize(n+1, vec<pii>(m+1));
            sz.resize(n+1, vec<int>(m+1, 1));
            for(int i=0;i<=n;i++) {
                for(int j=0;j<=m;j++) {
                    f[i][j] = {i,j};
                }
            }
        }
        pii find(pii x) {
            if(f[x.F][x.S] == x) return x;
            f[x.F][x.S] = find(f[x.F][x.S]);
            return f[x.F][x.S];
        }
        void merge(pii x, pii y) {
            x = find(x);
            y = find(y);
            if(x == y) return;
            if(sz[x.F][x.S]<sz[y.F][y.S]) swap(x,y);
            sz[x.F][x.S] += sz[y.F][y.S];
            f[y.F][y.S] = x;
        }
};

void solve(){
    int n, m; cin>>n>>m;
    DSU dsu(n,m);
    vec<vec<char>> v(n+1, vec<char>(m+1));
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            cin>>v[i][j];
        }
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if(v[i][j] == '.') {
                for(int k=0;k<4;k++){
                    if(1<=i+xx[k] && i+xx[k]<=n && 1<=j+yy[k] && j+yy[k]<=m && v[i+xx[k]][j+yy[k]]=='.') {
                        dsu.merge({i,j},{i+xx[k],j+yy[k]});
                    }
                }
            }
        }
    }
    set<pii> s;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if(v[i][j]=='.') s.insert(dsu.find({i,j}));
        }
    }
    cout<<s.size()<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}