cmake_minimum_required(VERSION 3.10)
project(gst-qtighost)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)

# Find GStreamer packages
pkg_check_modules(GST REQUIRED 
    gstreamer-1.0>=1.0
    gstreamer-base-1.0>=1.0
    gstreamer-video-1.0>=1.0
)

# Get GStreamer version separately for display
pkg_get_variable(GST_VERSION gstreamer-1.0 version)

# Include directories
include_directories(${GST_INCLUDE_DIRS})

# Add compiler flags
add_definitions(${GST_CFLAGS})

# Define package variables as compiler definitions
add_definitions(
    "-DPACKAGE=\"gst-qtighost\""
    "-DPACKAGE_VERSION=\"1.0.0\""
    "-DPACKAGE_NAME=\"GStreamer QTI Ghost Plugin\""
    "-DGST_LICENSE=\"LGPL\""
    "-DGST_PACKAGE_NAME=\"GStreamer QTI Ghost Plugin\""
    "-DGST_PACKAGE_ORIGIN=\"https://github.com/your-repo/gst-qtighost\""
    -DHAVE_CONFIG_H
)

# Create the plugin library
add_library(gstqtighost SHARED
    qtighost.cpp
)

# Link libraries
target_link_libraries(gstqtighost ${GST_LIBRARIES})

# Set library properties
set_target_properties(gstqtighost PROPERTIES
    PREFIX ""  # Remove 'lib' prefix
    SUFFIX ".so"
)

# Installation
install(TARGETS gstqtighost
    LIBRARY DESTINATION lib/gstreamer-1.0
)

# Get GStreamer version separately for display
pkg_get_variable(GST_VERSION gstreamer-1.0 version)

# Print build information
message(STATUS "Building GStreamer QTI Ghost plugin")
message(STATUS "GStreamer version: ${GST_VERSION}")
message(STATUS "Install destination: ${CMAKE_INSTALL_PREFIX}/lib/gstreamer-1.0")