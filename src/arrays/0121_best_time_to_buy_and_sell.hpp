/*
 * ID: 121
 * Title: best time to buy and sell
 * Difficulty: Easy
 * Companies: 
 */

 #pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        
        int min_price = prices[0];
        int max_profit = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            min_price = min(min_price, prices[i]);
            max_profit = max(max_profit, prices[i] - min_price);
        }
        
        return max_profit;
    }
};