#include "base.h"
#include "utils.h"
#include <fstream>
#include <iostream>


extern miracl* mip;


class ECC {
private:
    Big s;

public:
    Big order, p, a, b, q, x0, y0;
    ECn Ppub;
    ECn G;
    /**
     * @brief KGC constructor
    */
    explicit ECC(const char*& filename) {
        ifstream common(filename);
        mip->IOBASE = 10;
        common >> order;
        mip->IOBASE = 16;
        common >> p >> a >> b >> q >> x0 >> y0;
        ecurve(a, b, p, MR_PROJECTIVE);
        this->G = ECn(x0, y0);
        irand(utils::get_seed());
        this->s = rand(256, 2);
        this->Ppub = s * G;  // 不能换位
    }

    void test_point_multi(int threshold) {
        auto start_time = std::chrono::system_clock::now();

        for (int i = 0; i < threshold; ++i) {
            ECn R = rand(160, 2) * G;
        }


        auto end_time = std::chrono::system_clock::now();
        double duration = utils::count_time(start_time, end_time);
        std::cout << "point multi: " << duration / threshold << " ms" << std::endl;
    }

    void test_point_add(int threshold) {
        auto start_time = std::chrono::system_clock::now();
        ECn T(x0, y0);
        for (int i = 0; i < threshold; ++i) {
            T += G;
        }

        auto end_time = std::chrono::system_clock::now();
        double duration = utils::count_time(start_time, end_time);
        std::cout << "point add: " << duration / threshold << " ms" << std::endl;
    }

    void test_hash(int threshold) {
        std::string str = "helloworlddwddwadawdaawddwadwaddwadwadwadwasdawadasdawdawwawa";
        auto start_time = std::chrono::system_clock::now();
        Big h;
        for (int i = 0; i < threshold; ++i) {
            h = hash2big_256(str);
        }
        auto end_time = std::chrono::system_clock::now();
        std::cout << "bits of h: " << bits(h) << std::endl;
        double duration = utils::count_time(start_time, end_time);
        std::cout << "hash: " << duration / threshold << " ms" << std::endl;

        std::cout << "h: " << h << std::endl;
        std::cout << "bits of h: " << bits(h) << std::endl;
    }



public:
    void print_params() {
        std::cout << "bits: " << order << std::endl;
        std::cout << "p: " << p << std::endl;
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "q: " << q << std::endl;
        std::cout << "bit of q: " << bits(q) << std::endl;
        std::cout << "G: " << G << std::endl;
        std::cout << "s: " << s << std::endl;
        std::cout << "Ppub: " << Ppub << std::endl;
        std::cout << "==================" << std::endl;
    }
};







int main() {
    mip->IOBASE = 16;
    const char* filename = "../secp160.ecs";

    ECC* ecc_ptr = new ECC(filename);


    ecc_ptr->print_params();


    ecc_ptr->test_point_multi(1000);
    ecc_ptr->test_point_add(1000);
    ecc_ptr->test_hash(1000);


    return 0;
}