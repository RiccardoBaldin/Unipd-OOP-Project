#ifndef FINDER_HPP
#define FINDER_HPP

#include <vector>
#include <string>
#include <algorithm>

inline std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

template <typename T, typename Func>
std::vector<T*> finder(const std::vector<T*>& vec, const std::string& s, Func getString) {
    std::vector<T*> result;
    std::string s_lower = toLower(s);

    for (auto item : vec) {
        std::string name = toLower(getString(item));
        if (name.find(s_lower) != std::string::npos) {
            result.push_back(item);
        }
    }
    return result;
}

#endif // FINDER_HPP