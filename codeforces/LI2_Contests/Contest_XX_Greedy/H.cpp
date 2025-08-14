/*
Question: H. Mountain Climbing
Link: https://codeforces.com/group/jtU6D2hVEi/contest/533371/problem/H
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
    ll n; cin>>n;
    vec<pll> v1,v2;
    for(int i=0;i<n;i++) {
        int a, b; cin>>a>>b;
        if(a<=b) v1.EB(a,b);
        else v2.EB(b,a);
    }
    sort(ALL(v1));
    ll down = 0, time = 0;
    for(auto i:v1) {
        down -= i.F;
        if(down<0) { time -= down; down = 0; }
        time += i.S;
        down += i.S;
    } 
    sort(rall(v2));
    for(auto i:v2) {
        down -= i.S;
        if(down<0) { time -= down; down = 0; }
        time += i.F;
        down += i.F;
    }
    cout<<time<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}