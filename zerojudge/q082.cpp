#include <bits/stdc++.h>
using namespace std;
#define ll signed long long
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

const ll MOD =  numeric_limits<ll>::max();
const double PI = 3.14159265358;
const double EPS = 1e-9;
const int xx[8] = {0,1,0,-1,1,1,-1,-1}; 
const int yy[8] = {1,0,-1,0,1,-1,-1,1};

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

struct BigInt {
    string s;

    BigInt(long long num = 0) { s = to_string(num); }
    BigInt(string str) { 
        while(siz(str) > 1 && str[0] == '0') str.erase(str.begin());
        s = str; 
    }

    friend istream& operator>>(istream& in, BigInt &a) {
        in >> a.s;
        return in;
    }
    friend ostream& operator<<(ostream& out, const BigInt &a) {
        out << a.s;
        return out;
    }

    friend BigInt operator+(const BigInt &a, const BigInt &b) {
        string A = a.s, B = b.s;
        if(siz(A) < siz(B)) swap(A, B);
        reverse(ALL(A));
        reverse(ALL(B));
        int carry = 0;
        string res;
        for(size_t i=0; i<siz(A); i++) {
            int x = A[i]-'0' + (i < siz(B) ? B[i]-'0' : 0) + carry;
            carry = x/10;
            res.push_back(x%10+'0');
        }
        if(carry) res.push_back(carry+'0');
        reverse(ALL(res));
        return BigInt(res);
    }

    // 乘法
    friend BigInt operator*(const BigInt &a, const BigInt &b) {
        int n = siz(a.s), m = siz(b.s);
        vector<int> res(n+m, 0);
        for(int i=n-1; i>=0; i--) {
            for(int j=m-1; j>=0; j--) {
                int mul = (a.s[i]-'0') * (b.s[j]-'0');
                int sum = res[i+j+1] + mul;
                res[i+j+1] = sum % 10;
                res[i+j] += sum / 10;
            }
        }
        string result;
        for(int x: res) {
            if(!(result.empty() && x==0)) result.push_back(x+'0');
        }
        return result.empty() ? BigInt("0") : BigInt(result);
    }
};

BigInt mypow(BigInt a, long long b){
    BigInt res("1");
    while(b > 0) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve(){
    BigInt n,a,b;
    cin >> n >> a >> b;
    long long nn = stoll(n.s); 
    if(nn % 2 == 0) {
        cout<<"不能"<<endl;
        return;
    }
    cout<<"能"<<endl;
    BigInt ans = mypow(a, nn) + mypow(b, nn);
    cout << ans << endl;
}

signed main(){
    // fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}
