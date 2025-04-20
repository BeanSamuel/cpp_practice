/*
Question: 2563. Count the Number of Fair Pairs
Link: https://leetcode.com/problems/count-the-number-of-fair-pairs
*/

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

static int x = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

class Solution {
    public:
        long long countFairPairs(vector<int>& nums, int lower, int upper) {
            sort(nums.begin(),nums.end());
            long long ans = 0;
            for(int i=0 ; i<nums.size() ; i++) {
                auto l = lower_bound(nums.begin()+i+1, nums.end(), lower-nums[i]);
                auto r = upper_bound(nums.begin()+i+1, nums.end(), upper-nums[i]);
                ans += r - l;
            }
            return ans;
        }
    };
