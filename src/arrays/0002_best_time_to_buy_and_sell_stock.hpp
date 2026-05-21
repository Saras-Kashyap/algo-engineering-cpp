/*
 * ID: 0002
 * Title: Best Time to Buy and Sell Stock
 * Difficulty: Easy
 * Companies: Amazon, Microsoft, Goldman Sachs, Bloomberg
 */

#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_price = 2147483647; // Max possible int value
        int max_profit = 0;
        
        for (int i = 0; i < prices.size(); i++) {
            if (prices[i] < min_price) {
                min_price = prices[i];
            } else if (prices[i] - min_price > max_profit) {
                max_profit = prices[i] - min_price;
            }
        }
        return max_profit;
    }
};