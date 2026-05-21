#include <gtest/gtest.h>
#include "arrays/0121_best_time_to_buy_and_sell_stock.hpp"

TEST(BestTimeToBuyAndSellStockTest, HandlesStandardCase) {
    Solution sol;
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    EXPECT_EQ(sol.maxProfit(prices), 5); // Buy at 1, sell at 6
}

TEST(BestTimeToBuyAndSellStockTest, HandlesNoProfitCase) {
    Solution sol;
    vector<int> prices = {7, 6, 4, 3, 1};
    EXPECT_EQ(sol.maxProfit(prices), 0); // Price only drops, no transactions done
}