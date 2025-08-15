/*
Question: S. Mental Pressure in Mirny
Link: https://codeforces.com/group/jtU6D2hVEi/contest/104934/problem/S
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

const int MXN = 1e9; const int N = MXN + 10;
#define pii pair<int,int>
#define pll pair<ll, ll>

void solve(){
    int n; cin>>n;
    vec<pll> v1(n), v2(n);
    for(int i=0;i<n;i++) {
        cin>>v1[i].F>>v2[i].F;
        v1[i].S=v2[i].S=i;
    }
    sort(rall(v1));
    sort(rall(v2));
    if(v1.front().S == v2.front().S) {
        cout<<max(v1[1].F+v2[0].F, v1[0].F+v2[1].F)<<endl;
    } else {
        cout<<v1.front().F+v2.front().F<<endl;
    }
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}