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

using ull = unsigned long long;

int label[4][4] = {
    {0, 1, 2, 3},
    {0, 3, 2, 1},
    {2, 1, 0, 3},
    {2, 3, 0, 1}
};

int trans[4][4] = {
    {1, 0, 0, 2},
    {0, 3, 1, 1},
    {2, 2, 3, 0},
    {3, 1, 2, 3}
};

ull find_idx(pll coor, int s, int state, int depth) {

    if((1LL << depth) > s) return 0LL;

    if(2LL*coor.F<s && 2LL*coor.S<s) {
        return ( (ull)label[state][0] << (2ULL*(30-depth)) | find_idx({2LL*coor.F, 2LL*coor.S}, s, trans[state][0], depth+1) );
    } else if(2LL*coor.F<s && 2LL*coor.S>s) {
        return ( (ull)label[state][1] << (2ULL*(30-depth)) | find_idx({2LL*coor.F, 2LL*coor.S-s}, s, trans[state][1], depth+1) );
    } else if(2LL*coor.F>s && 2LL*coor.S>s) {
        return ( (ull)label[state][2] << (2ULL*(30-depth)) | find_idx({2LL*coor.F-s, 2LL*coor.S-s}, s, trans[state][2], depth+1) );
    } else {
        return ( (ull)label[state][3] << (2ULL*(30-depth)) | find_idx({2LL*coor.F-s, 2LL*coor.S}, s, trans[state][3], depth+1) );
    } 
}

void solve(){
    int n, s; cin>>n>>s;
    map<pii,string> mp;
    for(int i=0;i<n;i++) {
        int x, y; string name;
        cin>>x>>y>>name;
        mp[make_pair(x,y)] = name;
    }
    vec<pair<ull, pii>> v;
    for(auto [coor, name] : mp) {
        ull idx = find_idx(coor, s, 0, 0);
        v.push_back({idx, coor});
    }
    sort(ALL(v));
    for(auto [idx, coor] : v) {
        // debug(idx, mp[coor]);
        cout<<mp[coor]<<endl;
    }
}



signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}