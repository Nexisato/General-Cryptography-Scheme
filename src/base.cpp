/*** 
 * @Author: nexisato
 * @Date: 2024-02-29 15:49:15
 * @FilePath: /miracl_validation/src/base.cpp
 * @Description:  base 头文件中接口的定义
 * @
 */
#include "base.h"


#ifndef MR_NOFULLWIDTH
Miracl precision(_MIR_ND_, _MIR_BASE_);
#else
Miracl precision(50, MAXBASE);
#endif
miracl* mip = &precision;



Big hash2big(std::string& str) { /* compute hash function */
    Big h;
    sha256 sh;
    shs256_init(&sh);
    char* s = const_cast<char*>(str.c_str());
    shs256_hash(&sh, s);
    h = from_binary(20, s);
    return h;
}


std::string big2str(Big& b) {
    char c[128];
    c << b;
    return std::string(c);
}

Big str2big(const std::string& str) {
    Big b;
    b = const_cast<char*>(str.c_str());
    return b;
}

std::string point2str(const ECn& P) {
    Big x, y;
    P.getxy(x, y);
    std::string str = big2str(x) + big2str(y);
    return str;
}

ECn str2point(const std::string& str) {
    Big x, y;
    int len = str.length() / 2;
    x = str2big(str.substr(0, len));
    y = str2big(str.substr(len, len));
    ECn P(x, y);
    return P;
}