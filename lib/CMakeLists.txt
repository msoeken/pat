add_library(pat_range-v3 INTERFACE)
target_include_directories(pat_range-v3 INTERFACE range-v3/include)

add_library(pat_fmt INTERFACE) # v4.1.0
target_include_directories(pat_fmt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/fmt)
target_compile_definitions(pat_fmt INTERFACE FMT_HEADER_ONLY)
