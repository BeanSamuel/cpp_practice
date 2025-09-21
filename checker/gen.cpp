// gen.cpp
// Usage:
//   ./gen T NMAX SEED MODE
//   T: number of testcases to produce (default 100)
//   NMAX: maximum n for each test (default 50)
//   SEED: random seed (default time-based)
//   MODE: 0 = balanced mix (default), 1 = more edge cases
//
// Output: prints T testcases in the problem format
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = (argc >= 2 ? atoi(argv[1]) : 100);
    int NMAX = (argc >= 3 ? atoi(argv[2]) : 50);
    unsigned long long seed = (argc >= 4 ? (unsigned long long)stoull(argv[3]) : (unsigned long long)chrono::high_resolution_clock::now().time_since_epoch().count());
    int MODE = (argc >= 5 ? atoi(argv[4]) : 0);

    mt19937_64 rng(seed);
    auto randint = [&](int L, int R){ return uniform_int_distribution<int>(L,R)(rng); };
    auto bern = [&](double p){ return (uniform_real_distribution<double>(0,1)(rng) < p); };

    cout << T << "\n";
    for(int ti=0; ti<T; ++ti){
        // choose n
        int n;
        if(MODE==1){
            // more edge: sometimes large near NMAX, sometimes tiny
            int r = randint(1,100);
            if(r <= 10) n = 1;
            else if(r <= 30) n = randint(2,5);
            else if(r <= 70) n = randint(6, min(NMAX,100));
            else n = randint(max(1,NMAX/2), NMAX);
        } else {
            // balanced
            n = randint(1, NMAX);
        }

        string s(n, '0');

        // decide pattern type
        int pat;
        if(MODE==1){
            // bias toward tricky patterns
            int x = randint(1,100);
            if(x<=20) pat = 0;           // all zeros / ones
            else if(x<=40) pat = 1;      // alternating
            else if(x<=65) pat = 2;      // long runs of zeros/ones
            else if(x<=80) pat = 3;      // single zeros among ones
            else pat = 4;                // random with bias
        } else {
            pat = randint(0,4);
        }

        if(pat==0){
            // all zeros or all ones
            if(bern(0.5)) s = string(n,'0'); else s = string(n,'1');
        } else if(pat==1){
            // alternating 0101... or 1010...
            bool start = bern(0.5);
            for(int i=0;i<n;i++) s[i] = ((i+start)%2 ? '1' : '0');
        } else if(pat==2){
            // long runs: create 2-4 segments with random lengths
            int segs = randint(1, min(4, n));
            int left = n;
            vector<int> lens;
            for(int i=0;i<segs;i++){
                if(i==segs-1) lens.push_back(left);
                else {
                    int take = randint(1, max(1, left-(segs-i-1)));
                    lens.push_back(take);
                    left -= take;
                }
            }
            bool cur = bern(0.5);
            int idx = 0;
            for(int L: lens){
                for(int k=0;k<L;k++) s[idx++] = (cur ? '1' : '0');
                cur = !cur;
            }
        } else if(pat==3){
            // single zeros inside ones or single ones inside zeros, scattered
            s = string(n, '1');
            int singles = max(1, n/10);
            for(int k=0;k<singles;k++){
                int pos = randint(0,n-1);
                s[pos] = '0';
            }
            // also add some contiguous zeros occasionally
            if(bern(0.3)){
                int a = randint(0,n-1), b = min(n-1, a+randint(1, max(1,n/10)));
                for(int i=a;i<=b;i++) s[i] = '0';
            }
        } else {
            // random with some bias
            double p1 = (MODE==1 ? 0.4 : uniform_real_distribution<double>(0.0,1.0)(rng));
            for(int i=0;i<n;i++) s[i] = (bernoulli_distribution(p1)(rng) ? '1' : '0');
            // sprinkle some crafted traps: patterns "010" "101" "0110" etc
            if(n >= 3 && bern(0.2)){
                int st = randint(0,n-3);
                string trap;
                int pick = randint(0,3);
                if(pick==0) trap = "010";
                else if(pick==1) trap = "101";
                else if(pick==2) trap = "0110";
                else trap = "1001";
                for(int i=0;i<(int)trap.size() && st+i<n;i++) s[st+i] = trap[i];
            }
        }

        // final sanity: ensure length n
        if((int)s.size() != n) s.resize(n,'0');

        cout << n << "\n" << s << "\n";
    }

    // Print seed to stderr so runs are reproducible
    cerr << "gen finished. seed=" << seed << " T=" << T << " NMAX=" << NMAX << " MODE=" << MODE << "\n";
    return 0;
}
