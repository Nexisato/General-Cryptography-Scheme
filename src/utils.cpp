/***
 * @Author: nexisato
 * @Date: 2024-02-27 08:49:44
 * @FilePath: /miracl_validation/src/timer.cpp
 * @Description:
 * @
 */
#include "utils.h"

namespace utils {
double count_time(chrono_time t0, chrono_time t1) {
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);

    double res = double(duration.count()) *
                 std::chrono::microseconds::period::num /
                 std::chrono::milliseconds::period::den;
    return res;
}


std::string get_time_stamp() {
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto now_c = now.time_since_epoch().count();
    return std::to_string(now_c); 
}


unsigned int get_seed() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);
    return rng();
}

void toUpperCase(char * str) {
    if (str == nullptr) return; // 确保指针非空

    while (*str) { // 遍历字符串直到遇到空字符
        *str = std::toupper(*str); // 将当前字符转换为大写
        ++str; // 移动到下一个字符
    }
}

std::string toUpperCase(const std::string& input) {
    std::string result;
    for (char c : input) {
        result += std::toupper(c); // 将每个字符转换为大写
    }
    return result;
}

};  // namespace utils
