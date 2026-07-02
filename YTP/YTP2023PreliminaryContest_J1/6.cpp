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

class SegmentTree {
    vec<ll> lazy, mn, mx;
    vec<bool> has;
    int n; 

    inline void apply(int id,ll v) {
        mx[id] = mn[id] = lazy[id] = v;
        has[id] = true; 
    }

    inline void pushDown(int id) {
        if(!has[id]) return;
        apply(id<<1, lazy[id]);
        apply(id<<1|1, lazy[id]);
        has[id] = false;
    }

    inline void pull(int id) {
        mx[id] = max(mx[id<<1], mx[id<<1|1]);
        mn[id] = min(mn[id<<1], mn[id<<1|1]);
    }

    void build(vec<ll> &arr, int id, int l, int r) {
        if(l==r ) {
            mx[id] = mn[id] = arr[l];
        } else {
            int mid = (l+r)>>1;
            build(arr, id<<1, l, mid);
            build(arr, id<<1|1, mid+1, r);
            pull(id);
        }
    }

    void rangef(int id, int l, int r, int ql, int qr, ll d) {
        if(d == 1) return;
        if(qr < l || r < ql) return ;
        if(ql <= l && r<=qr && mx[id]==mn[id]) {
            ll v = mn[id];
            ll nv = v/d;
            apply(id, nv);
            return;
        }
        pushDown(id);
        int mid = (l+r)>>1;
        rangef(id<<1, l, mid, ql, qr, d);
        rangef(id<<1|1, mid+1, r, ql, qr, d);
        pull(id);
    }

    void rangec(int id, int l, int r, int ql, int qr, ll d) {
        if(d == 1) return;
        if(qr < l || r < ql) return ;
        if(ql <= l && r<=qr && mx[id]==mn[id]) {
            ll v = mn[id];
            ll nv = (v+d-1)/d;
            apply(id, nv);
            return;
        }
        pushDown(id);
        int mid = (l+r)>>1;
        rangec(id<<1, l, mid, ql, qr, d);
        rangec(id<<1|1, mid+1, r, ql, qr, d);
        pull(id);
    }


    ll query(int id, int l, int r, int pos) {
        if(l==r) return mn[id];
        pushDown(id);
        int mid = (l + r) >> 1;
        if(pos<=mid) {
            return query(id<<1, l, mid, pos);
        } else {
            return query(id<<1|1, mid+1, r, pos);
        }
    }
public:
    SegmentTree(vec<ll> & arr) {
        n = siz(arr);
        mx.assign(4*n+5, 0);
        mn.assign(4*n+5, 0);
        lazy.assign(4*n+5, 0);
        has.assign(4*n+5, false);
        if(n) build(arr, 1, 0, n-1);
    }

    void rangef(int l, int r, ll d) {
        rangef(1, 0, n-1, l-1, r-1, d);
    }

    void rangec(int l, int r, ll d) {
        rangec(1, 0, n-1, l-1, r-1, d);
    }

    ll query(int pos) {
        return query(1, 0, n-1, pos-1);
    }
};


void solve(){
    int n, q; cin>>n>>q;
    vec<ll> v(n);
    for(auto &i: v) cin>>i;
    SegmentTree seg(v);
    while(q--) {
        char cmd; cin>>cmd;
        if(cmd == 'f') {
            int l, r, x; cin>>l>>r>>x;
            seg.rangef(l, r, x);
        } else if(cmd == 'c') {
            int l, r, x; cin>>l>>r>>x;
            seg.rangec(l, r, x);
        } else {
            int k; cin>>k;
            cout<<seg.query(k)<<endl;
        }
    }
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}