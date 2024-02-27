/*** 
 * @Author: nexisato
 * @Date: 2024-02-27 19:30:53
 * @FilePath: /miracl_validation/include/accumulator.h
 * @Description: 密码累加器的定义
 * @
 */
#pragma once

#include "miracl/big.h"
#include "utils.h"
#include "miracl/miracl.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

#define _KEY_LEN_ 512


class Accumulator {
private:
    std::pair<Big, Big> secret_key;
    std::vector<Big> members;

    /**
     * @brief generate witness by pid
    */
    Big witness_generate_by_pid(const Big &);

    /**
     * @brief check if the member is in the accumulator
    */
    bool is_contained(const Big&);

    /**
     * @brief remove the member by pid (in vector: members, wits)
    */
    void remove_by_pid(const Big &);

public:
    Big public_key;
    Big acc_cur, acc_init;
    std::vector<Big> wits;

    explicit Accumulator(int BITS = _KEY_LEN_);
    ~Accumulator() {}

    /**
     * @brief add a member to the accumulator
    */
    void add_member(const Big &pid_val);

    /**
     * @brief add all witnesses to the accumulator
    */
    void witness_generate_all();

    /**
     * @brief verify if the pid in the current acc_val
    */
    bool verify_member(const Big& wit, const Big& pid_val);

    /**
     * @brief remove a member from the accumulator
    */
    Big remove_member(const Big& pid_val);

    /**
     * @brief remove members from the accumulator
    */
    Big remove_members(std::vector<Big>& pid_vals);

    /**
     * @brief update the witness by Aux
    */
    void update_witness(const Big& Aux);


#ifndef NDEBUG
public:
    void print_params() {
        std::cout << "p: " << secret_key.first << std::endl;
        std::cout << "q: " << secret_key.second << std::endl;
        std::cout << "pk: " << public_key << std::endl;
        std::cout << "acc_init: " << acc_init << std::endl;
        std::cout << "====================" << std::endl;
        const int size = members.size();
        for (int i = 0; i < size; i++) {
            std::cout << "member[" << i << "]: " << this->members[i] << std::endl;
            std::cout << "wits[" << i << "]: " << this->wits[i] << std::endl;
        }
    }
#endif

};