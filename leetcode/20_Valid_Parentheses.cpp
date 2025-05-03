/*
Question: 20. Valid Parentheses
Link: https://leetcode.com/problems/valid-parentheses
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
        bool isValid(string s) {
            stack<char> st;
            for(char i:s) {
                if(st.empty()) {
                    st.push(i);
                    continue;
                }
                if(st.top() == '(' && i == ')') st.pop();
                else if(st.top() == '[' && i == ']') st.pop();
                else if(st.top() == '{' && i == '}') st.pop();
                else st.push(i);
            }
            return st.empty();
        }
    };