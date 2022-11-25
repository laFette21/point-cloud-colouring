cmake_minimum_required(VERSION 3.16...3.23)

# Set the project name and language
project(point-cloud-colouring
    VERSION 1.0.0
    DESCRIPTION ""
    HOMEPAGE_URL ""
    LANGUAGES CXX C
)

# Include cmake files
include(cmake/settings.cmake)
include(cmake/compilerWarnings.cmake)

find_package(OpenCV REQUIRED)

# Enable project warnings
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings FALSE)

# Add the src directory
add_subdirectory(src)
