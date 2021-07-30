cmake_minimum_required(VERSION 3.12...3.21)
project(sandbox)

# Define executable (.cpp only)
add_executable(sandbox src/main.cpp)

# Set Output dir of library to be in build/bin
set_target_properties(sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set include directories
target_include_directories(sandbox
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

# Compiler standard
target_compile_features(sandbox PUBLIC cxx_std_17)

# Link libraries
target_link_libraries(sandbox PRIVATE vui::vui)