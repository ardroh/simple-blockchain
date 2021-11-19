set(BINARY ${CMAKE_PROJECT_NAME})

find_package(OpenSSL REQUIRED)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY}_run OpenSSL::SSL)
target_link_libraries(${BINARY}_lib OpenSSL::SSL)
