/*
Question: 2. Add Two Numbers
Link: https://leetcode.com/problems/add-two-numbers/description/
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ret = l1;
        ListNode* prev = nullptr;
        int carry = 0;
        while( l1!=nullptr || l2!=nullptr || carry==1 ) {
            if( l1 == nullptr ) {
                l1 = new ListNode(0);
                prev->next = l1;
            }
            if( l2!=nullptr ) l1->val += l2->val;
            l1->val += carry;
            carry = l1->val/10;
            l1->val = l1-val%10;
            prev = l1;
            l1 = l1->next;
            if( l2!=nullptr ) l2 = l2->next;
        }
        return ret;
    }
};