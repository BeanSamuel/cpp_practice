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
template <class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
const ll MXN = (ll)1e18;

void solve() {
    int n; cin >> n;
    ll h[1000][1000];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> h[i][j];
        }
    }        
    ll a[1000], b[1000];
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[j];

    bool allowX[1000][2][2];
    
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                allowX[i][j][k] = true;
            }
        }
    }
                
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n; j++) {
            ll delta = h[i][j] - h[i+1][j];
            if (delta == 0) { allowX[i][0][0] = false; allowX[i][1][1] = false; }
            else if (delta == 1) allowX[i][0][1] = false;
            else if (delta == -1) allowX[i][1][0] = false;
        }
    }

    for(int i=0;i<n-1;i++) {
        bool chk = false;
        for(int j=0;j<2;j++) {
            for(int k=0;k<2;k++) {
                chk |= allowX[i][s][t];
            }
        }
        if (!chk) { cout << -1 << endl; return; }
    }

    ll dpX[1000][2];

    for (int i = 0; i < n; i++) dpX[i][0] = dpX[i][1] = MXN;
    dpX[0][0] = 0;
    dpX[0][1] = a[0];
    
    for (int i = 0; i < n-1; i++) {
        ll nxt[2] = {MXN, MXN};
        for (int s = 0; s < 2; s++) if (dpX[i][s] < MXN)
            for (int t = 0; t < 2; t++) if (allowX[i][s][t])
                chmin(nxt[t], dpX[i][s] + (t ? a[i+1] : 0));
        dpX[i+1][0] = nxt[0];
        dpX[i+1][1] = nxt[1];
    }
    ll ansX = min(dpX[n-1][0], dpX[n-1][1]);
    if (ansX >= MXN) { cout << -1 << endl; return; }
    static bool allowY[1000][2][2];
    for (int j = 0; j < n-1; j++)
        for (int s = 0; s < 2; s++)
            for (int t = 0; t < 2; t++)
                allowY[j][s][t] = true;
    for (int j = 0; j < n-1; j++)
        for (int i = 0; i < n; i++) {
            ll d = h[i][j] - h[i][j+1];
            if (d == 0) { allowY[j][0][0] = false; allowY[j][1][1] = false; }
            else if (d == 1) allowY[j][0][1] = false;
            else if (d == -1) allowY[j][1][0] = false;
        }
    for (int j = 0; j < n-1; j++) {
        bool any = false;
        for (int s = 0; s < 2; s++)
            for (int t = 0; t < 2; t++)
                any |= allowY[j][s][t];
        if (!any) { cout << -1 << endl; return; }
    }
    static ll dpY[1000][2];
    for (int i = 0; i < n; i++) dpY[i][0] = dpY[i][1] = MXN;
    dpY[0][0] = 0;
    dpY[0][1] = b[0];
    for (int j = 0; j < n-1; j++) {
        ll nxt[2] = {MXN, MXN};
        for (int s = 0; s < 2; s++) if (dpY[j][s] < MXN)
            for (int t = 0; t < 2; t++) if (allowY[j][s][t])
                chmin(nxt[t], dpY[j][s] + (t ? b[j+1] : 0));
        dpY[j+1][0] = nxt[0];
        dpY[j+1][1] = nxt[1];
    }
    ll ansY = min(dpY[n-1][0], dpY[n-1][1]);
    if (ansY >= MXN) { cout << -1 << endl; return; }
    cout << ansX + ansY << endl;
}

int main() {
    fastio;
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
