/*
Question: 2302. Count Subarrays With Score Less Than K
Link: https://leetcode.com/problems/count-subarrays-with-score-less-than-k
*/

#include <bits/stdc++.h>

#define ll long long
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
        long long countSubarrays(vector<int>& nums, long long k) {
            ll ret = 0, sum = 0;
            for(int l=0, r=0; r<nums.size(); r++) {
                sum += nums[r];
                while(l<=r && sum * (r-l+1) >=k) {
                    sum -= nums[l];
                    l++;
                }
                ret+=r-l+1;
            }
            return ret;
        }
    };