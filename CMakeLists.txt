cmake_minimum_required(VERSION 3.15)
project(miracl_test)


set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")



include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(ACCUMULATOR_PART
    src/utils.cpp
    src/accumulator.cpp
    test/test_acc.cpp
)

set(ECC_PART 
    src/utils.cpp
    test/test_ecc.cpp
)

add_executable(${TARGET_NAME}
    #${ACCUMULATOR_PART}
    ${ECC_PART}
)


target_link_libraries(${PROJECT_NAME} 
    ${PROJECT_SOURCE_DIR}/lib/libmiracl.a
    jsoncpp
)