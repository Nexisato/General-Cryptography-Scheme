/*** 
 * @Author: nexisato
 * @Date: 2024-02-27 08:47:33
 * @FilePath: /miracl_validation/include/utils.h
 * @Description: 工具类函数头文件
 * @
 */

#pragma once
#include <chrono>
#include <ctime>
#include <random>
#include <cctype>
#include <string>
#include <cstring>

using chrono_time = std::chrono::_V2::system_clock::time_point;

namespace utils {

/**
 * @brief Calculate the Time Duration between 2 points
 *
 * @param t0 : start_time
 * @param t1 : end_time
 * @return double / (unit):milliseconds
 */
double count_time(chrono_time t0, chrono_time t1);


/**
 * @brief Get the Time Stamp in string format
*/
std::string get_time_stamp();

/**
 * @brief Get the Seed object
*/
unsigned int get_seed();

/**
 * @brief Convert a string to upper case
*/
void toUpperCase(char* str);
void toUpperCase(std::string &str);
};