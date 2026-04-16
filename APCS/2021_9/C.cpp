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

auto & operator >>( auto & s , auto & v ) { for ( auto && x : v ) s >> x ; return s; }
auto & operator <<( auto & s , auto v ) { for ( auto && x : v ) s << x << " "; return s; }
void dbg ( auto && ... x ) {
# ifdef LOCAL
char e {};
(( cerr << e << x , e = ' ') , ...) ;
cerr << '\n';
# endif
}
#define debug(...) dbg(#__VA_ARGS__, '=', __VA_ARGS__)


class SegmentTree {
    vec<ll> tree;
    int n;
    void build(vec<ll> &arr, int id, int l, int r) {
        if( l==r ) {
            tree[id] = arr[l];
        } else {
            int mid = (l+r)>>1;
            build(arr, 2*id, l, mid);
            build(arr, 2*id+1, mid+1, r);
            tree[id] = min(tree[2*id], tree[2*id+1]);
        }
    }

    void update(int id, int l, int r, int pos, ll val) {
        if( l==r ) {
            tree[id] = val;
        } else {
            int mid = (l+r)>>1;
            if(pos<=mid) {
                update(2*id, l, mid, pos, val);
            } else {
                update(2*id+1, mid+1, r, pos, val);
            }
            tree[id] = min(tree[2*id], tree[2*id+1]);
        }
    }

    ll query( int id, int l, int r, int targetl, int targetr ) {
        if( targetr<l || r<targetl ) return numeric_limits<ll>::max();
        if( l==targetl && r==targetr ) return tree[id];
        int mid = (l+r)>>1;
        return min(query( 2*id, l, mid, targetl, min(targetr, mid) ), query( 2*id+1, mid+1, r, max(targetl,mid+1), targetr ));
    }
    

public:
    SegmentTree( vec<ll> &arr ) {
        n = siz(arr);
        tree.resize(4*n);
        build(arr, 1, 0 ,n-1);
    }

    void update(int pos, ll val) {
        update(1, 0, n-1, pos-1, val);
    }

    ll query(int l, int r) {
        return query(1, 0, n-1, l-1, r-1);
    }
};

void solve(){
    ll n; cin>>n;
    vec<ll> v(n);
    for(auto &i: v) cin>>i;
    unordered_map<int,int> mp;
    for(int i=0;i<n;i++) mp[v[i]] = i;
    SegmentTree Seg(v);
    vec<ll> prefix_sum(n+1, 0);
    for(int i=0;i<n;i++) prefix_sum[i+1] = prefix_sum[i] + v[i+1];
    ll l = 0, r = n-1;
    while(l<r) {
        int mn_idx = mp[Seg.query(l+1, r+1)];
        if(prefix_sum[mn_idx] - prefix_sum[l] > prefix_sum[r+1] - prefix_sum[mn_idx+1]) {
            r = mn_idx - 1;
        } else {
            l = mn_idx + 1;
        }
    }
    cout<<v[l]<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}