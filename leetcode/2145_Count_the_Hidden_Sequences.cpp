/*
Question: 2145. Count the Hidden Sequences
Link: https://leetcode.com/problems/count-the-hidden-sequences
*/

#include <bits/stdc++.h>

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
        int numberOfArrays(vector<int>& differences, int lower, int upper) {
            long long mx=0, mn=0, counter=0;
            for(int i=0;i<differences.size();i++) {
                counter += differences[i];
                chmax(mx, counter);
                chmin(mn, counter);
            }
            return max(0LL, upper - lower - mx + mn + 1);
        }
    };