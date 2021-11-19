set(BINARY ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false t*.h *.cpp)
set(SOURCES ${TEST_SOURCES})
message(${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    ${CMAKE_PROJECT_NAME}_tests
    ${TEST_SOURCES}
)
add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(
    ${CMAKE_PROJECT_NAME}_tests
    PUBLIC
    ${CMAKE_PROJECT_NAME}_lib
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_tests)
