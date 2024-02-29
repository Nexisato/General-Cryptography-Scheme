/*** 
 * @Author: nexisato
 * @Date: 2024-02-29 16:46:13
 * @FilePath: /miracl_validation/src/kgc.cpp
 * @Description: KGC 的实现
 * @
 */
#include "kgc.h"

extern miracl* mip;

KGC::KGC(const char*& filename) {
            ifstream common(filename);
        mip->IOBASE = 10;
        common >> bits;
        mip->IOBASE = 16;
        common >> p >> a >> b >> q >> x0 >> y0;
        ecurve(a, b, p, MR_PROJECTIVE);
        this->G = ECn(x0, y0);
        irand(utils::get_seed());
        this->s = rand(256, 2);
        this->Ppub = s * G;  // 不能换位
}


    std::pair<std::string, std::string> KGC::generate_partial_key(const std::string& pid_val) {
        Big r = rand(160, 2);
        ECn R = r * G;

        std::string h_input = pid_val + point2str(R) + point2str(Ppub);
        Big h = hash2big(h_input);

        Big d = (s + h * r) % q;
        return std::make_pair(big2str(d), point2str(R));
    }
