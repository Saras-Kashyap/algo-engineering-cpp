#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "graphs/0269_alien_dictionary.hpp"

// Test Case 1: Standard valid ordering with a single unique topological sort.
TEST(AlienDictionaryTest, ValidUniqueOrder1) {
    Solution sol;
    std::vector<std::string> words = {"baa", "abcd", "abca", "cab", "cad"};
    
    // Dependencies: b->d, d->a, a->c 
    // This creates a strict path: b -> d -> a -> c
    EXPECT_EQ(sol.alienOrder(words), "bdac");
}

// Test Case 2: Standard valid ordering with a single unique topological sort.
TEST(AlienDictionaryTest, ValidUniqueOrder2) {
    Solution sol;
    std::vector<std::string> words = {"caa", "aaa", "aab"};
    
    // Dependencies: c->a, a->b
    // Strict path: c -> a -> b
    EXPECT_EQ(sol.alienOrder(words), "cab");
}

// Test Case 3: Invalid dictionary due to cyclic dependencies.
TEST(AlienDictionaryTest, InvalidCyclicDependency) {
    Solution sol;
    std::vector<std::string> words = {"ab", "cd", "ef", "ad"};
    
    // Dependencies imply: a->e and e->a (cycle)
    EXPECT_EQ(sol.alienOrder(words), "");
}

// Test Case 4: Invalid dictionary due to prefix violations.
// If a longer word appears before a shorter word that is its exact prefix, it is invalid.
TEST(AlienDictionaryTest, InvalidPrefixOrder) {
    Solution sol;
    std::vector<std::string> words = {"abcd", "abc"};
    
    EXPECT_EQ(sol.alienOrder(words), "");
}

// Test Case 5: Edge case with only a single character.
TEST(AlienDictionaryTest, SingleCharacterEdgeCase) {
    Solution sol;
    std::vector<std::string> words = {"z"};
    
    EXPECT_EQ(sol.alienOrder(words), "z");
}

// Test Case 6: Edge case with identical words.
TEST(AlienDictionaryTest, IdenticalWordsEdgeCase) {
    Solution sol;
    std::vector<std::string> words = {"alien", "alien", "alien"};
    
    // Should extract the unique characters. The relative order among them 
    // doesn't have strict dependencies, but "a", "e", "i", "l", "n" are all in-degree 0.
    // To avoid flakiness from unordered_map, we just check that the size is correct.
    std::string result = sol.alienOrder(words);
    EXPECT_EQ(result.size(), 5);
}