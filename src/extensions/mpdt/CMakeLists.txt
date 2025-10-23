include(GNUInstallDirs)

# Glob all headers under 'src/include/fst/extensions/mpdt' (for IDE integration)
file(GLOB_RECURSE MPDT_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../include/fst/extensions/mpdt/*.h)

# ------------------------------------------------------------------
# Library: mpdtscript (corresponds to libfstmpdtscript.la)
# ------------------------------------------------------------------
add_library(fstmpdtscript
    mpdtscript.cc
)

# Set version information (corresponds to Makefile.am's -version-info 23:0:0)
set_target_properties(fstmpdtscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add headers for IDE integration
target_sources(fstmpdtscript PRIVATE ${MPDT_HEADERS})

# Dependencies (corresponds to Makefile.am's libfstmpdtscript_la_LIBADD)
# fstscript inherits fst, m, dl
target_link_libraries(fstmpdtscript PUBLIC fstscript)

# Install the library and add it to the 'fst-targets' export set
install(TARGETS fstmpdtscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# Executable binaries (only if OPENFST_BUILD_BIN is ON)
# ------------------------------------------------------------------
if(OPENFST_BUILD_BIN)

    set(MPDT_BINARIES
        mpdtcompose
        mpdtexpand
        mpdtinfo
        mpdtreverse
    )
    
    foreach(target_name IN LISTS MPDT_BINARIES)
        add_executable(${target_name}
            ${target_name}.cc
            ${target_name}-main.cc
        )
        
        # Dependencies (corresponds to Makefile.am's LDADD)
        # 'pdtscript' corresponds to ../pdt/libfstpdtscript.la
        # 'mpdtscript' corresponds to libfstmpdtscript.la
        target_link_libraries(${target_name} PRIVATE
            mpdtscript
            pdtscript
            lib_export_dynamic
        )
    endforeach()
    
    # Install binaries
    install(TARGETS ${MPDT_BINARIES}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
