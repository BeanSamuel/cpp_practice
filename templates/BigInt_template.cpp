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
    static const int BASE = 1000000000;
    static const int BASE_DIGITS = 9;
    vector<int> z; // base 1e9, little-endian, 0 = 空陣列
    void trim(){ while(!z.empty()&&z.back()==0) z.pop_back(); }

    BigInt(){}
    BigInt(long long num){ if(num<0)num=0; while(num){ z.push_back((int)(num%BASE)); num/=BASE; } }
    BigInt(const string& str){ read(str); }
    void read(const string& s){
        z.clear(); int start=0; if(!s.empty()&&s[0]=='+') start=1;
        for(int i=(int)s.size()-1;i>=start;i-=BASE_DIGITS){
            int x=0,from=max(start,i-BASE_DIGITS+1);
            for(int j=from;j<=i;j++) x=x*10+(s[j]-'0');
            z.push_back(x);
        } trim();
    }
    static int cmp(const BigInt&a,const BigInt&b){
        if(a.z.size()!=b.z.size()) return a.z.size()<b.z.size()?-1:1;
        for(int i=(int)a.z.size()-1;i>=0;i--) if(a.z[i]!=b.z[i]) return a.z[i]<b.z[i]?-1:1;
        return 0;
    }
    friend bool operator<(const BigInt&a,const BigInt&b){return cmp(a,b)<0;}
    friend bool operator>(const BigInt&a,const BigInt&b){return cmp(a,b)>0;}
    friend bool operator<=(const BigInt&a,const BigInt&b){return cmp(a,b)<=0;}
    friend bool operator>=(const BigInt&a,const BigInt&b){return cmp(a,b)>=0;}
    friend bool operator==(const BigInt&a,const BigInt&b){return cmp(a,b)==0;}
    friend bool operator!=(const BigInt&a,const BigInt&b){return cmp(a,b)!=0;}
    friend istream& operator>>(istream& in,BigInt& v){ string s; in>>s; v.read(s); return in; }
    friend ostream& operator<<(ostream& o,const BigInt& v){
        if(v.z.empty()){o<<0;return o;}
        o<<v.z.back(); char b[16];
        for(int i=(int)v.z.size()-2;i>=0;i--){snprintf(b,sizeof(b),"%09d",v.z[i]);o<<b;}
        return o;
    }
    friend BigInt operator+(const BigInt&a,const BigInt&b){
        BigInt r; long long c=0;
        for(size_t i=0;i<a.z.size()||i<b.z.size()||c;i++){
            long long cur=c; if(i<a.z.size())cur+=a.z[i]; if(i<b.z.size())cur+=b.z[i];
            r.z.push_back((int)(cur%BASE)); c=cur/BASE;
        } r.trim(); return r;
    }
    friend BigInt operator-(const BigInt&a,const BigInt&b){ // 只支援 a>=b
        assert(cmp(a,b)>=0); BigInt r; long long bw=0;
        for(size_t i=0;i<a.z.size();i++){
            long long cur=(long long)a.z[i]-bw-(i<b.z.size()?b.z[i]:0);
            if(cur<0){cur+=BASE;bw=1;}else bw=0; r.z.push_back((int)cur);
        } r.trim(); return r;
    }

    // ---------- NTT（base 10 係數，質數 998244353，整數精確）----------
    static const unsigned MOD=998244353u, G=3;
    static unsigned pw(unsigned long long a,unsigned long long e){
        unsigned long long r=1; a%=MOD;
        while(e){ if(e&1)r=r*a%MOD; a=a*a%MOD; e>>=1; } return (unsigned)r;
    }
    static void ntt(vector<unsigned>& a,bool inv){
        int n=siz(a);
        for(int i=1,j=0;i<n;i++){int bit=n>>1;for(;j&bit;bit>>=1)j^=bit;j^=bit;if(i<j)swap(a[i],a[j]);}
        for(int len=2;len<=n;len<<=1){
            unsigned w=pw(G,(MOD-1)/len); if(inv) w=pw(w,MOD-2);
            for(int i=0;i<n;i+=len){
                unsigned wn=1;
                for(int k=0;k<len/2;k++){
                    unsigned u=a[i+k], v=(unsigned)((unsigned long long)a[i+k+len/2]*wn%MOD);
                    a[i+k]=u+v<MOD?u+v:u+v-MOD;
                    a[i+k+len/2]=u>=v?u-v:u+MOD-v;
                    wn=(unsigned)((unsigned long long)wn*w%MOD);
                }
            }
        }
        if(inv){ unsigned ni=pw(n,MOD-2); for(auto& x:a) x=(unsigned)((unsigned long long)x*ni%MOD); }
    }
    static BigInt mulSchool(const BigInt&a,const BigInt&b){
        vector<long long> res(a.z.size()+b.z.size(),0);
        for(size_t i=0;i<a.z.size();i++){ long long c=0;
            for(size_t j=0;j<b.z.size()||c;j++){
                long long cur=res[i+j]+c+(j<b.z.size()?(long long)a.z[i]*b.z[j]:0);
                res[i+j]=cur%BASE; c=cur/BASE;
            } }
        BigInt r; r.z.resize(res.size()); for(size_t i=0;i<res.size();i++)r.z[i]=(int)res[i];
        r.trim(); return r;
    }
    friend BigInt operator*(const BigInt&a,const BigInt&b){
        if(a.z.empty()||b.z.empty()) return BigInt();
        if(min(a.z.size(),b.z.size())<=64) return mulSchool(a,b); // 小數字走 schoolbook
        auto split=[](const vector<int>& z){            // base 1e9 -> base 10
            vector<unsigned> r; r.reserve(z.size()*9);
            for(int v:z){ for(int k=0;k<9;k++){ r.push_back(v%10); v/=10; } }
            return r;
        };
        vector<unsigned> fa=split(a.z), fb=split(b.z);
        int need=(int)fa.size()+(int)fb.size(); int n=1; while(n<need)n<<=1;
        fa.resize(n,0); fb.resize(n,0);
        ntt(fa,false); ntt(fb,false);
        for(int i=0;i<n;i++) fa[i]=(unsigned)((unsigned long long)fa[i]*fb[i]%MOD);
        ntt(fa,true);
        vector<long long> c(n); for(int i=0;i<n;i++) c[i]=fa[i];
        long long carry=0;                              // 正規化回 base 10
        for(int i=0;i<n;i++){ long long cur=c[i]+carry; c[i]=cur%10; carry=cur/10; }
        while(carry){ c.push_back(carry%10); carry/=10; }
        BigInt r;                                       // 每 9 個十進位 -> 一個 base-1e9 limb
        for(size_t i=0;i<c.size();i+=9){
            long long limb=0,p=1;
            for(int k=0;k<9&&i+k<c.size();k++){ limb+=c[i+k]*p; p*=10; }
            r.z.push_back((int)limb);
        }
        r.trim(); return r;
    }

    // 除法：O(n^2 log)，僅適合中小數字（百萬位請勿使用，見下方說明）
    friend pair<BigInt,BigInt> divmod(const BigInt&a,const BigInt&b){
        assert(!b.z.empty()); BigInt q,r; q.z.assign(a.z.size(),0);
        for(int i=(int)a.z.size()-1;i>=0;i--){
            r.z.insert(r.z.begin(),a.z[i]); r.trim();
            int lo=0,hi=BASE-1,d=0;
            while(lo<=hi){int mid=lo+(hi-lo)/2; if(cmp(b*BigInt((long long)mid),r)<=0){d=mid;lo=mid+1;}else hi=mid-1;}
            q.z[i]=d; if(d)r=r-b*BigInt((long long)d);
        } q.trim(); return {q,r};
    }
    friend BigInt operator/(const BigInt&a,const BigInt&b){return divmod(a,b).first;}
    friend BigInt operator%(const BigInt&a,const BigInt&b){return divmod(a,b).second;}
};