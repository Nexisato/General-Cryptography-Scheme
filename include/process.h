/*** 
 * @Author: nexisato
 * @Date: 2024-02-29 16:52:33
 * @FilePath: /miracl_validation/include/process.h
 * @Description: 通信实体类process接口声明
 * @
 */
#pragma once
#include "base.h"

class Process {
private:

public:
    Process();
    ~Process();

    /**
     * @brief 生成密钥对
    */
    std::pair<std::string, std::string> generate_key_pair();

    /**
     * @brief 生成密文
    */
    std::string sign(const std::string& plain, const std::string& pub_key);

    /**
     * @brief 解密
    */
    bool verify(const std::string& cipher, const std::string& pri_key);
};

