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

class DSU {
    public:
        vec<int> f, sz;
        DSU(int n) {
            f.resize(n+1);
            sz.resize(n+1, 1);
            for(int i=0;i<=n;i++) f[i] = -1;
        }
        int find(int x) {
            if(f[x] == -1) f[x] = x;
            if(f[x] == x) return x;
            f[x] = find(f[x]);
            return f[x];
        }
        void merge(int x, int y) {
            x = find(x);
            y = find(y);
            if(x == y) return;
            if(sz[x]<sz[y]) swap(x,y);
            sz[x] += sz[y];
            f[y] = x;
        }
        bool is_connected() {
            int record = -1;
            int n = siz(f);
            for(int i=0;i<n;i++) {
                if(f[i] == -1) continue;
                int x = find(i);
                if( record < 0) record = x;
                else if(x != record) return false;  
            }
            return true;
        }
};

int check_parity(int x, int y) {
    return ((x/2) + (y/2))%2;
}

bool check_neighbor(int x, int y, int &n, vec<vec<char>>& board) {
    for(int i=4;i<8;i++) {
        int nx = x + xx[i];
        int ny = y + yy[i];
        if( nx<0 || nx>=n || ny<0 || ny>=n ) continue;
        if( board[nx][ny] == 'W') return true;
    }
    return false;
}

bool check_euler_path(int x, int y, int &n, vec<vec<char>>& board) {
    DSU dsu(n*n);
    vec<int> degree(n*n, 0);
    int count_odd = 0;
    int p = check_parity(x,y);

    int id = x*n+y;
    
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(check_parity(i,j) != p) continue;
            for(int k=4;k<8;k++) {
                int mid_x = i + xx[k];
                int mid_y = j + yy[k];
                if( mid_x<0 || mid_x>=n || mid_y<0 || mid_y>=n || board[mid_x][mid_y]!='W' ) continue;
                int nx = mid_x + xx[k];
                int ny = mid_y + yy[k];
                if( board[i][j] == 'B' || nx<0 || nx>=n || ny<0 || ny>=n || board[nx][ny]=='B' ) return false;
                
                if(0<=nx && nx<n && 0<=ny && ny<n && board[nx][ny] == '_') {
                    degree[i*n+j]++;
                    dsu.merge(i*n+j, nx*n+ny);
                }
            }
            if(degree[i*n+j]%2 == 1) count_odd++;
        }
    }
    if(!dsu.is_connected()) return false;
    return count_odd == 0 || (count_odd==2 && degree[id]%2==1);
}

void solve(){
    int n; cin>>n;
    vec<vec<char>> board(n, vec<char>(n));
    int row_odd=0, row_even=0, col_odd=0, col_even=0;

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin>>board[i][j];
            if(board[i][j] == 'W') {
                if(i%2==1) row_odd++;
                else row_even++;
                if(j%2==1) col_odd++;
                else col_even++;
            }
        }
    }
    if((row_odd>0 && row_even>0)||(col_odd>0 && col_even>0)) {
        cout<<"None"<<endl;
        return;
    }

    int solutions_found = 0;
    int sol_r = -1, sol_c = -1;
    for(int p=0;p<2;p++) {
        for(int i=0;i<n;i++) {
            bool found_in_this_parity = false;
            for(int j=0;j<n;j++) {
                if(board[i][j] == 'B' && check_parity(i,j)==p && check_neighbor(i,j,n,board)) {
                    board[i][j] = '_';
                    if(check_euler_path(i,j,n,board)) {
                        solutions_found++;
                        sol_r = i;
                        sol_c = j;
                    }
                    found_in_this_parity = true;
                    break; 
                }
            }
            if (found_in_this_parity) break;
        }
    }
    if (solutions_found == 0) cout << "None" << endl;
    else if (solutions_found == 1) cout << (char)('a' + sol_c) << (n - sol_r) << endl;
    else cout << "Multiple" << endl;
}



signed main(){
    fastio;
	int t=1; //cin>>t;
	while(t--) solve();
}