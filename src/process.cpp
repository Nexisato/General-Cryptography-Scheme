/*** 
 * @Author: nexisato
 * @Date: 2024-02-29 16:52:58
 * @FilePath: /miracl_validation/src/process.cpp
 * @Description: 
 * @
 */
#include "process.h"

extern miracl* mip;


Process::Process(const std::string& pid, const std::string& Ppub_str) {
    this->pid = pid;
    this->Ppub = str2point(Ppub_str);

}

bool Process::generate_full_key(const std::pair<std::string, std::string>& partial_key) {
    Big d = str2big(partial_key.first);
    ECn R = str2point(partial_key.second);
    
    // this->secret_key = std::make_pair(d, R);
    // this->public_key = std::make_pair(d * Ppub, R);
    return true;
}


