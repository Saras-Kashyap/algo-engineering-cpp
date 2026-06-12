#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>
#include "graphs/721_accounts_merge.hpp" // Strictly pathed and lowercased

TEST(AccountsMergeTest, Example1) {
    Solution sol;
    std::vector<std::vector<std::string>> accounts = {
        {"John","johnsmith@mail.com","john_newyork@mail.com"},
        {"John","johnsmith@mail.com","john00@mail.com"},
        {"Mary","mary@mail.com"},
        {"John","johnnybravo@mail.com"}
    };
    
    std::vector<std::vector<std::string>> expected = {
        {"John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"},
        {"Mary","mary@mail.com"},
        {"John","johnnybravo@mail.com"}
    };

    auto result = sol.accountsMerge(accounts);
    
    // Sort outer vectors to ensure order-agnostic comparison
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    
    EXPECT_EQ(result, expected);
}

TEST(AccountsMergeTest, Example2) {
    Solution sol;
    std::vector<std::vector<std::string>> accounts = {
        {"Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"},
        {"Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"},
        {"Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"},
        {"Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"},
        {"Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"}
    };
    
    std::vector<std::vector<std::string>> expected = {
        {"Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"},
        {"Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"},
        {"Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"},
        {"Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"},
        {"Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"}
    };

    auto result = sol.accountsMerge(accounts);
    
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    
    EXPECT_EQ(result, expected);
}