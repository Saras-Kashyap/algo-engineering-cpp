/* * ID: 104
 * Title: Maximum Depth of Binary Tree
 * Difficulty: Easy
 */
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Required for std::max

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        // Base case: if the node is null, depth is 0
        if (!root) return 0;
        
        // Recursively find the depth of the left and right subtrees
        int left_depth = maxDepth(root->left);
        int right_depth = maxDepth(root->right);
        
        // The max depth at this current node is the greater of the two subtrees, plus 1 for itself
        return std::max(left_depth, right_depth) + 1;
    }
};