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

#ifdef LOCAL
template<class... T> void dbg(T...x) {
    char e{};
    ((cerr << e << x, e = ' '),...);
}
#define debug(x...) dbg(#x, '=',x,'\n')
#else 
#define debug(...) ((void)0)
#endif


void solve(){
    ll n, m, q; cin>>n>>m>>q;
    vec<vec<ll>> v(m);
    for(ll i=0;i<m;i++) {
        int cmd; cin>>cmd;
        v[i].EB(cmd);
        if(cmd == 1) {
            int a, b; cin>>a>>b;
            v[i].EB(a);
            v[i].EB(b);
        } else if(cmd == 2) {
            int a, b, c, d; cin>>a>>b>>c>>d;
            v[i].EB(a);
            v[i].EB(b);
            v[i].EB(c);
            v[i].EB(d);
        } else if(cmd == 3) {
            int a, b, c, d; cin>>a>>b>>c>>d;
            v[i].EB(a);
            v[i].EB(b);
            v[i].EB(c);
            v[i].EB(d); 
        } else if(cmd == 4) {
            int a, b, c; cin>>a>>b>>c;
            v[i].EB(a);
            v[i].EB(b);
            v[i].EB(c);
        } else if(cmd == 5) {
            int a, b, c; cin>>a>>b>>c;
            v[i].EB(a);
            v[i].EB(b);
            v[i].EB(c);
        }
    }
    
    vec<ll> qs(q);
    for(auto &i:qs) cin>>i;

    vec<ll> ans;

    for(ll i=0;i<q;i++) {
        ll x = qs[i];
        ll add = 0;
        
        for(ll j=m-1;j>=0;j--) {
            int t = v[j][0];
            if(t == 1) {
                ll a = v[j][1], b = v[j][2];
                if(a <= x and x < b) {
                    x = a + (b-1-x);
                }
            } else if(t == 2) {
                ll a = v[j][1], b = v[j][2], c = v[j][3], d = v[j][4];
                if (a > c) { swap(a, c); swap(b, d); }
                ll r = b - a;
                ll rr = d - c;
                if (a <= x and x < a + rr) {
                    x = c + (x - a);
                } else if (a + rr <= x and x < d - r) {
                    x = x - (rr - r);
                } else if (d - r <= x and x < d) {
                    x = x - (d - b);
                }
            } else if(t == 3) {
                ll a = v[j][1], b = v[j][2], c = v[j][3], d = v[j][4];
                ll r = b - a;
                ll rr = d - c;
                if (c <= x and x < c + r) {
                    x = a + (x - c);
                } else if (x >= c + r) {
                    x = x - (r - rr);
                }
            } else if(t == 4) {
                ll a = v[j][1], b = v[j][2], c = v[j][3];
                if( a <= x and x < b) {
                    ans.EB(c + add);
                    goto NEXT_QUERY;
                }
            } else if(t == 5) {
                ll a = v[j][1], b = v[j][2], c = v[j][3];
                if(a <= x and x < b) {
                    add += c;
                }
            }
        }
        ans.EB(1 + x + add);

    NEXT_QUERY:
        ;
    }

    for(int i=0;i<siz(ans);i++) {
        if(i) cout<<" ";
        cout<<ans[i];
    }
    cout<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}