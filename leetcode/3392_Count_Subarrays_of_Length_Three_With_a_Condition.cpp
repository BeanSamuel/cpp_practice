/*
Question: 3392. Count Subarrays of Length Three With a Condition
Link: https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition
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
        int countSubarrays(vector<int>& nums) {
            int ans = 0;
            for(int i=1;i<nums.size()-1;i++) {
                if(((nums[i+1] + nums[i-1])<<1) == nums[i] ) ans++;
            }
            return ans;
        }
    };