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

void solve(){
    int n, m; cin>>n>>m;
    cin.ignore();
    vec<vec<int>> v(n, vec<int>(m, MXN));
    for(int i=0;i<n;i++) {
        string s; getline(cin, s);
        for(int j=0;j<m;j++) {
            if((s[j]=='#')) v[i][j] = -1;
        }
    }
    queue<pair<int, pii>> q;
    v[1][1] = 0;
    q.push({0, {1,1} });
    while(!q.empty()) {
        pair<int, pii> now = q.front();
        q.pop();
        chmin(v[now.S.F][now.S.S],now.F);
        if(now.S.F==n-2 and now.S.S==m-2) {
            cout<<now.F<<endl;
            return;
        }
        for(int i=0;i<4;i++){
            pii nxt = {now.S.F+xx[i], now.S.S+yy[i]};
            if(0<=nxt.F and  nxt.F<n and 0<=nxt.S and nxt.S<m and v[nxt.F][nxt.S]>now.F+1 ) q.push({now.F+1, nxt});
        }
    }
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}