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

vec<string> split(string &s) {
    vector<string> ret;
    string cur = "";
    for (int i = 0; i < siz(s); i++) {
        if (s[i] == '1') {
            int j = i;
            while (j < siz(s) && s[j] == '1') j++;
            if (j - i >= 2) {
                if (!cur.empty()) {
                    ret.PB(cur);
                    cur.clear();
                }
                i = j - 1;
                continue;
            }
        }
        cur.PB(s[i]);
    }
    if (!cur.empty()) ret.PB(cur);
    return ret;
}

void solve(){
    int n; cin>>n;
    string s; cin>>s;
    vec<string> v = split(s);
    if(n<=2) {
        cout<<"YES"<<endl;
        return;
    }
    if(s[0]=='1'&&s[1]=='1') v.insert(v.begin(), "");
    if(s[n-1]=='1'&&s[n-2]=='1') v.EB("");
    if(siz(v) == 1){
        if(v.front()=="101"){
            cout<<"NO"<<endl;
            return;
        }
    }else if(siz(v)==2){
        if(v.front()=="101" or v.front()=="10" or v.back()=="101" or v.back()=="01"){
            cout<<"NO"<<endl;
            return;
        }
    }
    for(int i=1;i<siz(v)-1;i++) {
        if("0" == v[i] or "101" == v[i] or "01"==v[i] or "10"==v[i]){
            cout<<"NO"<<endl;
            return;
        }
    }

    if(siz(v)==1){
        if(v.front()=="101"){
            cout<<"NO"<<endl;
            return;
        }
    } else {
        
    }
    cout<<"YES"<<endl;
}


signed main(){
    fastio;
	int t=1; cin>>t;
	while(t--) solve();
}