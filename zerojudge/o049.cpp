#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long
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

string add(const string &a, const string &b) {
    string res;
    int carry = 0, i = a.size()-1, j = b.size()-1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string mul(const string &a, int b) {
    if (b == 0) return "0";
    string res;
    int carry = 0;
    for (int i = a.size()-1; i >= 0; i--) {
        int prod = (a[i] - '0') * b + carry;
        res.push_back(prod % 10 + '0');
        carry = prod / 10;
    }
    while (carry) {
        res.push_back(carry % 10 + '0');
        carry /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

pair<string,int> divmod(const string &a, int b) {
    string res;
    long long cur = 0;
    for (char c : a) {
        cur = cur * 10 + (c - '0');
        res.push_back(cur / b + '0');
        cur %= b;
    }
    // 去掉前導零
    int pos = 0;
    while (pos+1 < res.size() && res[pos] == '0') pos++;
    return {res.substr(pos), (int)cur};
}

void solve(){
    int n, m; cin>>n>>m;
    string x; cin>>x;
    string value = "0";
    for (char c : x) {
        int digit = c - '0';
        value = mul(value, n);
        value = add(value, to_string(digit));
    }
    string res;
    while (value != "0") {
        auto [q, r] = divmod(value, m);
        res.push_back(r + '0');
        value = q;
    }
    reverse(res.begin(), res.end());
    cout<<res<<endl;
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}