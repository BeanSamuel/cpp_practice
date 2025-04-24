/*
Question: 2799. Count Complete Subarrays in an Array
Link: https://leetcode.com/problems/count-complete-subarrays-in-an-array
*/

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")
#define ALL(x) (x).begin(), (x).end()

template <class T> bool chmax(T &a, T b) { return (a < b and (a = b, true)); }
template <class T> bool chmin(T &a, T b) { return (b < a and (a = b, true)); }

static int x = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

class Solution {
    public:
        int countCompleteSubarrays(vector<int>& nums) {
            int k = unordered_set<int> (ALL(x)).size();
            unordered_map<int, int> mp;
            int l = 0, ret = 0;
            for(int i=0;i<nums.size();i++){
                mp[nums[i]]++;
                while(mp.size() == k){
                    res += nums.size() - i;
                    mp[nums[l]]--;
                    if(mp[nums[l]]==0) mp.erase(nums[l]);
                    l++;
                }
            }
            return ret;
        }
    };