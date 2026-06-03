#include <gtest/gtest.h>
#include "graphs/0127_word_ladder.hpp"

// Test Case 1: Standard LeetCode Example 1 (Valid Transformation)
TEST(WordLadderTest, StandardValidPath) {
    Solution sol;
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    
    EXPECT_EQ(sol.ladderLength(beginWord, endWord, wordList), 5);
}

// Test Case 2: Standard LeetCode Example 2 (Target missing from wordList)
TEST(WordLadderTest, TargetMissingFromDictionary) {
    Solution sol;
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {"hot", "dot", "dog", "lot", "log"};
    
    EXPECT_EQ(sol.ladderLength(beginWord, endWord, wordList), 0);
}

// Test Case 3: Immediate Neighbor (Only 1 character difference directly to target)
TEST(WordLadderTest, DirectOneStepTransformation) {
    Solution sol;
    std::string beginWord = "hit";
    std::string endWord = "hot";
    std::vector<std::string> wordList = {"hot"};
    
    EXPECT_EQ(sol.ladderLength(beginWord, endWord, wordList), 2);
}

// Test Case 4: Dead End (Words exist, but no single-letter bridge connects them)
TEST(WordLadderTest, DeadEndNoValidPath) {
    Solution sol;
    std::string beginWord = "a";
    std::string endWord = "c";
    std::vector<std::string> wordList = {"b", "z", "c"}; 
    // "a" can go to "b" or "z", but let's say "b" and "z" can't reach "c" due to length or letters
    // A clearer example:
    std::string begin2 = "talk";
    std::string end2 = "moon";
    std::vector<std::string> list2 = {"tall", "tank", "moon"};
    
    // "talk" -> "tall" or "tank", but neither can transform into "moon"
    EXPECT_EQ(sol.ladderLength(begin2, end2, list2), 0);
}

// Test Case 5: Circular Dependency / Graph Cycles
// Ensures your code properly flags words as visited and doesn't loop infinitely
TEST(WordLadderTest, HandlesGraphCycles) {
    Solution sol;
    std::string beginWord = "cat";
    std::string endWord = "dog";
    // cat -> bat -> bit -> bot -> dot -> dog (but bat/cat can loop)
    std::vector<std::string> wordList = {"bat", "car", "bit", "bot", "dot", "dog"};
    
    EXPECT_EQ(sol.ladderLength(beginWord, endWord, wordList), 6);
}

// Test Case 6: Multiple Paths of Different Lengths (Must pick the shortest)
TEST(WordLadderTest, ChoosesShortestPath) {
    Solution sol;
    std::string beginWord = "dig";
    std::string endWord = "dog";
    // Path 1 (Short): dig -> dog (2 steps)
    // Path 2 (Long):  dig -> big -> bog -> dog (4 steps)
    std::vector<std::string> wordList = {"big", "bog", "dog"};
    
    EXPECT_EQ(sol.ladderLength(beginWord, endWord, wordList), 2);
}