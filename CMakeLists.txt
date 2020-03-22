cmake_minimum_required(VERSION 3.15)
project(llvm_ir)

set(LLVM_DIR /usr/local/Cellar/llvm/9.0.1/lib/cmake/llvm/)
#list(APPEND CMAKE_MODULE_PATH /usr/local/Cellar/llvm/9.0.1/lib/cmake/)
message( ${LLVM_DIR} )
find_package(LLVM REQUIRED CONFIG)


set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp test.c)

include_directories(/usr/local/Cellar/llvm/9.0.1/include)
#include_directories(/usr/local/opt/llvm/include)
# add extra lib directories

link_directories(/usr/local/Cellar/llvm/9.0.1/lib)
#link_directories(/usr/local/opt/llvm/lib)

target_link_libraries(LLVM)


