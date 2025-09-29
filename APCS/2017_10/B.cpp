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
    int k; cin>>k;
    string s; cin>>s;
    int n = siz(s);
    vec<int> v;
    bool tmp = 'A'<=s[0] and s[0]<='Z';
    int cnt = 1;
    for(int i=1;i<n;i++) {
        if(('A'<=s[i] and s[i]<='Z') == tmp) cnt++;
        else {
            v.EB(cnt);
            tmp = 'A'<=s[i] and s[i]<='Z';
            cnt = 1;
        }
    }
    v.EB(cnt);
    cnt = 0;
    int ans = 0;
    for(int i=0;i<siz(v);i++) {
        if(v[i] == k) cnt++;
        else {
            if(i-cnt-1>=0 and v[i-cnt-1]>k) cnt++;
            if(v[i]>k) cnt++;
            chmax(ans, cnt);
            cnt = 0;
        }
    }
    if(cnt>0) {
        if(v[siz(v) - cnt -1] >k) cnt++;
        chmax(ans, cnt);
    }
    cout<<ans*k<<endl;
}



signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}