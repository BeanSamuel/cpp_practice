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

const int MOD =  1000000007;
const double PI = 3.14159265358979323846;
const double EPS = 1e-9;
const int xx[8] = {0,1,0,-1,1,1,-1,-1};
const int yy[8] = {1,0,-1,0,1,-1,-1,1};

void pmod(ll &a, ll b) { a = ((a + b) % MOD + MOD) % MOD; }
void mmod(ll &a, ll b) { a = ((a - b) % MOD + MOD) % MOD; }
void tmod(ll &a, ll b) { a = (a * b) % MOD; }
ll POW(ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define pii pair<int,int>
#define pll pair<ll, ll>

#ifdef LOCAL
template<class T, class = void>
struct is_container : false_type {};
template<class T>
struct is_container<T, void_t<decltype(begin(declval<T>()))>> : true_type {};

template<class A, class B>
ostream& operator<<(ostream& os, const pair<A,B>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template<class T, enable_if_t<is_container<T>::value && !is_same<T, string>::value, int> = 0>
ostream& operator<<(ostream& os, const T& v) {
    os << "{";
    bool first = true;
    for (auto& x : v) {
        if (!first) os << ", ";
        os << x;
        first = false;
    }
    return os << "}";
}

template<class... T> void dbg(T...x) {
    char e{};
    ((cerr << e << x, e = ' '), ...);
}
#define debug(...) dbg(#__VA_ARGS__, '=', __VA_ARGS__, '\n')
#else
#define debug(...) ((void)0)
#endif

void solve(){
    int r, c, n; cin>>r>>c>>n;
    vec<vec<char>> v(r, vec<char>(c, '*'));
    vec<vec<char>> ans(r, vec<char>(c, '*'));
    while(n--) {
        int x, y, d; string w; cin>>x>>y>>d>>w;
        x--; y--;
        int len = siz(w);
        if(d&1) {
            if(!(0<=x&&x+len-1<r&&0<=y&&y<c)) continue;
            bool chk = false;
            for(int i=x;i<x+len;i++) {
                if(v[i][y]!='*'&&v[i][y]!=w[i-x]) chk = true;
            }
            if(chk) continue;
            for(int i=x;i<x+len;i++) v[i][y] = w[i-x];
            for(int i=x;i<x+len;i++) {
                if(i==x) ans[i][y] = w.front();
                else if(i==x+len-1) ans[i][y] = w.back();
                else if(ans[i][y]=='*') ans[i][y] = '_';
            }
        } else {
            if(!(0<=y&&y+len-1<c&&0<=x&&x<r)) continue;
            bool chk = false;
            for(int i=y;i<y+len;i++) {
                if(v[x][i]!='*'&&v[x][i]!=w[i-y]) chk = true;
            }
            if(chk) continue;
            for(int i=y;i<y+len;i++) v[x][i] = w[i-y];
            for(int i=y;i<y+len;i++) {
                if(i==y) ans[x][i] = w.front();
                else if(i==y+len-1) ans[x][i] = w.back();
                else if(ans[x][i]=='*') ans[x][i] = '_';
            }
        }
    }
    for(auto &i: ans) {
        for(auto &j: i) cout<<j;
        cout<<endl;
    }
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}