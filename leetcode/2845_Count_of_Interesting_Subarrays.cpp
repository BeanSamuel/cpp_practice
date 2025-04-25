/*
Question: 2845. Count of Interesting Subarrays
Link: https://leetcode.com/problems/count-of-interesting-subarrays
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
        long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
            long long ret = 0;
            int cnt = 0;
            unordered_map<int,int> mp;
            mp[0] = 1LL;
            for(int i : nums) {
                if( i%modulo == k ) cnt ++;
                ret += mp[(cnt-k+modulo)%modulo];
                mp[cnt%modulo]++;
            }
            return ret;
        }
    };