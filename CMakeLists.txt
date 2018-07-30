cmake_minimum_required(VERSION 2.8.12)

project (VTB)

enable_language(CXX)
enable_language(C)
enable_language(ASM)

include_directories ("${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/net/include")

# add subdirectory
add_subdirectory (storage)
add_subdirectory (lib)
add_subdirectory (config)
add_subdirectory (net)
add_subdirectory (rpc)
add_subdirectory (core)
add_subdirectory (cmd)

set (extra_libs storage )

#add_executable (VTB-DB main.c)

#target_link_libraries (VTB-DB ${extra_libs})