# 🤝 Contributing to Enterprise LeetCode Solutions

First off, thank you for considering contributing! We aim to build the cleanest, most scalable LeetCode repository on GitHub. 

To maintain our enterprise-grade architecture, we use a fully automated CI/CD pipeline. **You only need to write code—our scripts handle the database and documentation.**

## 🛑 Important: Do NOT Edit JSON Files
Our `metadata/database.json` and `README.md` are automatically generated from the C++ source code. **Any manual edits to these files will be overwritten and rejected.**

---

## 🛠️ Step-by-Step Contribution Guide

### 1. Write the Code & Add Metadata
* Navigate to the `src/` directory and find the appropriate topic folder (e.g., `src/arrays/`).
* Create a `.hpp` file using the standard format: `[ID]_[Problem_Name].hpp` (e.g., `0001_two_sum.hpp`).
* **Crucial Step:** You MUST include this exact comment block at the very top of your `.hpp` file. Our pipeline uses this to build the database:

```cpp
/*
 * ID: 1
 * Title: Two Sum
 * Difficulty: Easy
 * Companies: Amazon, Microsoft, Adobe, Apple
 */

#pragma once
#include <vector>
using namespace std;

class Solution {
    // ... pure algorithm logic here ...
};
```
*(Note: Provide **only** the `class Solution` logic. Do not include `main()` functions or fast I/O boilerplate).*

### 2. Write the Test (Mandatory)
* We use **Google Test (GTest)**. Code without tests will not be accepted.
* Navigate to the `tests/` directory and create your test file (e.g., `tests/arrays/two_sum_test.cpp`).
* Add at least 2-3 edge cases. 
* Register your new test in the root `CMakeLists.txt` file.

### 3. Verify Locally (Optional)
To ensure your code won't break the pipeline, you can run our automation scripts locally:
1. `python scripts/auto_discover.py` (Checks for duplicate IDs and builds the JSON)
2. `python scripts/generate_docs.py` (Updates the README tables)

### 4. Submit your Pull Request
* Push your branch to GitHub and open a Pull Request.
* Our CI/CD pipeline will automatically run your tests and verify your metadata. 
* **If the GitHub Actions build fails (e.g., duplicate ID found, or tests fail), your PR cannot be merged.** Please check the action logs and fix any errors!