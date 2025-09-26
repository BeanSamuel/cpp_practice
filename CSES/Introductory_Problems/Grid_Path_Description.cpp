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


bool grid[7][7];


void solve(){
    string s; cin>>s;
    ll ans = 0;
    auto dfs = [&](auto self, pii now, int move)->void{
        if(move>=48){
            if(now==make_pair(6, 0)) ans++;
            return;
        }
        if(now==make_pair(6,0)) return;
        
        if(abs(now.F-6) + abs(now.S-0)>48-move) return;

        bool up = (now.F-1<0) || grid[now.F-1][now.S];
        bool down = (now.F+1>6) || grid[now.F+1][now.S];
        bool left = (now.S-1<0) || grid[now.F][now.S-1];
        bool right = (now.S+1>6) || grid[now.F][now.S+1];
        if(up and down and !left and !right) return;
        if(!up and !down and left and right) return;

        grid[now.F][now.S] = true;
        if(s[move] == '?') {
            for(int i=0;i<4;i++) {
                int nxt_x = now.F+xx[i], nxt_y = now.S+yy[i];
                if(0<=nxt_x and nxt_x<=6 and 0<=nxt_y and nxt_y<=6 and !grid[nxt_x][nxt_y]){
                    self(self, {nxt_x, nxt_y}, move+1);
                }
            }
        } else if(s[move] == 'D'){
            int nxt_x = now.F+1, nxt_y = now.S;
            if(0<=nxt_x and nxt_x<=6 and 0<=nxt_y and nxt_y<=6 and !grid[nxt_x][nxt_y]){
                self(self, {nxt_x, nxt_y}, move+1);
            }
        } else if(s[move] == 'U'){
            int nxt_x = now.F-1, nxt_y = now.S;
            if(0<=nxt_x and nxt_x<=6 and 0<=nxt_y and nxt_y<=6 and !grid[nxt_x][nxt_y]){
                self(self, {nxt_x, nxt_y}, move+1);
            }
        } else if(s[move] == 'L'){
            int nxt_x = now.F, nxt_y = now.S-1;
            if(0<=nxt_x and nxt_x<=6 and 0<=nxt_y and nxt_y<=6 and !grid[nxt_x][nxt_y]){
                self(self, {nxt_x, nxt_y}, move+1);
            }
        } else if(s[move] == 'R'){
            int nxt_x = now.F, nxt_y = now.S+1;
            if(0<=nxt_x and nxt_x<=6 and 0<=nxt_y and nxt_y<=6 and !grid[nxt_x][nxt_y]){
                self(self, {nxt_x, nxt_y}, move+1);
            }
        }
        grid[now.F][now.S] = false;
        return;
    };

    dfs(dfs, {0,0}, 0);
    cout<<ans<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}