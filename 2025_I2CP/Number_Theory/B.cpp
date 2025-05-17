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

const int MOD =  1e9+7;
const double PI = 3.14159265358;
const double EPS = 1e-9;
const int xx[8] = {0,1,0,-1,1,1,-1,-1}; const int yy[8] = {1,0,-1,0,1,-1,-1,1};

void pmod(ll &a, ll b) {a = (a+b)%MOD;}
void mmod(ll &a, ll b) {a = (a-b+MOD)%MOD;} 
void tmod(ll &a, ll b) {a = (a*b)%MOD;}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b);}
ll POW(ll a, ll b) {ll res=1; do{if(b%2)tmod(res,a);tmod(a,a);}while(b>>=1); return res;}

const int MXN = 1e6+10; const int N = MXN - 5;
#define pii pair<int,int>

ll fac[MXN], inv[MXN];

void build() {
    fac[0] = 1;
    for(int i=1;i<=N;i++) fac[i] = fac[i-1] * i % MOD;
    inv[N] = POW(fac[N], MOD-2);
    for(int i=N-1;i>=0;i--) inv[i] = inv[i+1] * (i+1) % MOD;
}


void solve(){
    int a, b; cin>>a>>b;
    cout<<fac[a]*inv[b]%MOD*inv[a-b]%MOD<<endl;
}


signed main(){
    fastio;
    build();
	int t=1; cin>>t;
	while(t--) solve();
}