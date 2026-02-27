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
    int n; cin>>n;
    vec<vec<int>> v(n);
    for(int i=0;i<n;i++) {
        int x; cin>>x;
        while(x--) {
            int y; cin>>y;
            v[i].EB(y);
        }
    }
    for(int i=0;i<n;i++) {
        reverse(ALL(v[i])); 
    }
    for(int i=0;i<n;i++) {
        set<int> haha;
        vec<int> haha2;
        for(int j=0;j<siz(v[i]);j++) {
            if(haha.find(v[i][j])==haha.end()) {
                haha2.EB(v[i][j]);
                haha.insert(v[i][j]);
            }
        }
        v[i] = haha2;
    }
    
    set<int> used;
    vec<int> ans;
    vec<int> tmp;
    
    while(!v.empty()) {
        sort(ALL(v));
        tmp = v[0];
        for(int i : v[0]) {
            if(used.find(i) == used.end()) {
                ans.EB(i);
                used.insert(i);
            }
        }
        v.erase(v.begin());
        for(auto &i : v) {
            for(int j : tmp) {
                auto it = find(ALL(i), j);
                if(it!=i.end()) i.erase(it);
            }
        }
    }
    for(int i: ans) cout<<i<<" ";
    cout<<endl;
}


signed main(){
    fastio;
	int t=1; cin>>t;
	while(t--) solve();
}