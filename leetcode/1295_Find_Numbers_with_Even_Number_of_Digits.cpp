/*
Question: 1295. Find Numbers with Even Number of Digits
Link: https://leetcode.com/problems/find-numbers-with-even-number-of-digits
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
        int findNumbers(vector<int>& nums) {
            int ret = 0;
            for(int i:nums) {
                if(to_string(i).length()&1==0) ret++;
            }
            return ret;
        }
    };