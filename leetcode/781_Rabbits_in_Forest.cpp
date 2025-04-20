/*
Question: 781. Rabbits in Forest
Link: https://leetcode.com/problems/rabbits-in-forest
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
        int numRabbits(vector<int>& answers) {
            unordered_map<int,int> mp;
            for(int i:answers) mp[i]++;
            int ret = 0;
            for(auto i:mp) 
                ret += ceil((double)i.second / (i.first+1)) * (i.first+1);
            return ret;
        }
    };