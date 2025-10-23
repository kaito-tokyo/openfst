include(GNUInstallDirs)

# Glob all headers under 'src/include/fst/extensions/special' (for IDE integration)
file(GLOB_RECURSE SPECIAL_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../include/fst/extensions/special/*.h)

# ------------------------------------------------------------------
# Library: fstspecial (corresponds to libfstspecial.la)
# Combines modules like phi-fst.la into a single library
# ------------------------------------------------------------------
add_library(fstspecial
    phi-fst.cc
    rho-fst.cc
    sigma-fst.cc
)

# Set version information (corresponds to Makefile.am's -version-info 23:0:0)
set_target_properties(fstspecial PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add headers for IDE integration
target_sources(fstspecial PRIVATE ${SPECIAL_HEADERS})

# Dependencies (corresponds to Makefile.am's LIBS)
target_link_libraries(fstspecial PUBLIC fst)

# Install the library and add it to the 'fst-targets' export set
install(TARGETS fstspecial
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# Executable binary (only if OPENFST_BUILD_BIN is ON)
# ------------------------------------------------------------------
if(OPENFST_BUILD_BIN)

    # Use 'fstspecial_bin' as the CMake target name for the executable
    add_executable(fstspecial_bin
        # Use fstspecial.cc as per Makefile.am's fstspecial_SOURCES
        fstspecial.cc
        # (phi-fst.cc etc. are linked from the 'fstspecial' library)
    )
    
    # Set the output file name to 'fstspecial' (matches bin_PROGRAMS)
    set_target_properties(fstspecial_bin PROPERTIES
        OUTPUT_NAME "fstspecial"
    )

    target_include_directories(fstspecial_bin PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../bin
    )

    # Link dependencies (as per Makefile.am's LDADD and SOURCES)
    target_link_libraries(fstspecial_bin PRIVATE
        fstscript
        fstspecial
        lib_export_dynamic
    )

    # Install the executable
    install(TARGETS fstspecial_bin
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
