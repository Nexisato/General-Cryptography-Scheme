/*** 
 * @Author: nexisato
 * @Date: 2024-02-29 16:52:58
 * @FilePath: /miracl_validation/src/process.cpp
 * @Description: 
 * @
 */
#include "process.h"

extern miracl* mip;



Process::Process(const std::string& pid, const ECn& Ppub_val) {
    this->pid = pid;
    this->Ppub = Ppub_val;
}

bool Process::generate_full_key(const std::pair<Big, ECn>& partial_key) {
    Big d = partial_key.first;
    ECn R = partial_key.second;
    
    std::string h_input = this->pid + point2str(R) + point2str(this->Ppub);
    Big h1 = hash2big(h_input);


    ECn lhs = d * ec_G;
    ECn rhs = h1 * this->Ppub;
    rhs += R;

    std::cout << "lhs: " << lhs << std::endl;
    std::cout << "rhs: " << rhs << std::endl;
    
    if (lhs != rhs) {
        std::cerr << "generate_full_key: d * G != h1 * Ppub + R" << std::endl;
        return false;
    }

    Big x = rand(160, 2);
    ECn X = x * ec_G;

    this->public_key.first = X;
    this->public_key.second = R;

    this->secret_key.first = d;
    this->secret_key.second = x;

    return true;
}


