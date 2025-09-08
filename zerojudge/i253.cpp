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

vec<int> v;

void build() {
    for(int i=1;i<=10000;i++) v.EB(i*i);
}


void solve(){
    int n, k; cin>>n>>k;
    if(k>=7||k<=2) { cout<<"no"<<endl; return; }
    else if(k==3) { 
        if(find(ALL(v), n) != v.end()) cout<<"yes"<<endl;
        else cout<<"no"<<endl;
    } else if(k == 4) {
        if(n>=2) cout<<"yes"<<endl;
        else cout<<"no"<<endl;
    } else if(k == 5) {
        for(int i=3;i<=n;i++) {
            for(int j=1;j<i;j++) {
                for(int l=1;l<i;l++) {
                    if(l+j>=i) continue; 
                    if(v[i-1] - v[j-1] - v[l-1] == n) {
                        cout<<"yes"<<endl;
                        return;
                    }
                }
            }
        }
        cout<<"no"<<endl;
    } else if(k==6) {
        for(int i=3;i<=n;i++) {
            for(int j=1;j<i;j++) {
                for(int l=1;l<i;l++) {
                    if(j+l>=i) continue;
                    for(int m=1;m<i;m++) {
                        if(j+m>=i || m+l>=i) continue;
                        if(v[i-1] - v[j-1] - v[l-1] -v[m-1] == n) {
                            cout<<"yes"<<endl;
                            return;
                        }
                    }

                }
            }
        }
        cout<<"no"<<endl;
    }

}


signed main(){
    fastio;
    build();
	int t=1; cin>>t;
	while(t--) solve();
}