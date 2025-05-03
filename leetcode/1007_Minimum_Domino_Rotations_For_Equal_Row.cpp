/*
Question: 1007. Minimum Domino Rotations For Equal Row
Link: https://leetcode.com/problems/minimum-domino-rotations-for-equal-row
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
        int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
            int ans = 100005, len = tops.size();
            for(int i=1;i<=6;i++) {
                int top_cnt = 0, bottom_cnt = 0;
                bool chk = true;
                for(int j=0;j<len;j++) {
                    if(!(tops[j]==i || bottoms[j]==i)) {
                        chk = false;
                        break;
                    }
                    if(tops[j]!=i) top_cnt++;
                    if(bottoms[j]!=i) bottom_cnt++;
                }
                if(chk) chmin(ans,min(top_cnt, bottom_cnt));
            }
            if(ans == 100005) ans = -1;
            return ans;
        }
    };

/*
[2,1,2,4,2,2]
1 1
2 4
3 0
4 1
5 0
6 0

[5,2,6,2,3,2]

*/