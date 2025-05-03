/*
Question: 14. Longest Common Prefix
Link: https://leetcode.com/problems/longest-common-prefix
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
        string longestCommonPrefix(vector<string>& strs) {
            sort(strs.begin(), strs.end());
            string a = strs.front(), b = strs.back();
            string ret = "";
            for(int i=0;i<a.length();i++) {
                if(a[i] != b[i]) return ret;
                ret += a[i];
            }
            return ret;
        }
    };