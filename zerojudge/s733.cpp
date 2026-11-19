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

struct Binary_Indexed_Tree { 
    int n;
    vec<ll> bit;

    static int lowbit(int x) { return x&-x; }

    Binary_Indexed_Tree(const vec<ll> &v) { //O(n)
        n = siz(v)+1;
        bit.resize(n, 0);
        for(int i=1;i<n;i++) {
            bit[i] += v[i-1] - (i > 1 ? v[i-2] : 0);
            int j = i + lowbit(i);
            if(j < n) bit[j] += bit[i];
        }
    }

    void update(int x, ll val) {
        for(; x<n; x+=lowbit(x)) {
            bit[x] += val;
        }
    }

    void range_update(int l, int r, ll val) { //O(logn)
        update(l, val);
        update(r+1, -val);
    }

    ll query(int x) { //O(logn)
        ll ret = 0;
        for(; x>0; x-=lowbit(x)) {
            ret += bit[x];
        }
        return ret;
    }
};

void solve(){
    int n, q; cin>>n>>q;
    vec<ll> v(n);
    for(auto &i: v) cin>>i;
    Binary_Indexed_Tree bit(v);
    while(q--) {
        int op; cin>>op;
        if(op==1) {
            int l, r, x; cin>>l>>r>>x;
            bit.range_update(l, r, x);
        } else {
            int i; cin>>i;
            cout<<bit.query(i)<<endl;
        }
    }
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}