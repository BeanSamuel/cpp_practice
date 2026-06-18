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

const ll MXN = 1e15; const ll N = MXN + 10;
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
    vec<vec<char>> v(n+2, vec<char>(m+2));
    pii b, g;
    for(int i=0;i<n+2;i++) {
        for(int j=0;j<m+2;j++) {
            cin>>v[i][j];
            if(v[i][j] == 'B') b = make_pair(i,j);
            else if(v[i][j] == 'G') g = make_pair(i,j);
        }
    }
    int bdir, gdir;
    if(b.S==0) bdir = 0; //right    
    else if(b.F==0) bdir = 1; //down
    else if(b.S==n+1) bdir = 2; //left 
    else bdir = 3; //up

    if(g.S==0) gdir = 0; //right    
    else if(g.F==0) gdir = 1; //down
    else if(g.S==n+1) gdir = 2; //left
    else gdir = 3; //up

    vec<vec<char>> bmap(n+2, vec<char>(m+2,'.'));
    b.F += xx[bdir];
    b.S += yy[bdir];
    while(0<b.F&&b.F<n+1&&0<b.S&&b.S<m+1) {
        bmap[b.F][b.S] = 'B';
        if(v[b.F][b.S]=='/') {
            if(bdir==0) bdir = 3;
            else if(bdir==1) bdir = 2;
            else if(bdir== 2) bdir = 1;
            else bdir = 0;
        } else if(v[b.F][b.S]=='\\') {
            if(bdir==0) bdir = 1;
            else if(bdir==1) bdir = 0;
            else if(bdir== 2) bdir = 3;
            else bdir = 2;
        }
        b.F += xx[bdir];
        b.S += yy[bdir];
    }

    vec<vec<char>> gmap(n+2, vec<char>(m+2,'.'));
    g.F += xx[gdir];
    g.S += yy[gdir];
    while(0<g.F&&g.F<n+1&&0<g.S&&g.S<m+1) {
        gmap[g.F][g.S] = 'G';
        if(v[g.F][g.S]=='/') {
            if(gdir==0) gdir = 3;
            else if(gdir==1) gdir = 2;
            else if(gdir== 2) gdir = 1;
            else gdir = 0;
        } else if(v[g.F][g.S]=='\\') {
            if(gdir==0) gdir = 1;
            else if(gdir==1) gdir = 0;
            else if(gdir== 2) gdir = 3;
            else gdir = 2;
        }
        g.F += xx[gdir];
        g.S += yy[gdir];
    }

    for(int i=1;i<n+1;i++) {
        for(int j=1;j<n+1;j++) {
            if(bmap[i][j]=='B'&&gmap[i][j]=='G') {
                cout<<"W";
            } else if(bmap[i][j]=='B') {
                cout<<"B";
            } else if(gmap[i][j]=='G') {
                cout<<"G";
            } else {
                cout<<'.';
            }
        }
        cout<<endl;
    }

}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}