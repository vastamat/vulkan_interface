cmake_minimum_required(VERSION 3.12...3.21)
project(vui-framework)

# Define shared library (only .cpp)
add_library(${PROJECT_NAME} STATIC 
  src/application.cpp
  src/graphics.cpp
  src/keyboard.cpp
  src/mouse.cpp
  src/timer.cpp
  src/window.cpp
  )

# Create nice looking alias for clients of bge to link to 
add_library(vui::vui ALIAS ${PROJECT_NAME})

# Set compile options privately for this project
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -pipe -march=native
        $<$<CONFIG:Debug>:-O0 -Wall -Wextra>>
    $<$<CXX_COMPILER_ID:MSVC>:
        $<$<CONFIG:Debug>:/Od /Wall /Zi>>
)

# Set include directories
target_include_directories(${PROJECT_NAME}
   PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Find dependencies
find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
else()
   target_compile_definitions(${PROJECT_NAME} PRIVATE DVK_USE_PLATFORM_XLIB_KHR)
endif()

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Vulkan::Vulkan
        glfw
)