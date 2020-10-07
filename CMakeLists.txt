cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_MAIN "Build main" OFF)
option(BUILD_COVERAGE "Build coverage" OFF)
option(BUILD_TESTS "Build coverage" OFF)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz"
    SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d"
)

project(template_cpp_project)

string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

if (BUILD_TESTS)
    hunter_add_package(GTest)
    find_package(GTest CONFIG REQUIRED)
endif()

set(SOURCES ${PROJECT_NAME}_sources)
set(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(${SOURCES} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/math.cpp)
target_include_directories(${SOURCES} PUBLIC ${INCLUDE})

if(BUILD_MAIN)
set(MAIN ${PROJECT_NAME}_main)

add_executable(${MAIN} ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)

target_include_directories(${MAIN} PUBLIC ${INCLUDE})
target_link_libraries(${MAIN} ${SOURCES})

endif()

if (BUILD_TESTS)

add_executable(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        )

target_include_directories(
        tests
        PUBLIC
        ${INCLUDE}
        ${GTEST_ROOT}/include
)
target_link_libraries(
        tests
        GTest::gtest
        GTest::gtest_main
        ${SOURCES}
)
enable_testing()
add_test(NAME unit_tests COMMAND tests)
endif()

if (BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  add_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif ()