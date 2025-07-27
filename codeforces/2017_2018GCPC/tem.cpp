#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define siz(v) ((int)v.size())
#define ALL(v) v.begin(),v.end()
#define EB emplace_back
#define PB push_back
#define endl '\n'

using ll = long long ;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T,vec<T>,greater<T>>;
template <class T> bool chmin(T &a, T b){return (b < a and ( a=b,true));}
template <class T> bool chmax(T &a, T b){return (a<b  and ( a=b,true));}
template<class T> inline constexpr T inf = numeric_limits<T>::max()/2;
#ifdef LOCAL
template <class... T> void dbg(T... x){
    char e{};
    ((cerr << e << x, e = ' '),...);

}
#define debug(x...) dbg(#x, '=',x,'\n')
#else 
#define debug(...)((void)0)
#endif

#define rall(x) x.rbegin(),x.rend()
const ll MOD = 998244353;
template<typename T> bool INR (T a, T b, T c){return b <= a && a<= c;}



void solve(){
    cout << 1 ;
}


signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    ll t = 1;
    while(t--) solve();
}