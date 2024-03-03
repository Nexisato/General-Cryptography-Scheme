# RSA Accumulator-based-CLPKS Scheme
> A prototype of Certificate Less Public Key Signature based on RSA Accumulator Scheme.

## Environment
- **OS**: Ubuntu22.04 (WSL2)
- **Build**: CMake
- **Architecture**: x86_64
- **Dependencies**:
    - MIRACL Cryptography Library
    - jsoncpp



## Notes
This implementation does not consider the `serialization` and `deserialization` problem, 
all of the intermediate paramters are passed with the specific data structure, for I have not solved the I/O converter function :( 

    - Not solving the ECn parmaters unmatch problem.



## References
- https://github.com/miracl/MIRACL
- https://github.com/acherstyx/SM2-CPP-Implementation
- [【Readme First】How To Compile C++ version MIRACL](https://adityagudimetla.medium.com/installing-miracl-for-dummies-7eb7192c3285)