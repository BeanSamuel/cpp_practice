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

void solve(){
    int n,m; cin>>n>>m;
    vec<int> a(n), b(m);
    for(auto &i:a) cin>>i;
    for(auto &i:b) cin>>i;

    for(int i=0,j=0;i<n&&j<m;i++) {
        if(a[i]>=b[j]) j++;
        if(j==m) {
            cout<<0<<endl;
            return;
        }
    }

    int now=0, now2=-1;
    for(int i=0;i<n;i++) {
        if(now<m) chmax(now2, now+1);
        if(now<m && a[i]>=b[now]) now++;
        if(now2<m && now2>=0 &&a[i]>=b[now2]) now2++;
    }
    if(now<m) chmax(now2, now+1);
    if(now2<m) {cout<<-1<<endl; return;}

    set<int> s;
    for(int i:b) s.insert(i);
    vec<int> v;
    for(auto i:s) v.EB(i);
    
    auto chk = [&] (int k) {
        int now=0, now2=-1;
        for(int i=0;i<n;i++) {
            if(now<m && k>=b[now]) chmax(now2, now+1);
            if(now<m && a[i]>=b[now]) now++;
            if(now2<m && now2>=0 &&a[i]>=b[now2]) now2++;
        }
        if(now<m && k>=b[now]) chmax(now2, now+1);
        return now2>=m;
    };
    int l = 0, r=v.size()-1, ans = v.size()-1; 
    while(l <= r) {
        int mid = (l+r)/2;
        if(chk(v[mid])) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout<<v[ans]<<endl;

}


signed main(){
    fastio;
	int t=1; cin>>t;
	while(t--) solve();
}