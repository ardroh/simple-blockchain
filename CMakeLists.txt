# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.16.3)
project (SimpleCppBlockchain)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")

file(GLOB SimpleCppBlockchain_SRC
    "src/*.cpp"
)

add_executable (SimpleCppBlockchain ${SimpleCppBlockchain_SRC})

target_link_libraries(SimpleCppBlockchain OpenSSL::SSL)
