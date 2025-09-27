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

struct PAM {
    // nxt[i][c]：從節點 i，兩側加上字元 c ('a' ~ 'z') 之後得到的節點
    vec<array<int, 26>> nxt;
    // fail[i]：節點 i 的「失敗指標」，指向「次長回文後綴」
    vec<int> fail;
    // len[i]：節點 i 代表的回文長度
    vec<int> len;
    // dep[i]：這個節點對應的回文有幾層後綴（例如 "ababa" → "aba" → "a" = 3 層)
    vec<int> dep;
    // walk[pos]：處理到字串的第 pos 個字元時，對應的最長後綴回文節點編號
    vec<int> walk;

    int odd, even;  // 兩個根節點：odd 長度 = -1，even 長度 = 0
    int lst;        // 當前「最長後綴回文」的節點編號
    string s;       // 已經處理過的字串
    
    int newNode(int l){
        fail.PB(0);
        nxt.PB({});
        len.PB(l);
        dep.PB(0);
        return siz(fail) - 1;
    } 

    PAM() : odd(newNode(-1)), even(newNode(0)) {
        lst = fail[even] = odd; // 空字串的 fail 指向 odd
    }

    void reserve(int l) {
        fail.reserve(l+2);
        len.reserve(l+2);
        nxt.reserve(l+2);
        dep.reserve(l+2);
        walk.reserve(l+2);
    }

    int up(int p) {
        while(s[siz(s)-len[p]-2] != s.back()) {
            p = fail[p];
        }
        return p;
    }

    int add(char c) {
        s+=c;
        lst = up(lst);
        int x = c - 'a';
        if(!nxt[lst][x]) {
            int id = newNode(len[lst] + 2);
            nxt[lst][x] = id;
            if(len[id] == 1) {
                fail[id] = even;
            } else {
                fail[id] = nxt[up(fail[lst])][x];
            }
        }
        lst = nxt[lst][x];
        dep[lst] = dep[fail[lst]] + 1;
        return lst;
    }
    
    void build(string_view sv){
        reserve(siz(sv));
        for(char c: sv) {
            walk.PB(add(c));
        }
    }
};

