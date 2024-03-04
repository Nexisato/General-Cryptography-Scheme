/***
 * @Author: nexisato
 * @Date: 2024-02-29 16:46:13
 * @FilePath: /miracl_validation/src/kgc.cpp
 * @Description: KGC 的实现
 * @
 */
#include "kgc.h"

extern miracl* mip;
extern Big ec_p, ec_a, ec_b, ec_q, ec_x0, ec_y0;
extern ECn ec_G;

KGC::KGC(const char*& filename) {
    init_ecc(filename);
    irand(utils::get_seed());
    this->s = rand(160, 2);
    this->Ppub = s * ec_G;  // 不能换位
}

std::pair<Big, ECn> KGC::generate_partial_key( const std::string& pid_val) {
    Big r = rand(160, 2);
    ECn R = r * ec_G;

    std::string h_input = pid_val + point2str(R) + point2str(Ppub);
    Big h = hash2big(h_input);

    Big d = (s * h + r) % ec_q;
    return std::make_pair(d, R);
}
