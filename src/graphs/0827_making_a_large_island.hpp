/* * ID: 827
 * Title: Making A Large Island
 * Difficulty: Hard
 */
#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>

// Efficient I/O boilerplate
static const int fast_io = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}();

class DSU {
public:
    std::vector<int> parent;
    std::vector<int> size;

    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1); // Initially, every isolated cell is an island of size 1
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]); // Path compression
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            // Union by size
            if (size[root_i] < size[root_j]) {
                parent[root_i] = root_j;
                size[root_j] += size[root_i];
            } else {
                parent[root_j] = root_i;
                size[root_i] += size[root_j];
            }
        }
    }
};

class Solution {
public:
    int largestIsland(std::vector<std::vector<int>>& grid) {
        if (grid.empty()) return 0;
        
        int n = grid.size();
        DSU dsu(n * n);
        int max_area = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Step 1: Connect all adjacent 1s to form initial components
        for (std::size_t i = 0; i < grid.size(); ++i) {
            for (std::size_t j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 1) {
                    int index = i * n + j;
                    for (int k = 0; k < 4; ++k) {
                        int ni = i + dr[k];
                        int nj = j + dc[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] == 1) {
                            int n_index = ni * n + nj;
                            dsu.unite(index, n_index);
                        }
                    }
                    // Keep track of the max area in case the grid is entirely 1s
                    max_area = std::max(max_area, dsu.size[dsu.find(index)]);
                }
            }
        }

        // Step 2: Try flipping every '0' to '1' and calculate the potential combined area
        for (std::size_t i = 0; i < grid.size(); ++i) {
            for (std::size_t j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 0) {
                    std::unordered_set<int> neighbor_roots;
                    
                    // Collect unique roots of adjacent islands
                    for (int k = 0; k < 4; ++k) {
                        int ni = i + dr[k];
                        int nj = j + dc[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] == 1) {
                            neighbor_roots.insert(dsu.find(ni * n + nj));
                        }
                    }

                    int possible_area = 1; // Start with 1 for the flipped '0'
                    for (int root : neighbor_roots) {
                        possible_area += dsu.size[root];
                    }
                    
                    max_area = std::max(max_area, possible_area);
                }
            }
        }

        // If max_area is 0, it means the grid was all 0s, and flipping one gives an area of 1
        return max_area == 0 ? 1 : max_area;
    }
};