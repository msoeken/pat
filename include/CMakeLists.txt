add_library(pat INTERFACE)
target_include_directories(pat INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(pat INTERFACE fmt::fmt-header-only)
target_link_libraries(pat INTERFACE range-v3)
