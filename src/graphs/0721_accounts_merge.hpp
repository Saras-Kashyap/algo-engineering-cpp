/* * ID: 721
 * Title: Accounts Merge
 * Difficulty: Medium
 */
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <numeric>

// Efficient I/O boilerplate
static const int fast_io = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}();

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
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
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

class Solution {
public:
    std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>>& accounts) {
        std::unordered_map<std::string, int> email_to_id;
        std::unordered_map<std::string, std::string> email_to_name;
        int id_counter = 0;

        // Step 1: Map each unique email to an integer ID and to its associated name
        for (std::size_t i = 0; i < accounts.size(); ++i) {
            const std::string& name = accounts[i][0];
            for (std::size_t j = 1; j < accounts[i].size(); ++j) {
                const std::string& email = accounts[i][j];
                if (email_to_id.find(email) == email_to_id.end()) {
                    email_to_id[email] = id_counter++;
                    email_to_name[email] = name;
                }
            }
        }

        // Step 2: Union emails belonging to the same account
        DSU dsu(id_counter);
        for (std::size_t i = 0; i < accounts.size(); ++i) {
            if (accounts[i].size() <= 1) continue; // Safety check for accounts with no emails
            const std::string& first_email = accounts[i][1];
            int first_id = email_to_id[first_email];
            
            for (std::size_t j = 2; j < accounts[i].size(); ++j) {
                const std::string& next_email = accounts[i][j];
                dsu.unite(first_id, email_to_id[next_email]);
            }
        }

        // Step 3: Group emails by their Disjoint Set root ID
        std::unordered_map<int, std::vector<std::string>> root_to_emails;
        for (auto it = email_to_id.begin(); it != email_to_id.end(); ++it) {
            const std::string& email = it->first;
            int id = it->second;
            int root = dsu.find(id);
            root_to_emails[root].push_back(email);
        }

        // Step 4: Format the result (Name followed by sorted emails)
        std::vector<std::vector<std::string>> merged_accounts;
        for (auto it = root_to_emails.begin(); it != root_to_emails.end(); ++it) {
            std::vector<std::string>& emails = it->second;
            std::sort(emails.begin(), emails.end());
            
            std::vector<std::string> account;
            account.push_back(email_to_name[emails[0]]); // Push the name first
            account.insert(account.end(), emails.begin(), emails.end()); // Push sorted emails
            merged_accounts.push_back(account);
        }

        return merged_accounts;
    }
};