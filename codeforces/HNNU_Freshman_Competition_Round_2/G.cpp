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
#define pll pair<ll,ll>


using namespace std;

void solve(){
    int n; cin>>n;
    vec<pll> v(n);
    for(auto &i: v) cin>>i.F>>i.S;
    pll l = {v[1].F-v[0].F, v[1].S-v[0].S};
    for(int i=2;i<n;i++) {
        pll a = l, b = {v[i].F-v[0].F, v[i].S-v[0].S};
        ll chk = a.F*b.S - a.S*b.F;
        if(chk == 0) continue;
        if(a.F*b.F + a.S*b.S>0) {
            cout<<2<<" "<<1<<" "<<i+1<<endl;
            return;
        }
        a = {v[0].F-v[1].F, v[0].S-v[1].S};
        b = {v[i].F-v[1].F, v[i].S-v[1].S};
        chk = a.F*b.F + a.S*b.S;
        if(chk>0) {
            cout<<1<<" "<<2<<" "<<i+1<<endl;
        } else {
            cout<<1<<" "<<i+1<<" "<<2<<endl;
        }
        return;
    }
    cout<<-1<<endl;
    return;
}


signed main(){
    fastio;
	int t=1; cin>>t;
	while(t--) solve();
}