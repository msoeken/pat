cmake_minimum_required(VERSION 3.1)
project(kitty LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

# Options
#option(PAT_EXAMPLES "Build examples" ON)
#option(PAT_BENCH "Build benchmarks" OFF)
option(PAT_TEST "Build tests" OFF)

# some specific compiler definitions
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-fcolor-diagnostics" HAS_FCOLOR_DIAGNOSTICS)
if(HAS_FCOLOR_DIAGNOSTICS)
  add_definitions(-fcolor-diagnostics)
endif()

add_subdirectory(lib)
add_subdirectory(include)

if(PAT_TEST)
  add_subdirectory(test)
endif()
