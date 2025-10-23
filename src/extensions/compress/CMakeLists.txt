# Include GNUInstallDirs to access CMAKE_INSTALL_LIBDIR and related variables
include(GNUInstallDirs)

# Target: compressscript (corresponds to libfstcompressscript.la)
add_library(fstcompressscript
    compressscript.cc
)

# Set version information (corresponds to Makefile.am's -version-info 23:0:0)
set_target_properties(fstcompressscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add header for IDE integration (installation handled by src/lib/CMakeLists.txt glob)
target_sources(fstcompressscript PRIVATE
    ../../include/fst/extensions/compress/compressscript.h
)

# Dependencies (corresponds to Makefile.am's libfstcompressscript_la_LIBADD)
# fstscript inherits fst, m, dl
target_link_libraries(fstcompressscript PUBLIC fstscript)

# Install the library and add it to the 'fst-targets' export set
install(TARGETS fstcompressscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# Executable binary (only if OPENFST_BUILD_BIN is ON)
# ------------------------------------------------------------------

# Corresponds to Makefile.am's 'if HAVE_BIN'
if(OPENFST_BUILD_BIN)

    # Target: fstcompress
    add_executable(fstcompress
        fstcompress.cc
        fstcompress-main.cc
    )
    
    # Dependencies (corresponds to Makefile.am's LDADD)
    # compressscript inherits fstscript, fst, m, dl
    target_link_libraries(fstcompress PRIVATE
        compressscript
        lib_export_dynamic
    )

    # Install the binary
    install(TARGETS fstcompress
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
