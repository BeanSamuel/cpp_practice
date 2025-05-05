/*
Question: 790. Domino and Tromino Tiling
Link: https://leetcode.com/problems/domino-and-tromino-tiling
*/

#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

template <class T> bool chmax(T &a, T b) { return (a < b and (a = b, true)); }
template <class T> bool chmin(T &a, T b) { return (b < a and (a = b, true)); }

static int x = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

class Solution {
    public:
        int numTilings(int n) {
            int MOD = 1000000007;
            if(n==1) return 1;
            if(n==2) return 2;
            vector<int> dp(n+1, 0);
            dp[0] = 1;
            dp[1] = 1;            
            dp[2] = 2;
            for(int i=3;i<=n;i++) {
                dp[i] = ((dp[i-1]<<1)%MOD + dp[i-3])%MOD;
            }
            return dp[n];
        }
    };