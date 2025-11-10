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

const ll MXN = 1e18; const ll N = MXN + 10;
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
    int n, k; cin>>n>>k;
    vec<int> v(n);
    for(auto &i: v) cin>>i;
    multiset<int> low, high;
    auto balance = [&]() {
        while(siz(low) > siz(high)+1) {
            auto it = prev(low.end());
            high.insert(*it);
            low.erase(it);
        }
        while(siz(low) < siz(high)) {
            auto it = high.begin();
            low.insert(*it);
            high.erase(it);
        }
    } ;
    for(int i=0;i<k;i++) low.insert(v[i]);
    balance();
    cout<<*prev(low.end())<<" ";
    for(int i=k;i<n;i++) {
        auto it = low.find(v[i-k]);
        if(it!=low.end()) low.erase(it);
        else {
            it = high.find(v[i-k]);
            high.erase(it);
        }
        balance();
        if(!low.empty()&&v[i]>*prev(low.end())) high.insert(v[i]);
        else low.insert(v[i]);
        balance();
        cout<<*prev(low.end())<<" ";
    }
    cout<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}