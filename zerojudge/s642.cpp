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
const double PI = 3.14159265358979323846;
const double EPS = 1e-9;
const int xx[8] = {0,1,0,-1,1,1,-1,-1};
const int yy[8] = {1,0,-1,0,1,-1,-1,1};

void pmod(ll &a, ll b) { a = ((a + b) % MOD + MOD) % MOD; }
void mmod(ll &a, ll b) { a = ((a - b) % MOD + MOD) % MOD; }
void tmod(ll &a, ll b) { a = (a * b) % MOD; }
ll POW(ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define pii pair<int,int>
#define pll pair<ll, ll>

#ifdef LOCAL
template<class T, class = void>
struct is_container : false_type {};
template<class T>
struct is_container<T, void_t<decltype(begin(declval<T>()))>> : true_type {};

template<class A, class B>
ostream& operator<<(ostream& os, const pair<A,B>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template<class T, enable_if_t<is_container<T>::value && !is_same<T, string>::value, int> = 0>
ostream& operator<<(ostream& os, const T& v) {
    os << "{";
    bool first = true;
    for (auto& x : v) {
        if (!first) os << ", ";
        os << x;
        first = false;
    }
    return os << "}";
}

template<class... T> void dbg(T...x) {
    char e{};
    ((cerr << e << x, e = ' '), ...);
}
#define debug(...) dbg(#__VA_ARGS__, '=', __VA_ARGS__, '\n')
#else
#define debug(...) ((void)0)
#endif

template < class T > // O(N^3) , N <= 800
T KM ( const vector < vector <T > > & w ) {
    const int n = siz(w);
    vector <T > lx ( n ) , ly ( n ) ;
    vector <int > mx (n , -1) , my (n , -1) , pa ( n ) ;
    auto aug = [&]( int y ) {
        for (int x , z ; y != -1; y = z ) {
            x = pa [ y ]; z = mx [ x ];
            my [ y ] = x ; mx [ x ] = y ;
        }
    };
    auto bfs = [&]( int s ) {
        vector <T > sy (n , inf <T >) ;
        vector <bool > vx ( n ) , vy ( n ) ;
        queue <int > q ;
        q . push ( s ) ;
        while ( true ) {
            while ( q . size () ) {
                int x = q . front () ; q . pop () ;
                vx [ x ] = 1;
                for ( int y = 0; y < n ; y ++) {
                    if ( vy [ y ]) continue ;
                    T d = lx [ x ] + ly [ y ] - w [ x ][ y ];
                    if ( d == 0) {
                        pa [ y ] = x ;
                        if ( my [ y ] == -1)
                            return aug ( y ) ;
                        vy [ y ] = 1;
                        q . push ( my [ y ]) ;
                    } else if ( chmin ( sy [ y ] , d ) ) {
                        pa [ y ] = x ;
                    }
                }
            } /* SPLIT - HASH */
            T cut = inf <T >;
            for (int y = 0; y < n ; y ++)
                if (! vy [ y ])
                    chmin ( cut , sy [ y ]) ;
            for (int j = 0; j < n ; j ++) {
                if ( vx [ j ]) lx [ j ] -= cut ;
                if ( vy [ j ]) ly [ j ] += cut ;
                else sy [ j ] -= cut ;
            }
            for (int y = 0; y < n ; y ++)
            if (! vy [ y ] and sy [ y ] == 0) {
                if ( my [ y ] == -1)
                    return aug ( y ) ;
                vy [ y ] = 1;
                q . push ( my [ y ]) ;
            }
        }
    };
    for (int x = 0; x < n ; x ++)
        lx [ x ] = *max_element(ALL(w[x]));
    for (int x = 0; x < n ; x ++)
        bfs ( x ) ;
    T ans = 0;
    for (int x = 0; x < n ; x ++)
        ans += w [ x ][ mx [ x ]];
    return ans ;
}
void solve() {
    int n; cin>>n;
    vec<vec<int>> v(n, vec<int>(n));
    for(auto &i: v) {
        for(auto &j: i) {
            cin>>j;
            j = -j;
        }
    }
    cout<<-KM(v)<<endl;
}


int main() {
    fastio;
    int t = 1; //cin >> t;
    while (t--) solve();
}