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

class Trie {
    static const int ALPHABET_SIZE = 26;
    struct Node {
        Node* next[ALPHABET_SIZE];
        int sz; //有多少字串的前綴包括此節點
        int cnt; //是否存在某個特定字串
        int mx = 0;
        string mx_s= "";
        Node() : sz(0), cnt(0) {
            fill(next, next + ALPHABET_SIZE, nullptr);
        }
    };
    Node* root;
public:
    Trie() { root = new Node; }
    ~Trie() { clear(root); }
    
    void insert( string& word ) {
        Node* cur = root;
        for(char c : word) {
            int idx = c-'a';
            if( !cur->next[idx] ) cur->next[idx] = new Node();
            cur = cur->next[idx];
            cur->sz++;
        }
        cur->cnt++;
    }

    void generateAnswer() {
        auto dfs = [&](auto self, Node* node, string& path) -> void {
            if(node->cnt>0) {
                node->mx = node->cnt;
                node->mx_s = path;
            } else {
                node->mx = 0;
                node->mx_s = "";
            }
            for(int i=0;i<ALPHABET_SIZE;i++) {
                if(node->next[i]) {
                    path.PB(char('a'+i));
                    self(self, node->next[i], path);
                    if(node->next[i]->mx > node->mx ||
                       (node->next[i]->mx == node->mx && node->next[i]->mx_s < node->mx_s)) {
                        node->mx = node->next[i]->mx;
                        node->mx_s = node->next[i]->mx_s;
                    }
                    path.pop_back();
                }
            }
        };
        string path = "";
        dfs(dfs,root,path);
    }

    pair<string, int> ans( string& prefix) {
        Node* cur = root;
        for(char c : prefix) {
            int idx = c - 'a';
            if( !cur->next[idx] ) return {"-1",0};
            cur = cur->next[idx];
        }
        return {cur->mx_s, cur->mx};
    }

    int countPrefix( string& prefix ) {
        Node* cur = root;
        for(char c : prefix) {
            int idx = c - 'a';
            if( !cur->next[idx] ) return 0;
            cur = cur->next[idx];
        }
        return cur->sz;
    }

    int countWord( string& word ) {
        Node* cur = root;
        for(char c : word) {
            int idx = c - 'a';
            if( !cur->next[idx] ) return 0;
            cur = cur->next[idx];
        }
        return cur->cnt;
    }

private:
    void clear(Node* node) {
        if(!node) return;
        for(int i=0;i<ALPHABET_SIZE;i++)
            clear(node->next[i]);
        delete node;
    }
};

void solve(){
    int n; cin>>n;
    Trie trie;
    for(int i=0;i<n;i++) {
        string s; cin>>s;
        trie.insert(s);
    }
    trie.generateAnswer();
    int q; cin>>q;
    while(q--) {
        string s; cin>>s;
        pair<string,int> ans = trie.ans(s);
        if(ans.F != "-1") cout<<ans.F<<" "<<ans.S<<endl;
        else cout<<"-1"<<endl;
    }
    
}


signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}