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

constexpr double eps = 1E-9L;

struct Pt {
    double x{}, y{};
};

Pt operator+(Pt a, Pt b) {
    return {a.x + b.x, a.y + b.y};
}

Pt operator-(Pt a, Pt b) {
    return {a.x - b.x, a.y - b.y};
}

double operator*(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}

double operator^(Pt a, Pt b) {
    return a.x * b.y -  a.y * b.x;
}

int sgn(double x) {
    return (x>-eps) - (x<eps);
}

double ori(Pt a, Pt b, Pt c) {
    return (b-a) ^ (c-a);
}


struct Line {
    Pt a, b;
    Pt dir() const { return b - a; }
};

int PtSide(Pt p, Line L) {
    return sgn(ori(L.a, L.b, p));
}

bool PtOnSeg(Pt p, Line L) {
    return PtSide(p, L) == 0 and sgn((p - L.a) * (p - L.b)) <= 0;
}

bool isInter(Line l, Line m) {
    if(PtOnSeg(m.a, l) or PtOnSeg(m.b, l) or PtOnSeg(l.a, m) or PtOnSeg(l.b, m))
        return true;
    return PtSide(m.a, l) * PtSide(m.b, l) <0 and PtSide(l.a, m) * PtSide(l.b, m) < 0;
}

void solve(){
    int x1, x2, x3, x4, y1, y2, y3, y4;
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    Pt p1{x1, y1};
    Pt p2{x2, y2};
    Pt p3{x3, y3};
    Pt p4{x4, y4};

    Line line1, line2;
    line1.a = p1; line1.b = p2;
    line2.a = p3; line2.b = p4;

    if(isInter(line1, line2)){
        cout<<"YES"<<endl;
    } else {
        cout<<"NO"<<endl;
    }

}


signed main(){
    fastio;
	int t=1; cin>>t;
	while(t--) solve();
}