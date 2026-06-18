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
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

void solve(){
    int n, m; cin>>n>>m;
    vec<vec<char>> v(n, vec<char>(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin>>v[i][j];
        }
    }
    vec<vec<int>> R(n, vec<int>(m));
    vec<vec<int>> D(n, vec<int>(m));
    vec<vec<int>> DR(n, vec<int>(m));
    vec<vec<int>> DL(n, vec<int>(m));
    
    for(int i=n-1;i>=0;i--) {
        for(int j=m-1;j>=0;j--) {
            if(v[i][j]!='.') continue;
            R[i][j] = (j+1<m&&v[i][j+1]=='.') ? R[i][j+1]+1 : 0;
            D[i][j] = (i+1<n&&v[i+1][j]=='.') ? D[i+1][j]+1 : 0;
            DR[i][j] = (i+1<n&&j+1<m&&v[i+1][j+1]=='.') ? DR[i+1][j+1]+1 : 0;
        }
        for(int j=0;j<m;j++) {
            if(v[i][j]!='.') continue;
            DL[i][j] = (i+1<n&&0<=j-1&&v[i+1][j-1]=='.') ? DL[i+1][j-1]+1 : 0;            
        }
    }

    ll ans = 0;

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(v[i][j]!='.') continue;
            int mn = min({R[i][j], D[i][j], DR[i][j]});
            for(int k=1;k<=mn;k++) {
                if(R[i+k][j]>=k&&D[i][j+k]>=k&&DL[i][j+k]>=k) ans++;
            }
        }
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(v[i][j]!='.') continue;
            int mn = min(DL[i][j], DR[i][j]);
            for(int k=1;k<=mn;k++) {
                if(i+2*k>=n || j-k<0 || j+k>=m) break;
                if(R[i+k][j-k]>=2*k&&D[i][j]>=2*k&&DR[i+k][j-k]>=k&&DL[i+k][j+k]>=k) ans++;
            }
        }
    }
    cout<<ans<<endl;

}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}