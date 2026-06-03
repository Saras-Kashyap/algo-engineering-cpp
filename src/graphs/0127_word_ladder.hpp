/* * ID: 127
 * Title: Word Ladder
 * Difficulty: Hard
 */
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
        // Transfer words to a set for O(1) lookups and easy tracking of unvisited words
        std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
        
        // If the target word isn't even in the dictionary, no transformation is possible
        if (dict.find(endWord) == dict.end()) {
            return 0;
        }

        // Queue stores pairs of {current_word, current_step_count}
        std::queue<std::pair<std::string, int>> q;
        q.push({beginWord, 1});

        while (!q.empty()) {
            auto [word, steps] = q.front();
            q.pop();

            // If we reached the destination, return the total step count
            if (word == endWord) {
                return steps;
            }

            // Try mutating every character position of the current word
            for (std::size_t i = 0; i < word.length(); ++i) {
                char originalChar = word[i];

                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == originalChar) continue;

                    word[i] = c;

                    // If the mutated word is valid, queue it and erase to avoid revisiting
                    if (dict.find(word) != dict.end()) {
                        q.push({word, steps + 1});
                        dict.erase(word); 
                    }
                }
                
                // Backtrack to original state for the next character index mutation
                word[i] = originalChar;
            }
        }

        // If the queue is empty and we haven't returned, no path exists
        return 0;
    }
};