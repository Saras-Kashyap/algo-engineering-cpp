/* * ID: 269
 * Title: Alien Dictionary
 * Difficulty: Hard
 */
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

class Solution {
public:
    std::string alienOrder(std::vector<std::string>& words) {
        std::unordered_map<char, std::unordered_set<char>> adj;
        std::unordered_map<char, int> in_degree;
        
        // 1. Initialize in_degree for all unique characters present in the words
        for (std::size_t i = 0; i < words.size(); ++i) {
            for (std::size_t j = 0; j < words[i].size(); ++j) {
                char c = words[i][j];
                in_degree[c] = 0; 
            }
        }
        
        // 2. Build the directed graph and calculate in-degrees
        for (std::size_t i = 0; i < words.size() - 1; ++i) {
            std::string word1 = words[i];
            std::string word2 = words[i + 1];
            
            // Edge Case: If word1 is longer than word2, and word2 is a prefix of word1, 
            // the dictionary order is invalid (e.g., "abcd" appearing before "abc").
            if (word1.size() > word2.size() && word1.substr(0, word2.size()) == word2) {
                return "";
            }
            
            // Find the first differing character to create a directed edge
            std::size_t len = std::min(word1.size(), word2.size());
            for (std::size_t j = 0; j < len; ++j) {
                if (word1[j] != word2[j]) {
                    char u = word1[j];
                    char v = word2[j];
                    
                    // Add edge u -> v if it hasn't been added yet
                    if (adj[u].find(v) == adj[u].end()) {
                        adj[u].insert(v);
                        in_degree[v]++;
                    }
                    break; // The remaining characters don't dictate order
                }
            }
        }
        
        // 3. Topological Sort (Kahn's Algorithm via BFS)
        std::queue<char> q;
        for (const auto& pair : in_degree) {
            if (pair.second == 0) {
                q.push(pair.first);
            }
        }
        
        std::string result = "";
        while (!q.empty()) {
            char current = q.front();
            q.pop();
            result += current;
            
            for (char neighbor : adj[current]) {
                in_degree[neighbor]--;
                if (in_degree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // 4. Cycle Check: If the result doesn't contain all unique characters, 
        // there is a cyclic dependency (invalid dictionary).
        if (result.size() != in_degree.size()) {
            return "";
        }
        
        return result;
    }
};