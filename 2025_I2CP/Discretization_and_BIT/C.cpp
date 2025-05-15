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

struct Binary_Indexed_Tree { 
    int n;
    vec<ll> bit;

    Binary_Indexed_Tree(int _n) {
        n = _n + 1;
        bit.resize(n, 0);
    }

    int lowbit(int x) {
        return x&-x;
    }

    void update(int x, int val) {
        for(; x<n; x+=lowbit(x)) {
            bit[x] += val;
        }
    }

    ll query(int x) {
        ll ret = 0;
        for(; x>0; x-=lowbit(x)) {
            ret += bit[x];
        }
        return ret;
    }

};

void solve(){
    int n,k; cin>>n>>k;
    vec<int> x(n),y(n);
    for(int i=0;i<n;i++) cin>>x[i]>>y[i];
    vec<int> tmpy(y);
    sort(ALL(tmpy));
    tmpy.erase(unique(ALL(tmpy)),tmpy.end());
    vec<pii> cor(n); 
    for(int i=0;i<n;i++) {
        cor[i].F = x[i];
        cor[i].S = lower_bound(ALL(tmpy), y[i]) - tmpy.begin() + 1;
    }
    sort(ALL(cor));
    Binary_Indexed_Tree BIT(tmpy.size()+1);
    ll ans = 0, idx = 0;
    for(auto [f,s]:cor) {
        BIT.update(s+1,1);
        int dom = BIT.query(s);
        if(abs( n-dom*2 -1 ) >= k) ans++;
    }   
    
    cout<<ans<<endl;
}


signed main(){
    fastio;
	int t=1; cin>>t;
	while(t--) solve();
}