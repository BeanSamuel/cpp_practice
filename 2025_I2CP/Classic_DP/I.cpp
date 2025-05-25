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

void solve(){
    string s1, s2; cin>>s1>>s2;
    s1.insert(s1.begin(), '$');
    s2.insert(s2.begin(), '$');
    int n1=s1.length(), n2=s2.length();
    
    vec<vec<int>> dp(n1+1, vec<int>(n2+1, MXN));
    dp[0][0] = 0;
    for(int i=1;i<=n1;i++) dp[i][0] = i;
    for(int j=1;j<=n2;j++) dp[0][j] = j;

    for(int i=1;i<=n1;i++) {
        for(int j=1;j<=n2;j++) {
            if(s1[i] == s2[j]) {
                dp[i][j] = dp[i-1][j-1];
            } else {

                dp[i][j] = min( {dp[i-1][j], dp[i-1][j-1], dp[i][j-1]} ) + 1;
            }
        }
    }
    cout<<dp[n1][n2]<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}