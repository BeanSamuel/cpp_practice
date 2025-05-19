/*
Question: 3024. Type of Triangle
Link: https://leetcode.com/problems/type-of-triangle
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
    string triangleType(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        if(nums[0]+nums[1]<=nums[2]) return "none";
        if(nums[0] == nums[1] && nums[1]==nums[2] ) return "equilateral";
        if(nums[0]==nums[1] || nums[1]==nums[2]) return "isosceles";
        return "scalene";
    }
};