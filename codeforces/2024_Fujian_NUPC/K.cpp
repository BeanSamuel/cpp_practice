/*
Question: K. Uniform Dispersion
Link: https://codeforces.com/gym/105168/problem/K
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

const int MXN = 1e9; const int N = MXN + 10;
#define pii pair<int,int>
#define pll pair<ll, ll>

void solve(){
    int n, k; cin>>n>>k;
    vec<pii> x(n), y(n);
    for(int i=0;i<n;i++) {
        cin>>x[i].F>>y[i].F;
        x[i].S = y[i].S = i;
    }

    if( k==0 ) {
        cout<<"Yes"<<endl;
        return;
    }

    if(n%((k+1)*(k+1)) != 0 || n<(k+1)*(k+1)) {
        cout<<"No"<<endl;
        return;
    }
    sort(ALL(x));
    sort(ALL(y));
    vec<pii> cor(n);

    int add = n/(k+1), cnt = 0;

    for(int i=0;i<n;i+=add) {
        if(i>=add && x[i-1].F==x[i].F) {
            cout<<"No"<<endl;
            return;
        }
        for(int j=i;j<i+add;j++) cor[x[j].S].F = cnt;
        cnt++;
    }
    
    cnt = 0;

    for(int i=0;i<n;i+=add) {
        if(i>=add && y[i-1].F==y[i].F) {
            cout<<"No"<<endl;
            return;
        }
        for(int j=i;j<i+add;j++) cor[y[j].S].S = cnt;
        cnt++;
    }

    int add2 = add/(k+1);
    map<pii, int> mp;
    for(auto i:cor) mp[i]++;
    for(auto i:mp) {
        if(i.S != add2) {
            cout<<"No"<<endl;
            return;
        }
    }
    cout<<"Yes"<<endl;
}


signed main(){
    fastio;
	int t=1; cin>>t;
	while(t--) solve();
}