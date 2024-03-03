/*** 
 * @Author: nexisato
 * @Date: 2024-02-29 16:39:50
 * @FilePath: /miracl_validation/include/kgc.h
 * @Description: KGC 的接口声明
 * @
 */

#pragma once
#include "base.h"
#include "utils.h"
#include <fstream>

class KGC {
private:
    Big s;

public:
    Big bits, p, a, b, q, x0, y0;
    ECn Ppub;
    ECn G;
    /**
     * @brief KGC constructor
    */
    explicit KGC(const char*&);

    /**
     * @brief generate partial key
    */
    std::pair<std::string, std::string> generate_partial_key(const std::string&);


#ifndef NDEBUG
public:
    void print_params() {
        std::cout << "bits: " << bits << std::endl;
        std::cout << "p: " << p << std::endl;
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "q: " << q << std::endl;
        std::cout << "G: " << G << std::endl;
        std::cout << "s: " << s << std::endl;
        std::cout << "Ppub: " << Ppub << std::endl;
        std::cout << "==================" << std::endl;


    }
#endif
};
