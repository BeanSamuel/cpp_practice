/*
Question: 2176. Count Equal and Divisible Pairs in an Array
Link: https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array
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
        int countPairs(vector<int>& nums, int k) {
            map<int, vector<int>> mp;
            for(int i=0;i<nums.size();i++) mp[nums[i]].emplace_back(i);
            int ans = 0;
            for(auto [num,v]:mp) {
                for(int i=0;i<v.size();i++) {
                    for(int j=i+1;j<v.size();j++) {
                        if((v[i]*v[j])%k == 0) ans++;
                    }
                }
            }
            return ans;
        }
    };