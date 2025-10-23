# Minimum required CMake version
cmake_minimum_required(VERSION 3.16)

# Project name and language
project(openfst LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add MSVC-specific compile options and definitions
if(MSVC)
    add_compile_options(/bigobj)
    add_compile_definitions(NOMINMAX FST_NO_DYNAMIC_LINKING)
endif()

# OpenFst versioning
set(OPENFST_VERSION 23.0.0)
set(OPENFST_SOVERSION 23)

# ------------------------------------------------------------------
# Options
# ------------------------------------------------------------------

# Enable Abseil support (similar to Bazel 'config_setting' and 'select')
option(OPENFST_HAS_ABSL "Enable Abseil support" OFF)

# Build shared libraries if ON, otherwise build static libraries (default: OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Build executable binaries in bin/ (default: ON)
option(OPENFST_BUILD_BIN "Build executable binaries" ON)

# ------------------------------------------------------------------
# External Dependencies
# ------------------------------------------------------------------

if(OPENFST_HAS_ABSL)
    # Find required Abseil components
    find_package(absl REQUIRED COMPONENTS synchronization)
    message(STATUS "Found Abseil (via find_package)")
else()
    message(STATUS "Abseil support disabled (OPENFST_HAS_ABSL=OFF)")
endif()

# ------------------------------------------------------------------
# Add Source Directories
# ------------------------------------------------------------------

# Add 'src' directory to the build
add_subdirectory(src)
