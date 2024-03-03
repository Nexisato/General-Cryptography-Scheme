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


/**
* @brief 
* the payload of the signed msg
*/
struct Payload {
    std::string pid;    // from process
    std::string msg;
    std::string sig1, sig2;
    std::string pk1, pk2;
    std::string time_stamp;
    std::string wit_new;
    std::string u_generated;    // for aggregate(contains P_pub_hex)
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
    explicit Process(const std::string& pid, const std::string& Ppub_str);
    ~Process();

    /**
     * @brief 生成完整密钥
     * 
     * PublicKey: (X, R)
     * SecretKey: (d, r)
    */
    bool generate_full_key(const std::pair<std::string, std::string>& partial_key);

    /**
     * @brief 消息签名
     *
     * @param msg
     * @param wit_hex
     * @param N: public key in accumulator system
     * @return Payload: include (pid, msg, sig1, sig2, pk1, pk2)
      sig1(ECn): Y1
      sig2 (Big): w
     */
    Payload sign(const std::string& msg, const std::string& wit_old, const std::string& N);


    /**
     * @brief 消息验签
     *
     * @param payload
     * @param nid
     * @param acc_cur
     * @return true
     * @return false
     */
    bool verify(Payload &payload, const int nid, std::string &Ppub_hex,
                std::string &acc_cur, std::string &N);
};

