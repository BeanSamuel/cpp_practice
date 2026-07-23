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

bool chk(vec<vec<int>> &v, int diff, int n) {
    queue<pii> q;
    vec<vec<bool>> used(n, vec<bool>(n, false));
    q.push(make_pair(0,0));
    used[0][0] = true;
    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if(x==n-1&&y==n-1) break;
        for(int i=0;i<4;i++) {
            int nx = x+xx[i], ny = y+yy[i];
            if(nx<0||n<=nx||ny<0||n<=ny) continue;
            if(used[nx][ny]) continue;
            if(abs(v[nx][ny]-v[x][y])<=diff) {
                q.push(make_pair(nx, ny));
                used[nx][ny] = true;
            }
        }
    }
    return used[n-1][n-1];
}

void solve() {
    int n; cin>>n;
    vec<vec<int>> v(n, vec<int>(n));
    for(auto &i: v) for(auto &j: i) cin>>j;
    int l=0, r=1000005;
    while(l<r) {
        int mid = l + (r-l)/2;
        if(chk(v, mid, n)) {
            r = mid;
        } else {
            l = mid+1;
        }
    }
    queue<pair<pii, int>> q;
    q.push({{0,0},0});
    vec<vec<bool>> used(n, vec<bool>(n, false));
    used[0][0] = true;
    int ans = 0;
    while(!q.empty()) {
        auto [p, w] = q.front(); q.pop();
        int x = p.F, y = p.S;
        if(x==n-1&&y==n-1) {
            ans = w;
            break;
        }
        for(int i=0;i<4;i++) {
            int nx = x+xx[i], ny = y+yy[i];
            if(nx<0||n<=nx||ny<0||n<=ny) continue;
            if(used[nx][ny]) continue;
            if(abs(v[nx][ny]-v[x][y])<=l) {
                q.push({{nx,ny},w+1});
                used[nx][ny] = true;
            }
        }
    }
    cout<<l<<endl<<ans<<endl;
}

int main() {
    fastio;
    int t = 1; //cin >> t;
    while (t--) solve();
}