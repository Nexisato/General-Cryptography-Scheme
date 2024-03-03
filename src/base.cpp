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


miracl *mip = &precision;

Big ec_bits, ec_p, ec_a, ec_b, ec_q, ec_x0, ec_y0;
ECn ec_G;
const char* ec_filename = "../secp160.ecs";


void init_ecc(const char*& filename) {
    ifstream common(filename);
    if (!common) {
        std::cerr << "Unexpected filename: " << filename << std::endl;
        throw std::invalid_argument("File not found.");
    }
    mip->IOBASE = 10;
    common >> ec_bits;
    mip->IOBASE = 16;
    common >> ec_p >> ec_a >> ec_b >> ec_q >> ec_x0 >> ec_y0;
    ecurve(ec_a, ec_b, ec_p, MR_PROJECTIVE);
    ec_G = ECn(ec_x0, ec_y0);
}



/**
 * @brief Hash a string to a number : default is 160 bit
*/
Big hash2big(std::string& str) { 
    char s[20];
    Big h;
    sha sh;
    shs_init(&sh);
    for (auto&& ch : str) {
        shs_process(&sh, ch);
    }
    shs_hash(&sh, s);
    h = from_binary(20, s);
    return h;
}

// Hash a zero-terminated string to a number < modulus
Big hash2big_256(std::string& str) {  
    Big h, p;
    char s[_HASH256_LEN_];
    int i, j;
    sha256 sh;
    char* c_str = const_cast<char*>(str.c_str());
    shs256_init(&sh);

    for (i = 0;; i++) {
        if (str[i] == 0) break;
        shs256_process(&sh, str[i]);
    }
    shs256_hash(&sh, s);
    p = get_modulus();
    h = 1;
    j = 0;
    i = 1;
    forever {
        h *= 256;
        if (j == _HASH256_LEN_) {
            h += i++;
            j = 0;
        } else
            h += s[j++];
        if (h >= p) break;
    }
    h %= p;
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
    std::string str = big2str(x) + "," +  big2str(y);
    return str;
}

//! [BUG NOT FIX]Convert a string to a point
// ECn str2point(const std::string& str) {
//     init_ecc(ec_filename);
//     std::size_t pos = str.find(",");
//     if (pos == std::string::npos) {
//         throw std::invalid_argument("Invalid input string format. Expected format 'x,y' .");
//     }
//     Big x = str2big(str.substr(0, pos));
//     Big y = str2big(str.substr(pos + 1));

    
//     return P;
// }