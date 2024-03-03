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

extern Big ec_bits, ec_p, ec_a, ec_b, ec_q, ec_x0, ec_y0;
extern ECn ec_G;

class KGC {
private:
    Big s;

public:
    ECn Ppub;
    /**
     * @brief KGC constructor
    */
    explicit KGC(const char*&);

    /**
     * @brief generate partial key
     * @return (d, R)
     *  d - big number
     *  R - EC Point
    */
    std::pair<Big, ECn> generate_partial_key(const std::string&);


#ifndef NDEBUG
public:
    void print_params() {
        std::cout << "-------- KGC Params -----------" << std::endl;
        std::cout << "bits: " << ec_bits << std::endl;
        std::cout << "p: " << ec_p << std::endl;
        std::cout << "a: " << ec_a << std::endl;
        std::cout << "b: " << ec_b << std::endl;
        std::cout << "q: " << ec_q << std::endl;
        std::cout << "G: " << ec_G << std::endl;
        std::cout << "s: " << s << std::endl;
        std::cout << "Ppub: " << Ppub << std::endl;
        std::cout << "==================" << std::endl;


    }
#endif
};
