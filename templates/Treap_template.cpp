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

struct Node {
    int val;              // 當前值
    int priority;         // Treap 用的隨機優先度
    int size;             // 子樹大小
    long long sum;        // 子樹總和 (可改成 max/min 之類)
    
    //懶標
    bool rev;             // 是否翻轉
    bool assignFlag;      // 是否整段賦值
    ll add;        // 是否整段加值
    ll assignVal;  // 賦值的數字

    Node *l, *r;          // 左右子樹

    Node(int v) : val(v), priority(rand()), size(1), sum(v), rev(false), assignFlag(false), add(0), assignVal(0), l(nullptr), r(nullptr){}
};

int getSize(Node *t) { return t ? t->size : 0; }
ll getSum(Node *t) { return t ? t->sum : 0; }

void push(Node* t) {
    if (!t) return;

    // (1) 賦值 lazy
    if (t->assignFlag) {
        t->val = t->assignVal;
        t->sum = 1LL * t->assignVal * getSize(t);

        // 傳給小孩
        if (t->l) {
            t->l->assignFlag = true;
            t->l->assignVal = t->assignVal;
            t->l->add = 0;
        }
        if (t->r) {
            t->r->assignFlag = true;
            t->r->assignVal = t->assignVal;
            t->r->add = 0;
        }
        t->assignFlag = false;
    }

    // (2) 加值 lazy
    if (t->add != 0) {
        t->val += t->add;
        t->sum += 1LL * t->add * getSize(t);

        if (t->l) t->l->add += t->add;
        if (t->r) t->r->add += t->add;

        t->add = 0;
    }

    // (3) 翻轉 lazy
    if (t->rev) {
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
        t->rev = false;
    }
}

//從小孩更新自己
void pull(Node* t) {
    if (!t) return;
    push(t->l);
    push(t->r);
    t->size = 1 + getSize(t->l) + getSize(t->r);
    t->sum = t->val + getSum(t->l) + getSum(t->r);
}

//前 k 個 vs 其餘
void split(Node* t, int k, Node*& l, Node*& r) {
    if (!t) { l = r = nullptr; return; }
    push(t); // 先把懶標記處理掉

    if (getSize(t->l) >= k) {
        split(t->l, k, l, t->l);
        r = t;
    } else {
        split(t->r, k - getSize(t->l) - 1, t->r, r);
        l = t;
    }
    pull(t);
}

//合併兩棵 treap
Node* merge(Node* l, Node* r) {
    if (!l || !r) return l ? l : r;

    if (l->priority > r->priority) {
        push(l);
        l->r = merge(l->r, r);
        pull(l);
        return l;
    } else {
        push(r);
        r->l = merge(l, r->l);
        pull(r);
        return r;
    }
}

Node* build(const vector<int>& arr) {
    vector<Node*> stk;
    Node* root = nullptr;

    for (int v : arr) {
        Node* cur = new Node(v);
        Node* last = nullptr;

        while (!stk.empty() && stk.back()->priority < cur->priority) {
            last = stk.back();
            stk.pop_back();
        }
        cur->l = last;
        if (!stk.empty()) stk.back()->r = cur;
        else root = cur;
        stk.push_back(cur);
    }

    // 記得 pull 更新 size, sum
    function<void(Node*)> dfs = [&](Node* t) {
        if (!t) return;
        push(t);
        dfs(t->l);
        dfs(t->r);
        pull(t);
    };
    dfs(root);

    return root;
}


// 區間翻轉
void rangeReverse(Node*& root, int l, int r) {
    Node *t1, *t2, *t3;
    split(root, r, t1, t3);
    split(t1, l-1, t1, t2);
    if (t2) t2->rev ^= 1;
    root = merge(merge(t1, t2), t3);
}

// 區間加值
void rangeAdd(Node*& root, int l, int r, int val) {
    Node *t1, *t2, *t3;
    split(root, r, t1, t3);
    split(t1, l-1, t1, t2);
    if (t2) t2->add += val;
    root = merge(merge(t1, t2), t3);
}

// 區間賦值
void rangeAssign(Node*& root, int l, int r, int val) {
    Node *t1, *t2, *t3;
    split(root, r, t1, t3);
    split(t1, l-1, t1, t2);
    if (t2) {
        t2->assignFlag = true;
        t2->assignVal = val;
        t2->add = 0; // 賦值會覆蓋加值
    }
    root = merge(merge(t1, t2), t3);
}

// 區間交換 [l1..r1] <-> [l2..r2] (假設不重疊, 且 l1 <= r1 < l2 <= r2)
void rangeSwap(Node*& root, int l1, int r1, int l2, int r2) {
    Node *a, *b, *c, *d, *e;
    split(root, r2, d, e); 
    split(d, l2-1, c, d); 
    split(c, r1, b, c); 
    split(b, l1-1, a, b);
    root = merge(merge(merge(merge(a, d), c), b), e);
}

// 區間取代: 把 [l..r] 換成一段新的序列 seq
void rangeReplace(Node*& root, int l, int r, const vector<int>& seq) {
    Node *t1, *t2, *t3;
    split(root, r, t1, t3);
    split(t1, l-1, t1, t2);

    // 建立新 treap
    Node* newTreap = nullptr;
    for (int v : seq) newTreap = merge(newTreap, new Node(v));

    root = merge(merge(t1, newTreap), t3);
}

int getKth(Node* t, int k) {
    if (!t) return -1;
    push(t);

    int leftSize = getSize(t->l);

    if (k == leftSize + 1) return t->val;           // 剛好是 root
    else if (k <= leftSize) return getKth(t->l, k); // 在左子樹
    else return getKth(t->r, k - leftSize - 1);     // 在右子樹
}

//1-based
