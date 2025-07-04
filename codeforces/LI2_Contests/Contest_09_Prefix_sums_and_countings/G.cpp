/*
Question: G. Haybale Stacking
Link: https://codeforces.com/group/jtU6D2hVEi/contest/104997/problem/G
*/
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

template<typename T>
class Fenwick {
private:
    int n;
    vec<T> bit;
    static int lowbit(int x) { return x&-x; }

public:
    explicit Fenwick(int _n)
        : n(_n), bit(n+1, T(0)) {}
    
    explicit Fenwick(const vec<T>& a)
        : Fenwick((int)a.size() - 1) {
            for(int i=1;i<=n;i++) range_update(i,i,a[i]);
        }

    void update(int idx, T val) {
        for(int i=idx;i<=n;i+=lowbit(i)) {
            bit[i] += val;
        }
    }
    void range_update(int l, int r, T val) {
        update(l, val);
        update(r+1, -val);
    }

    T query(int idx) { 
        T ret = 0;
        for(;idx>0;idx-=lowbit(idx)) {
            ret += bit[idx];
        }
        return ret;
    }

};

void solve(){
    int n, k; cin>>n>>k;
    Fenwick<int> BIT(n);
    while(k--) {
        int x, y; cin>>x>>y;
        BIT.range_update(x, y, 1);
    }
    for(int i=1;i<=n;i++) {
        cout<<BIT.query(i)<<" ";
    }
    cout<<endl;
}

signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}