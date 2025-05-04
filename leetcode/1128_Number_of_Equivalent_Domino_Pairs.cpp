/*
Question: 1128. Number of Equivalent Domino Pairs
Link: https://leetcode.com/problems/number-of-equivalent-domino-pairs
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
        int numEquivDominoPairs(vector<vector<int>>& dominoes) {
            vector<int> v(100,0);
            for(auto i:dominoes) v[max(i[0],i[1])*10+min(i[0],i[1])]++;   
            int ans = 0;
            for(int i:v) {
                ans += (i * (i-1))>>1;
            }
            return ans;
        }
    };