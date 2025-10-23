include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Define an INTERFACE target to manage header files.
#
# Linking to the 'fst_headers' target automatically adds 'src/include' to the include path.
# This eliminates the need to call include_directories() in each subproject.
add_library(fst_headers INTERFACE)
target_include_directories(
    fst_headers
    INTERFACE
        # $<BUILD_INTERFACE:...> : Path used when linking 'fst_headers' in the build tree
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # $<INSTALL_INTERFACE:...> : Path used when linking 'fst_headers' after installation
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
install(TARGETS fst_headers EXPORT fst-targets)

# Add subdirectories for each component
add_subdirectory(lib)
add_subdirectory(script)
if(OPENFST_BUILD_BIN)
    add_subdirectory(bin)
endif()
add_subdirectory(extensions)

# Write all targets (fst, fst_headers) accumulated in 'fst-targets'
# to the package file after all add_subdirectory calls.
install(
    EXPORT fst-targets
    FILE fst-targets.cmake
    NAMESPACE OpenFst::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/openfst
)

# Generate 'OpenFstConfig.cmake' from the 'OpenFstConfig.cmake.in' template
configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/OpenFstConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/OpenFstConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/openfst
    # Pass variables used by @PACKAGE_INIT@ in OpenFstConfig.cmake.in
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

# Install the generated 'OpenFstConfig.cmake'
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/OpenFstConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/openfst
)
