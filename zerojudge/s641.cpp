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

vec<bool> c(50,false), left_diag(50, false), right_diag(50, false);

int backtracking(int n, vec<vec<char>> &v, int layer, int remaining) {
    if(remaining==0) return 1;
    int ret = 0;
    for(int i=0;i<n;i++) {
        if(v[layer][i]!='.'||c[i]||left_diag[layer+i]||right_diag[layer-i+n]) continue;
        c[i] = true;
        left_diag[layer+i] = true;
        right_diag[layer-i+n] = true;
        ret += backtracking(n, v, layer+1, remaining-1);
        c[i] = false;
        left_diag[layer+i] = false;
        right_diag[layer-i+n] = false;
    }
    return ret;
}

void solve() {
    int n; cin>>n;
    vec<vec<char>> v(n, vec<char>(n));
    for(auto &i: v) for(auto &j: i) cin>>j;
    cout<<backtracking(n, v, 0, n)<<endl;
}

//   0 1 2 3
// 0 0 1 2 3
// 1 1 2 3 4
// 2 2 3 4 5
// 3 3 4 5 6

//    0  1  2  3
// 0  0 -1 -2 -3
// 1  1  0 -1 -2
// 2  2  1  0 -1
// 3  3  2  1  0

int main() {
    fastio;
    int t = 1; //cin >> t;
    while (t--) solve();
}