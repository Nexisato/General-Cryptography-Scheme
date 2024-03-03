/*** 
 * @Author: nexisato
 * @Date: 2024-02-29 16:52:58
 * @FilePath: /miracl_validation/src/process.cpp
 * @Description: 
 * @
 */
#include "process.h"

extern miracl* mip;



bool Process::generate_full_key(const std::pair<Big, ECn>& partial_key) {
    Big d = partial_key.first;
    ECn R = partial_key.second;
    
    std::string h_input = this->pid + point2str(R) + point2str(this->Ppub);
    Big h1 = hash2big(h_input);


    ECn lhs = d * ec_G;
    ECn rhs = h1 * this->Ppub;
    rhs += R;

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



Payload Process::sign(const std::string& msg, const Big& wit, const Big& N) {
    std::string ti = utils::get_time_stamp();
    Big ht = hash2big(ti);

    // wit = wit ^ ht mod N
    Big wit_new = pow(wit, ht, ec_q);
    Big y1 = rand(160, 2);

    ECn Y1 = y1 * ec_G;


    std::string h3_input = msg + big2str(wit_new) + this->pid + point2str(this->public_key.first) + point2str(this->public_key.second) + ti;
    std::string u_input = h3_input + point2str(Y1);

    Big h3 = hash2big(h3_input);
    Big u = hash2big(u_input);

    // w = (u * y1 + h3 * (d + x)) % ec_q;
    Big w = (u * y1 + h3 * (this->secret_key.first + this->secret_key.second)) % ec_q;


    Payload payload = {
        .pid = this->pid,
        .msg = msg,
        .sig1 = Y1,
        .sig2 = w,
        .pk1 = this->public_key.first,
        .pk2 = this->public_key.second,
        .time_stamp = ti,
        .wit_new = wit_new,
        .u_generated = u  
    };
    

    return payload;
}

bool Process::verify(Payload &payload, Big& acc_cur, Big& N) {
    std::string ti = payload.time_stamp;
    Big ht = hash2big(ti);

    std::string h1_input = payload.pid + point2str(payload.pk2) + point2str(this->Ppub);
    std::string h3_input = payload.msg + big2str(payload.wit_new) + payload.pid + point2str(payload.pk1) + point2str(payload.pk2) + payload.time_stamp;
    std::string u_input = h3_input + point2str(payload.sig1);

    Big h1 = hash2big(h1_input);
    Big h3 = hash2big(h3_input);
    Big u = hash2big(u_input);


    ECn rhs = payload.pk1;
    rhs += payload.pk2;
    ECn rhs_tmp = h1 * this->Ppub;
    rhs += rhs_tmp;
    rhs *= ht;

    ECn lhs = payload.sig2 * ec_G;

    ECn lhs_tmp = -payload.sig1;
    lhs_tmp *= u;

    lhs += lhs_tmp;


    if (lhs != rhs) {
        std::cerr << "verify: 签名不合法" << std::endl;
        return false;
    }

    std::cout << "验证累加器参数" << std::endl;

    return true;
}