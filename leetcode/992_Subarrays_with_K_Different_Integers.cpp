/*
Question: 992. Subarrays with K Different Integers
Link: https://leetcode.com/problems/subarrays-with-k-different-integers
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
        int subarraysWithKDistinct(vector<int>& nums, int k) {
            int ret=0, diff=0;
            vector<int> v(20005,0);
            for(int l=0,mid=0,r=0; r<nums.size();r++) {
                if(++v[nums[r]] == 1) {
                    if(k < ++diff) {
                        v[nums[mid++]] = 0;
                        diff--;
                        l = mid;
                    }
                }
                if( k==diff ) {
                    while(v[nums[mid]]>1) {
                        v[nums[mid++]]--;
                    }
                    ret += mid - l + 1;
                }
            }
            return ret;
        }
    };

