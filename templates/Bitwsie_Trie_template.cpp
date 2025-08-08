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
#define pll pair<ll, ll>

using namespace std;

class BitwiseTrie { //lowbit -> highbit
    static const int MAX_BIT = 31; //32-bit;
    struct Node {
        Node* nxt[2];
        int cnt;
        Node() : nxt{nullptr, nullptr}, cnt(0) {}
    };
    Node* root;
public:
    BitwiseTrie() { root = new Node(); }

    void insert( int x ) {
        Node* cur = root;
        for(int i=MAX_BIT; i>=0; i--) {
            int b = (x>>i) & 1;
            if(!cur->nxt[b]) cur->nxt[b] = new Node();
            cur = cur->nxt[b];
            cur->cnt++;
        }
    }

    void erase( int x ) {
        Node* cur = root;
        vec<Node*> path;
        for(int i=MAX_BIT; i>=0 ;i--) {
            int b = (x>>i) & 1;
            path.EB(cur);
            if(!cur->nxt[b]) return;
            cur = cur->nxt[b];
        } 
        path.EB(cur);
        for (int i=MAX_BIT; i>=0; i--) {
            int b = (x >> i) & 1;
            path[i+1]->cnt--;
            if (path[i+1]->cnt == 0) {
                delete path[i]->nxt[b];
                path[i]->nxt[b] = nullptr;
            }
        }
    }

    int query_max( int x ) { // 找x^y 的最大值
        Node* cur = root;
        int ret = 0;
        for(int i = MAX_BIT; i>=0; i--) {
            int b = (x>>i) & 1;
            if(cur->nxt[!b]) {
                ret |= (1<<i);
                cur = cur->nxt[!b];
            } else if(cur->nxt[b]){
                cur = cur->nxt[b];
            } else {
                break;
            }
        }
        return ret;
    }

    int query_min( int x ) { // 找x^y 的最小值
        Node* cur = root;
        int ret = 0;
        for(int i=MAX_BIT; i>=0 ;i--) {
            int b = (x>>i) & i;
            if(cur->nxt[b]) {
                cur = cur->nxt[b];
            } else if(cur->nxt[!b]) {
                ret |= (1<<b);
                cur = cur->nxt[!b];
            } else {
                break;
            }
        }
        return ret;
    }

}