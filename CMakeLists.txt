set(CONTEST 240227_b23)
set(PROBLEM I)

cmake_minimum_required(VERSION 3.0.0)
project(MCSContest VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(MCSContest sources/${CONTEST}/${PROBLEM}.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
