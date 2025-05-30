/*
Question: 1550. Three Consecutive Odds
Link: https://leetcode.com/problems/three-consecutive-odds
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
        bool threeConsecutiveOdds(vector<int>& arr) {
            short cnt = 0;
            for(int i:arr) {
                if(i&1) {
                    if(++cnt==3) return true;
                } else {
                    cnt = 0;
                }
            }
            return false;
        }
    };