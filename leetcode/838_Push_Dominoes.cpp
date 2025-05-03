/*
Question: 838. Push Dominoes
Link: https://leetcode.com/problems/push-dominoes
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
        string pushDominoes(string dominoes) {
            int len = dominoes.length();
            vector<pair<char,int>> v1(len,{'.',0}), v2(len,{'.',0});
            string ans = "";
            char now = '.'; int cnt = 0;
            for(int i=0;i<len;i++) {
                if(dominoes[i] == 'L' || dominoes[i] == 'R') {
                    cnt = 0;
                    now = dominoes[i];
                    v1[i] = make_pair(now, cnt);
                } else if(now == 'R') {
                    v1[i] = make_pair(now, ++cnt);
                } else {
                    cnt = 0;
                    now = '.';
                    v1[i] = make_pair(now, cnt);
                }
            }
            now = '.'; cnt = 0;
            for(int i=len-1;i>=0;i--) {
                if(dominoes[i] == 'L' || dominoes[i] == 'R') {
                    cnt = 0;
                    now = dominoes[i];
                    v2[i] = make_pair(now, cnt);
                } else if(now == 'L') {
                    v2[i] = make_pair(now, ++cnt);
                } else {
                    cnt = 0;
                    now = '.';
                    v2[i] = make_pair(now, cnt);
                }
            }
            for(int i=0;i<len;i++) {
                if(dominoes[i] == 'L' || dominoes[i] == 'R') {
                    ans+=dominoes[i];
                } else if((v1[i].first=='L' && v2[i].first=='R')||(v1[i].first=='R' && v2[i].first=='L')) {
                    if(v1[i].second < v2[i].second) {
                        ans += v1[i].first;
                    } else if(v1[i].second > v2[i].second){
                        ans += v2[i].first;
                    } else {
                        ans += '.';
                    }
                } else {
                    ans += (v1[i].first=='.') ? v2[i].first: v1[i].first;
                }
            }
            return ans;
        }
    };

/*
.L.R...LR..L..
.L.RRRRLRRRL..
00001230012000
LL.RLLLLRLLL..
10003210021000
LL.RR.LLRRLL..
*/