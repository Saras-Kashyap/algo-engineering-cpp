# 🤝 Contributing to Enterprise LeetCode Solutions

First off, thank you for considering contributing! We aim to build the cleanest, most scalable LeetCode repository on GitHub. 

To maintain our enterprise-grade architecture, we use a fully automated CI/CD pipeline. **You only need to write code—our scripts handle the database, build system, and documentation.**

> **🛑 IMPORTANT: DO NOT EDIT GENERATED FILES**
> * Our `metadata/database.json` and `README.md` are automatically generated. **Manual edits will be overwritten.**
> * Our build system is completely dynamic. **Do NOT edit `CMakeLists.txt` to add your tests.**

---

## 🛠️ How to Contribute

### 🚀 Method 1: The Automated Way (Recommended)
We have built a Python automator that handles all boilerplate, folder creation, and file linking for you.

1. Open your terminal in the root directory.
2. Run the automator script with your problem details:
   ```bash
   python scripts/start.py --id [PROBLEM_ID] --topic [CATEGORY] --title "[PROBLEM TITLE]" --diff [Easy/Medium/Hard]
   ```
   
   *Example:*
   ```bash
   python scripts/start.py --id 20 --topic stacks --title "Valid Parentheses" --diff Easy
   ```

3. The script will instantly generate your `.hpp` file and your `_test.cpp` file in the correct folders. 
4. Just write your logic, write your test cases, and push!

---

### ✍️ Method 2: The Manual Way
If you prefer to create the files manually, you **MUST** adhere strictly to the following rules so our cloud pipeline can find and execute your code:

#### 1. Write the Code & Add Metadata
* Navigate to `src/` and find (or create) the appropriate topic folder (e.g., `src/arrays/`).
* Create a `.hpp` file using the standard format: `[ID]_[Problem_Name].hpp` (e.g., `0001_two_sum.hpp`).
* You **MUST** include the exact comment block at the very top. You can use this prompt/template and just write this in your file:

```cpp
/* * ID: 1 
 * Title: Two Sum 
 * Difficulty: Easy 
 * Companies: Amazon, Microsoft 
 */

class Solution {
public:
    // main code here
};
```

#### 2. Write the Test (Mandatory Naming Convention)
* We use **Google Test (GTest)**. Code without tests will not be accepted.
* Navigate to the `tests/` directory and match the topic folder.
* ⚠️ **CRITICAL:** Your test file **MUST** end with `_test.cpp` (e.g., `tests/arrays/two_sum_test.cpp`). 
* If your file does not end in `_test.cpp`, our dynamic CMake build system will ignore it, and your Pull Request will fail.

---

## ✅ Verify Locally (Optional)
To ensure your code won't break the pipeline, you can run our checks locally before pushing:

* **Run Tests:** ```bash
  cmake -B build -S . && cmake --build build && cd build && ctest
  ```
* **Check Metadata:** ```bash
  python scripts/auto_discover.py
  ```

## 🚢 Submit your Pull Request
Push your branch to GitHub and open a Pull Request. Our CI/CD pipeline will automatically run your tests, verify your code, and update the documentation!