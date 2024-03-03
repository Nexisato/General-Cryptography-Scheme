/*** 
 * @Author: nexisato
 * @Date: 2024-02-29 16:52:33
 * @FilePath: /miracl_validation/include/process.h
 * @Description: 通信实体类process接口声明
 * @
 */
#pragma once
#include "base.h"
#include "utils.h"


extern Big ec_bits, ec_p, ec_a, ec_b, ec_q, ec_x0, ec_y0;
extern ECn ec_G;

/**
* @brief 
* the payload of the signed msg
*/
struct Payload {
    std::string pid;    // from process
    std::string msg;
    ECn sig1;
    Big sig2;
    ECn pk1, pk2;
    std::string time_stamp;
    Big wit_new;
    Big u_generated;
};

class Process {
private:
    std::pair<Big, Big> secret_key;
public:
    std::string pid;
    std::pair<ECn, ECn> public_key;
    ECn Ppub;
    
    /**
     * @brief Process constructor
    */
    explicit Process(const std::string& pid_val, const ECn& Ppub_val) : pid(pid_val), Ppub(Ppub_val) {}
    ~Process();

    /**
     * @brief 生成完整密钥
     * 
     * PublicKey: (X, R)
     * SecretKey: (d, r)
    */
    bool generate_full_key(const std::pair<Big, ECn>& partial_key);

    /**
     * @brief 消息签名
     *
     * @param msg
     * @param wit
     * @param N: public key in accumulator system
     * @return Payload: include (pid, msg, sig1, sig2, pk1, pk2)
      sig1(ECn): Y1
      sig2 (Big): w
     */
    Payload sign(const std::string& msg, const Big& wit, const Big& N);


    /**
     * @brief 消息验签，这里不考虑跨 KGC 的问题
     *
     * @param payload
     * @param acc_cur
     * @param N
     * @return true
     * @return false
     */
    bool verify(Payload &payload, Big& acc_cur, Big& N);

#ifndef NDEBUG
public:
    void print_params() {
        std::cout << "---------- Process Params -------------" << std::endl;
        std::cout << "pid: " << pid << std::endl;
        std::cout << "Ppub: " << this->Ppub << std::endl;
        std::cout << "G: " << ec_G << std::endl;
        std::cout << "==================" << std::endl;
    }
#endif
};

