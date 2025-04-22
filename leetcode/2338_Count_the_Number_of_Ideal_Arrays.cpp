/*
Question: 2338. Count the Number of Ideal Arrays
Link: https://leetcode.com/problems/count-the-number-of-ideal-arrays
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
        const long long MOD = 1e9+7;
        long long mod_pow(long long x) {
            long long ret = 1;
            long long e = MOD - 2 ;
            while(e) {
                if(e&1) ret = ret * x % MOD;
                x = x * x % MOD;
                e >>= 1;
            }
            return ret;
        }

        int idealArrays(int n, int maxValue) {
            
            vector<vector<int>> divs(maxValue + 1);
            for(int i=1;i<=maxValue;i++) {
                for(int j=i<<1;j<=maxValue;j+=i) {
                    divs[j].emplace_back(i);
                }
            }
            
            const int Lmax = floor(log2(maxValue))+1;

            vector<long long> fact(n+1), invfact(n+1);
            fact[0] = 1;
            for(int i=1;i<=n;i++) fact[i] = fact[i-1] * i % MOD;
            invfact[n] = mod_pow(fact[n]);
            for(int i=n;i>0;i--) invfact[i-1] = invfact[i] * i % MOD;

            vector<long long> prev(maxValue+1, 1), cnt(Lmax+1, 0);
            cnt[1] = maxValue;

            for(int L=2;L<=Lmax;L++) {
                vector<long long> cur(maxValue+1, 0);
                for(int i=1;i<=maxValue;i++) {
                    for(int j:divs[i]) {
                        cur[i] = (cur[i] + prev[j]) % MOD;
                    }
                }
                long long sum = 0;
                for(int i=1;i<=maxValue;i++) {
                    sum = (sum + cur[i]) % MOD;
                }
                cnt[L] = sum;
                prev.swap(cur);
            }
            auto comb = [&](int a, int b) {
                if( b<0 || b>a ) return 0LL;
                return fact[a] * invfact[b] % MOD *invfact[a-b] % MOD;
            };
    
            long long ans = 0;

            for(int L=1;L<=Lmax;L++) {
                if(cnt[L] == 0) continue;
                long long ways = comb(n-1,L-1);
                ans = (ans + cnt[L] * ways) % MOD;
            }
            return ans;
        }
    };