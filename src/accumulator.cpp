/***
 * @Author: nexisato
 * @Date: 2024-02-27 19:32:13
 * @FilePath: /miracl_validation/src/accumulator.cpp
 * @Description: 密码累加器的类实现
 * @
 */
#include "accumulator.h"

Big Accumulator::witness_generate_by_pid(const Big &pid) {
    Big product = 1;
    for (auto &pid_val : members) {
        if (pid_val != pid) {
            product *= pid_val;
        }
    }
    Big w = pow(acc_init, product, public_key);
    return w;
}

bool Accumulator::is_contained(const Big &pid_val) {
    for (auto &it : members) {
        if (it == pid_val) {
            return true;
        }
    }
    return false;
}

void Accumulator::remove_by_pid(const Big &pid_val) {
    for (auto it = members.begin(); it != members.end(); it++) {
        if (*it == pid_val) {
            members.erase(it);
            size_t idx = std::distance(members.begin(), it);
            wits.erase(wits.begin() + idx);
            break;
        }
    }
}

Accumulator::Accumulator(int BITS) {
    irand(utils::get_seed());
    Big p = nextprime(rand(BITS, 2));
    Big q = nextprime(rand(BITS, 2));
    secret_key = std::make_pair(p, q);
    public_key = p * q;
    acc_init = rand(BITS, 2);
    acc_cur = acc_init;
}

void Accumulator::add_member(const Big &pid_val) {
    this->members.push_back(pid_val);
    this->acc_cur = pow(acc_cur, pid_val, public_key);
}

void Accumulator::witness_generate_all() {
    for (auto &pid_val : members) {
        this->wits.push_back(std::move(witness_generate_by_pid(pid_val)));
    }
}

bool Accumulator::verify_member(const Big& wit, const Big& pid_val) {
        Big rhs = pow(wit, pid_val, public_key);
        return rhs == acc_cur;
}

Big Accumulator::remove_member(const Big& pid_val) {
        if (!is_contained(pid_val)) {
            std::cerr << "The member is not in the accumulator" << std::endl;
            return 0;
        }
        Big euler_pk = (secret_key.first - 1) * (secret_key.second - 1);
        // 求逆元
        Big Aux = inverse(pid_val, euler_pk);
        acc_cur = pow(acc_cur, Aux, public_key);
        remove_by_pid(pid_val);
        return Aux;
}

Big Accumulator::remove_members(std::vector<Big>& pid_vals) {
            Big X = 1;
        bool is_effective = true;
        for (auto &pid_val : pid_vals) {
            if (!is_contained(pid_val)) {
                is_effective = false;
                break;
                
            } else {
               X = X * pid_val; 
            }
        }
        if (!is_effective) {
            std::cerr << "There exits a member which not in the accumulator" << std::endl;
            return 0;
        }

        Big euler_pk = (secret_key.first - 1) * (secret_key.second - 1);
        // 求逆元
        Big Aux = inverse(X, euler_pk);
        acc_cur = pow(acc_cur, Aux, public_key);
        for (auto &pid_val : pid_vals) {
            remove_by_pid(pid_val);
        }
        return Aux;
}

void Accumulator::update_witness(const Big& Aux) {
    for (auto &wit : wits) {
        wit = pow(wit, Aux, public_key);
    }
}