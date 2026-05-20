#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> strs;
    std::string s;
    while (std::cin >> s) strs.push_back(s);

    if (strs.empty()) {
        std::cout << "" << std::endl;
        return 0;
    }

    std::string prefix = strs[0];
    for (size_t i = 1; i < strs.size(); ++i) {
        while (strs[i].find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.length() - 1);
            if (prefix.empty()) {
                std::cout << "" << std::endl;
                return 0;
            }
        }
    }
    std::cout << prefix << std::endl;
    return 0;
}