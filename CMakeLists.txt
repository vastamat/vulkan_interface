cmake_minimum_required(VERSION 3.12...3.21)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Project
project(vui VERSION 1.0
                  DESCRIPTION "Vulkan rendering"
                  LANGUAGES CXX)
                  
# Options
option(VUI_BUILD_SANDBOX "Build sandbox application" ON)

# framework
add_subdirectory(vui)

# sandbox
if(VUI_BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()