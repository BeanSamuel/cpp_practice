/*
Question: 2094. Finding 3-Digit Even Numbers
Link: https://leetcode.com/problems/finding-3-digit-even-numbers
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
        vector<int> findEvenNumbers(vector<int>& digits) {
            vector<int> ret;
            vector<short> v(10,0);
            for(int i:digits) v[i]++;
            for(short i=100;i<1000;i+=2) {
                short a = i/100, b = (i/10)%10, c = i%10;
                v[a]--; v[b]--; v[c]--;
                if(v[a]>=0&&v[b]>=0&&v[c]>=0 ) ret.emplace_back(i);
                v[a]++; v[b]++; v[c]++;
            }
            return ret;
        }
    };