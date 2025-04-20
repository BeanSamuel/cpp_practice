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

int MOD =  998244353;
const double PI = 3.14159265358;
const double EPS = 1e-9;
const int xx[8] = {0,1,0,-1,1,1,-1,-1}; const int yy[8] = {1,0,-1,0,1,-1,-1,1};

void pmod(ll &a, ll b) {a = (a+b)%MOD;}
ll mmod(int a, int b) {return (a-b+MOD)%MOD;} 
void tmod(ll &a, ll b) {a = (a*b)%MOD;}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b);}
ll POW(ll a, ll b) {ll res=1; do{if(b%2)tmod(res,a);tmod(a,a);}while(b>>=1); return res;}

const int MXN = 1e8; const int N = MXN + 10;
#define pii pair<int,int>

using namespace std;

template <class T>
struct BIT {
    int n;
    vector<T> a;
    BIT(int _n) : n(_n), a(_n) {}
    int lowbit(int x) { return x & -x; }
    void add(int p, T x) {
        for (int i = p + 1; i <= n; i += lowbit(i)){
            pmod(a[i-1],x);
        }
            
    }
    T qry(int p) {
        T r{};
        for (int i = p + 1; i > 0; i -= lowbit(i)){
            pmod(r,a[i - 1]);
        }
        return r;
    }
    T qry(int l, int r) { // [l, r)
        return mmod(qry(r - 1),qry(l - 1));
    }
};

void solve(){
    ll x, m; cin >> x >> m >> MOD;
    map<ll,ll> mp;
    mp[m] = 1; mp[m+1] = 1;
    vector<pii> route(x);
    for(int i=0;i<x;i++) {
        cin>>route[i].S;
        mp[route[i].S] = 1;
    }
    for(int i=0;i<x;i++){
        cin>>route[i].F;
        mp[route[i].F] = 1;
    }
    sort(ALL(route));
    int cnt = 1;
    for(auto &i:mp) i.S = cnt++;
    BIT<ll> dp(cnt+5);
    dp.add(mp[0],1);
    for(auto [end,start] : route){
        dp.add(mp[end],dp.qry(mp[start],mp[end]));
    }
    cout<<dp.qry(mp[m],mp[m+1])%MOD<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}