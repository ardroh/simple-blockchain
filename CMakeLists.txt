# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (SimpleCppBlockchain)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")

add_executable (SimpleCppBlockchain main.cpp Block.cpp Digest.cpp)

target_link_libraries(SimpleCppBlockchain OpenSSL::SSL)
