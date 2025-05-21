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

using namespace std;

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
            tree[id] = tree[2*id] ^ tree[2*id+1];
        }
    }

    ll query( int id, int l, int r, int targetl, int targetr ) {
        if( targetr<l || r<targetl ) return 0LL;
        if( l==targetl && r==targetr ) return tree[id];
        int mid = (l+r)>>1;
        return query( 2*id, l, mid, targetl, min(targetr, mid) ) ^ query( 2*id+1, mid+1, r, max(targetl,mid+1), targetr );
    }

public:
    SegmentTree( vec<ll> &arr ) {
        n = arr.size();
        tree.resize(4*n);
        build(arr, 1, 0 ,n-1);
    }

    ll query(int l, int r) {
        return query(1, 0, n-1, l-1, r-1);
    }
};

void solve(){
    int n, q; cin>>n>>q;
    vec<ll> v(n);
    for(auto &i:v) cin>>i;
    SegmentTree tree(v);
    while(q--) {
        int a, b; cin>>a>>b;
        cout<< tree.query(a,b) <<endl;
    }

}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}