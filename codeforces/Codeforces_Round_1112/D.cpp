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

ll cal(int n, int k, vec<int> &v) {
    bool conflict = false;
    vec<char> nums(n+5, 0);
    int mx  = 0;
    vec<int> left;
    for(int i=0;i<k;i++) {
        if(v[i]>mx) {
            if(nums[v[i]]!=0) conflict = true;
            else nums[v[i]] = 1;
            mx = v[i];
        } else {
            left.EB(v[i]);
        }
    }
    mx = 0;
    vec<int> right;
    for(int i=n-2;i>=k;i--) {
        if(v[i]>mx) {
            if(nums[v[i]]!=0) conflict = true;
            else nums[v[i]] = 1;
            mx = v[i];
        } else {
            right.EB(v[i]);
        }
    }
    if(conflict) return 0;
    vec<int> merge = left;
    merge.insert(merge.end(), ALL(right));
    sort(ALL(merge));

    ll ret = 1, now=1, cnt = 0;
    for(int i=0;i<siz(merge);i++) {
        while(now<merge[i]&&now<=n-1) {
            if(nums[now]==0) cnt++;
            now++;
        }
        ll tmp = cnt - (ll)i;
        if(tmp<=0) {ret = 0; break;}
        tmod(ret, tmp%MOD);
    }
    return ret;
}

void solve() {
    int n; cin>>n;
    vec<int> v(n-1);
    for(auto &i: v) cin>>i;
    int mx = *max_element(ALL(v));
    if(mx != n-1) {
        cout<<0<<endl;
        return;
    }
    
    int p = -1, q = -1;
    for(int i=0;i<n-1;i++) {
        if(v[i]==mx) {
            if(p==-1) p = i;
            q = i;
        }
    }

    bool chk = true;
    for(int i=1;i<=q;i++) {
        if(v[i]<v[i-1]) chk = false;
    }
    for(int i=p+1;i<n-1;i++) {
        if(v[i]>v[i-1]) chk = false;
    }

    if(!chk) {
        cout<<0<<endl;
        return;
    }
    cout<<(cal(n, p, v)+cal(n, q+1, v))%MOD<<endl;
}

int main() {
    fastio;
    int t = 1; cin >> t;
    while (t--) solve();
}