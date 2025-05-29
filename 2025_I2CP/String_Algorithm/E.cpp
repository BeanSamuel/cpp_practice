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

const int MXN = 1e9+5; const int N = MXN + 10;
#define pii pair<int,int>

int kmp_times(vec<int> &s, vec<int> &p) { // find p in s 
    int n = siz(s), m = siz(p);
    vec<int> f(m, -1);
    for(int i = 1; i < m; i++) {
        int j = f[i-1];
        while(j != -1 && p[i] != p[j+1]) j = f[j];
        if(p[j+1] == p[i]) f[i] = j+1;
        else f[i] = -1;
    }
    int ret = 0, cur = -1;
    for(int i = 0; i < n; i++) {
        while(cur != -1 && s[i] != p[cur+1]) cur = f[cur];
        if(s[i] == p[cur+1]) cur++;
        if(cur == m-1) {
            ret++;
            cur = f[cur];
        }
    }
    return ret;
}

void solve(){
    int n, m; cin>>n>>m;
    vec<int> v1(n), v11;
    for(auto &i: v1) cin>>i;
    for(int i=1;i<n;i++) v11.EB(v1[i]-v1[i-1]);
    vec<int> v2(m), v22;
    for(auto &i: v2) cin>>i;
    for(int i=1;i<m;i++) v22.EB(v2[i]-v2[i-1]);
    if(m==1) {
        cout<<n<<endl;
        return;
    }
    cout<<kmp_times(v11,v22)<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}