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
const int xx[8] = {0,-1,0,1,1,1,-1,-1}; const int yy[8] = {1,0,-1,0,1,-1,-1,1};

void pmod(ll &a, ll b) {a = (a+b)%MOD;}
void mmod(ll &a, ll b) {a = (a-b+MOD)%MOD;} 
void tmod(ll &a, ll b) {a = (a*b)%MOD;}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b);}
ll POW(ll a, ll b) {ll res=1; do{if(b%2)tmod(res,a);tmod(a,a);}while(b>>=1); return res;}

const ll MXN = 1e15; const ll N = MXN + 10;
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

struct Vec {
    ll x, y;
    Vec operator+(const Vec &o) const { return {x + o.x, y + o.y}; }
};


Vec rot(Vec v, int r) {
    r %= 4;
    if(r == 0) return v;
    else if(r == 1) return {-v.y, v.x};
    else if(r == 2) return {-v.x, -v.y};
    else return {v.y, -v.x};
}


class SegmentTree {
    vec<Vec> tree;
    vec<int> lazy;
    int n;

    void applyLazy(int id, int r) {
        tree[id] = rot(tree[id], r);
        lazy[id] = (lazy[id] + r) % 4;
    }

    void pushDown(int id) {
        if(lazy[id]) {
            applyLazy(2*id, lazy[id]);
            applyLazy(2*id+1, lazy[id]);
            lazy[id] = 0;
        }
    }

    void build(vec<ll> &arr, int id, int l, int r) {
        if( l==r ) {
            tree[id] = {arr[l], 0};
        } else {
            int mid = (l+r)>>1;
            build(arr, 2*id, l, mid);
            build(arr, 2*id+1, mid+1, r);
            tree[id] = tree[2*id] + tree[2*id+1];
        }
    }

    void update(int id, int l, int r, int pos, Vec val) {
        if( l==r ) {
            tree[id] = val;
        } else {
            pushDown(id);
            int mid = (l+r)>>1;
            if(pos<=mid) {
                update(2*id, l, mid, pos, val);
            } else {
                update(2*id+1, mid+1, r, pos, val);
            }
            tree[id] = tree[2*id] + tree[2*id+1];
        }
    }

    void rotate(int id, int l, int r, int targetl, int targetr, int rr) {
        if( targetr<l || r<targetl ) return;
        if( targetl<=l && r <=targetr ) {
            applyLazy(id, rr); return;
        }
        pushDown(id);
        int mid = (l+r)>>1;
        rotate(2*id, l, mid, targetl, targetr, rr);
        rotate(2*id+1, mid+1, r, targetl, targetr, rr);
        tree[id] = tree[2*id] + tree[2*id+1];
    }

    Vec get(int id, int l, int r, int pos) {
        if(l==r) return tree[id];
        pushDown(id);
        int mid = (l+r)>>1;
        if(pos<=mid) return get(2*id, l, mid, pos);
        else return get(2*id+1, mid+1, r, pos);
    }

    Vec query( int id, int l, int r, int targetl, int targetr ) {
        if( targetr<l || r<targetl ) return {0,0};
        if( l==targetl && r==targetr ) return tree[id];
        pushDown(id);
        int mid = (l+r)>>1;
        return query( 2*id, l, mid, targetl, min(targetr, mid) ) + query( 2*id+1, mid+1, r, max(targetl,mid+1), targetr );
    }
    

public:
    SegmentTree( vec<ll> &arr ) {
        n = siz(arr);
        tree.resize(4*n);
        lazy.resize(4*n, 0);
        build(arr, 1, 0 ,n-1);
    }

    void rotateSuffix(int x, int rr) {
        if(rr) rotate(1, 0, n-1, x-1, n-1, rr);
    }

    void setLength(int pos, int len) {
        Vec v = get(1, 0, n-1, pos-1);
        
        if(v.x!=0) {
            v = {(v.x>0?1:-1)*len,0};
        } else {
            v = {0,(v.y>0?1:-1)*len};
        }
        update(1, 0, n-1, pos-1, v);
    }

    Vec query(int k) {
        return query(1, 0, n-1, 0, k-1);
    }
};


void solve(){
    int n, q; cin>>n>>q;
    vec<ll> v(n);
    for(auto &i: v) cin>>i;
    SegmentTree seg(v);
    vec<int> ang(n+1, 0);
    while(q--) {
        int cmd; cin>>cmd;
        if(cmd==1) {
            int k; cin>>k;
            Vec ans = seg.query(k);
            cout<<ans.x<<" "<<ans.y<<endl;
        } else if(cmd == 2) {
            int x, theta; cin>>x>>theta;
            int rr = ((theta-ang[x])/90 + 4)%4;
            ang[x] = theta;
            seg.rotateSuffix(x, rr);
        } else {
            int x, len; cin>>x>>len;
            seg.setLength(x, len);
        }
    }

}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}