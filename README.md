# General-Cryptography-Scheme
>  A prototype of General Cryptography Scheme Framework

## Environment
- **OS**: Ubuntu22.04 (WSL2) / Windows (only for Java Development)
- **Architecture**: x86_64
- **C++ version (bug not fixed):**
    - **Build**: CMake
    - **Dependencies**:
        - MIRACL Cryptography Library
        - jsoncpp
- **Python Version(Recommended):**
    - **Dependencies**:
        - gmpy2
        - fastecdsa
        - sympy
        - cryptography
        - pymcl (bilinear pairing, safer and faster)
        - pypbc (bilinear pairing, NOT SAFE)
        - py_ecc (Recommended for Pair and ECDSA Demo)
- **Java Version (Useful for jpbc-API)**
    - **Dependencies**
        - bcprov-jdk16-1.46.jar
        - Jama-1.0.3.jar
        - jna-3.2.5.jar
        - jpbc-api-2.0.0.jar
        - jpbc-benchmark-2.0.0.jar
        - jpbc-crypto-2.0.0.jar
        - jpbc-mm-2.0.0.jar
        - jpbc-pbc-2.0.0.jar
        - jpbc-plaf-2.0.0.jar
        - logback-classic-1.5.6.jar
        - logback-core-1.5.6.jar
        - slf4j-api-2.0.13.jar
        - guava-19.0.jar


## Notes

- **2024-05-31**: update `time_perf` decorator in `utils.py` for better measurment

This implementation does not consider the `serialization` and `deserialization` problem, 
all of the intermediate paramters are passed with the specific data structure, for I have not solved the I/O converter function :( 

    - Not solving the ECn parmaters unmatch problem.

For more complex pairing shchemes, we recommend JPBC with `Scheme` Abstract Base Class.



## References
- https://github.com/miracl/MIRACL
- https://github.com/acherstyx/SM2-CPP-Implementation
- [【Readme First】How To Compile C++ version MIRACL](https://adityagudimetla.medium.com/installing-miracl-for-dummies-7eb7192c3285)
- https://github.com/Jemtaly/pypbc  (Recommended for Python >= 3.10)
- https://github.com/AntonKueltz/fastecdsa
- https://github.com/Jemtaly/pymcl
- https://github.com/herumi/mcl