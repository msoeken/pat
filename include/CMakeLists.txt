add_library(pat INTERFACE)
target_include_directories(pat INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(pat INTERFACE pat_fmt)
target_link_libraries(pat INTERFACE pat_range-v3)
