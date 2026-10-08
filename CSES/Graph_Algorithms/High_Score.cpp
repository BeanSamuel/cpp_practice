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

void solve() {
    int n, m; cin>>n>>m;
    vec<pair<pii,ll>> edges(m);
    vec<vec<int>> g(n+1);
    for(int i=0;i<m;i++) {
        int u, v; ll w; cin>>u>>v>>w;
        edges.EB(make_pair(make_pair(u,v),-w));
        g[u].EB(v);
    }
    vec<ll> dist(n+1, inf<ll>);
    dist[1] = 0;
    for(int i=0;i<n-1;i++) {
        char chk = 1;
        for(auto [edge, w]: edges) {
            if(dist[edge.F]!=inf<ll>&&dist[edge.F]+w<dist[edge.S]) {
                dist[edge.S] = dist[edge.F]+w;
                chk = 0;
            }
        }
        if(chk) break;
    }
    vec<char> record(n+1, 0);
    queue<int> q;
    for(auto [edge, w]: edges) {
        if(dist[edge.F]!=inf<ll>&&dist[edge.F]+w<dist[edge.S]) {
            q.push(edge.S);
            record[edge.S] = 1;
        }
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto v: g[u]) {
            if(record[v]) continue;
            record[v] = 1;
            q.push(v);
        }
    }
    cout<<(record[n]?-1:-dist[n])<<endl;
}

int main() {
    fastio;
    int t = 1; //cin >> t;
    while (t--) solve();
}