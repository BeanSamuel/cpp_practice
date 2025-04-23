/*
Question: 1399. Count Largest Group
Link: https://leetcode.com/problems/count-largest-group
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
        int countLargestGroup(int n) {
            unordered_map<int,int> mp;
            int chk = 0;
            for(int i=1;i<=n;i++) {
                int tmp = i, sm = 0;
                while(tmp>0) {
                    sm += tmp%10;
                    tmp /= 10;
                }
                mp[sm]++;
                chmax(chk, mp[sm]);
            }
            int ret=0;
            for(auto i:mp) {
                if(i.second ==chk) ret++;
            }
            return ret;
        }
    };