/*
Question: 2962. Count Subarrays Where Max Element Appears at Least K Times
Link: https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times
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
        long long countSubarrays(vector<int>& nums, int k) {
            int mx = -1;
            for(int i:nums) chmax(mx, i);
            int l = 0, r = 0, now = 0;
            long long ret = 0;
            for(r=0;r<nums.size();r++) {
                if(nums[r] == mx) now++;
                while(now == k) {
                    ret += nums.size() - r;
                    if(nums[l] == mx) now--;
                    l++;
                }
            }
            return ret;
        }
    };