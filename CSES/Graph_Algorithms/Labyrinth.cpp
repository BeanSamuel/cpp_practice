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

char dir[4] = {'R','D','L','U'};

void solve(){
    int n, m; cin>>n>>m;
    vec<string> v(n);
    pii start, end;
    for(int i=0;i<n;i++) {
        cin>>v[i];
        for(int j=0;j<m;j++) {
            if(v[i][j]=='A') start={i,j}; 
            else if(v[i][j]=='B') end={i,j}; 
        }
    }
    vec<vec<pii>> last(n, vec<pii>(m, {-1,-1}));
    bool chk = true;
    queue<pii> q;
    q.push(start);
    while(!q.empty()) {
        auto now = q.front();
        q.pop();
        if(now==end) {
            chk = false;
            break;
        }
        for(int i=0;i<4;i++) {
            int nxtx = now.F+xx[i], nxty = now.S+yy[i];
            if(0<=nxtx and nxtx<n and 0<=nxty and nxty<m and (v[nxtx][nxty]=='.' or v[nxtx][nxty]=='B')) {
                v[nxtx][nxty] = dir[i];
                last[nxtx][nxty] = now;
                q.push({nxtx,nxty});
            }
        }
    }
    if(chk) {
        cout<<"NO"<<endl;
        return;
    }
    string ans = "";
    while(end!=start) {
        ans += v[end.F][end.S];
        end = last[end.F][end.S];
    }
    reverse(ALL(ans));
    cout<<"YES"<<endl<<ans.length()<<endl<<ans<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}