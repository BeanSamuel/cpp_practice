/*
Question: D. Merge Lists
Link: https://codeforces.com/group/jtU6D2hVEi/contest/105000/problem/D
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
 
void solve(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string s1; getline(fin, s1); s1+='\n';
    string s2; getline(fin, s2); s2+='\n';
    string s = "";
    vec<int> v1, v2;
    for(char c : s1) {
        if(c == '\n') {
            v1.EB(stoi(s));
            s = "";
            break;
        } else if( c == ' ' ) {
            v1.EB(stoi(s));
            s = "";
        } else {
            s+=c;
        }
    }
    for(auto c : s2) {
        if(c == '\n') {
            v2.EB(stoi(s));
            break;
        } else if( c == ' ') {
            v2.EB(stoi(s));
            s = "";
        } else {
            s+=c;
        }
    }
    int i=0, j=0;
    while(i<v1.size()&&j<v2.size()) {
        if(v1[i]<=v2[j]) fout<<v1[i++]<<" ";
        else fout<<v2[j++]<<" ";
    }
    while(i<v1.size()) {
        fout<<v1[i++]<<" ";
    }
    while(j<v2.size()) {
        fout<<v2[j++]<<" ";
    }
    fout<<endl;
}
 
signed main(){
    // fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}