/*
Question: 2140. Solving Questions With Brainpower
Link: https://leetcode.com/problems/solving-questions-with-brainpower
*/

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

template <class T> bool chmax(T &a, T b) { return (a < b and (a = b, true)); }

static int x = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

class Solution {
    public:
        long long mostPoints(vector<vector<int>>& questions) {
            long long dp[questions.size()+1];
            memset(dp, 0, sizeof(dp));
            for(int i=questions.size()-1;i>=0;i--) {
                if(i+questions[i][1]+1<questions.size()) {
                    chmax(dp[i], questions[i][0]+dp[i+questions[i][1]+1]);
                } else {
                    dp[i] = questions[i][0];
                }
                chmax(dp[i],dp[i+1]);
            }
            return dp[0];
        }
    };