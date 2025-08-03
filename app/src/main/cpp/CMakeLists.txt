cmake_minimum_required(VERSION 3.22.1)

project("fridablocker")

# Add library
add_library(fridablocker SHARED
    frida_detector.cpp
    jni_bridge.cpp
)

# Include directories
target_include_directories(fridablocker PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link libraries
find_library(log-lib log)
find_library(android-lib android)

target_link_libraries(fridablocker
    ${log-lib}
    ${android-lib}
)

# Set C++ standard
set_target_properties(fridablocker PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Export symbols for JNI
set_target_properties(fridablocker PROPERTIES
    LINK_FLAGS "-Wl,--export-dynamic"
)