/*
Question: D. Greatest Common Divisor
Link: https://codeforces.com/group/jtU6D2hVEi/contest/104997/problem/D
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

void solve(){
    ll n; cin>>n;
    vec<ll> v(n), v1, v2;
    for(auto &i:v) cin>>i;
    v1.EB(v[0]);
    v2.EB(v[n-1]);
    for(int i=1;i<n;i++) {
        v1.EB(gcd(v[i], v1[i-1]));
    }
    for(int i=n-2;i>=0;i--) {
        v2.EB(gcd(v[i], v2.back()));
    }
    reverse(ALL(v2));
    ll ans = 0;
    for(int i=1;i<n-1;i++) {
        ans = max(ans, (1LL)*gcd(v1[i-1] ,v2[i+1]));
    }
    ans = max(ans, v1[n-2]);
    ans = max(ans, v2[1]);
    cout<<ans<<endl;
}

signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}