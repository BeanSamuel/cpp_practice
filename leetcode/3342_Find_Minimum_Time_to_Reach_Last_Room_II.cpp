/*
Question: 3342. Find Minimum Time to Reach Last Room II
Link: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii
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
        int minTimeToReach(vector<vector<int>>& moveTime) {
            int n = moveTime.size(), m = moveTime[0].size();
            vector<vector<int>> v(n, vector<int>(m, INT_MAX)); 
            priority_queue<pair<int, pair<pair<int,int>,int>>, vector<pair<int, pair<pair<int,int>,int>>>, greater<pair<int, pair<pair<int,int>,int>>>> pq;
            v[0][0] = 0;
            pq.push({0,{{0,0},1}});
            while(!pq.empty()) {
                auto [d,u] = pq.top();
                pair<int,int> pos = u.first;
                int next_step = u.second;
                pq.pop();
                if( d > v[pos.first][pos.second]) continue;
                const int xx[4] = {0,1,0,-1}; const int yy[4] = {1,0,-1,0};
                for(int i=0;i<4;i++) {
                    int nextx = pos.first+xx[i], nexty = pos.second+yy[i];
                    if((0<=nextx&&nextx<n)&&(0<=nexty&&nexty<m)){
                        int tmp = v[pos.first][pos.second] + max(next_step, moveTime[nextx][nexty] - v[pos.first][pos.second]+next_step);
                        if(tmp < v[nextx][nexty]){
                            v[nextx][nexty] = tmp;
                            pq.push({tmp, {{nextx,nexty}, (next_step==1)?2:1}});
                        }
                    }
                }
            }
            
            return v[n-1][m-1];
        }
    };