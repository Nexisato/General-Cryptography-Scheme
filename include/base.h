/*** 
 * @Author: nexisato
 * @Date: 2024-02-29 15:44:29
 * @FilePath: /miracl_validation/include/base.h
 * @Description: miracl 密码学库的基础头文件
 *  - 头文件 inclue
 *  - 数据转换函数，string 和 big/ECn 的相互转换
 * @
 */
#pragma once
#ifndef _BASE_H_
#include "miracl/miracl.h"
#include "miracl/ecn.h"
#include "miracl/big.h"


#define _MIR_ND_ 2048
#define _MIR_BASE_ 2
#define _HASH_LEN_ 20
#define _HASH256_LEN_ 32


/**
 * @brief Hash function，string -> big number
 */
Big hash2big(std::string& str);

/**
 * @brief hash function, sha256
*/
Big hash2big_256(std::string& str);

/**
 * @brief big number -> string
*/
std::string big2str(Big& b);

/**
 * @brief string -> big number
*/
Big str2big(const std::string& str);


/**
 * @brief ECn -> string
*/
std::string point2str(const ECn& P);


/**
 * @brief string -> ECn
*/
ECn str2point(const std::string& str);

#endif  // _BASE_H_





