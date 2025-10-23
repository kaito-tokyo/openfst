include(GNUInstallDirs)

# Glob all headers under 'src/include/fst/extensions/pdt' (for IDE integration)
file(GLOB_RECURSE PDT_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../include/fst/extensions/pdt/*.h)

# ------------------------------------------------------------------
# Library: pdtscript (corresponds to libfstpdtscript.la)
# ------------------------------------------------------------------
add_library(pdtscript
    getters.cc
    pdtscript.cc
)

# Set version information (corresponds to Makefile.am's -version-info 23:0:0)
set_target_properties(pdtscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add headers for IDE integration
target_sources(pdtscript PRIVATE ${PDT_HEADERS})

# Dependencies (corresponds to Makefile.am's libfstpdtscript_la_LIBADD)
# fstscript inherits fst, m, dl
target_link_libraries(pdtscript PUBLIC fstscript)

# Install the library and add it to the 'fst-targets' export set
install(TARGETS pdtscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# Executable binaries (only if OPENFST_BUILD_BIN is ON)
# ------------------------------------------------------------------
if(OPENFST_BUILD_BIN)

    set(PDT_BINARIES
        pdtcompose
        pdtexpand
        pdtinfo
        pdtreplace
        pdtreverse
        pdtshortestpath
    )
    
    foreach(target_name IN LISTS PDT_BINARIES)
        add_executable(${target_name}
            ${target_name}.cc
            ${target_name}-main.cc
        )
        
        # Dependencies (corresponds to Makefile.am's LDADD)
        # (pdtscript inherits fstscript, fst, m, dl)
        target_link_libraries(${target_name} PRIVATE
            pdtscript
            lib_export_dynamic
        )
    endforeach()
    
    # Install binaries
    install(TARGETS ${PDT_BINARIES}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
