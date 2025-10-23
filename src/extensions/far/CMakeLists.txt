include(GNUInstallDirs)

# Glob all headers under 'src/include/fst/extensions/far' (for IDE integration)
file(GLOB_RECURSE FAR_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../include/fst/extensions/far/*.h)
file(GLOB_RECURSE FAR_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../include/fst/extensions/far/*.inc)
set(FAR_HEADERS ${FAR_HEADERS_H} ${FAR_HEADERS_INC})

# ------------------------------------------------------------------
# Library: fstfar (corresponds to libfstfar.la)
# ------------------------------------------------------------------
add_library(fstfar
    sttable.cc
    stlist.cc
)

set_target_properties(fstfar PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add headers for IDE integration
target_sources(fstfar PRIVATE ${FAR_HEADERS})

# Dependencies (libfstfar_la_LIBADD)
target_link_libraries(fstfar PUBLIC fst)

# Install settings
install(TARGETS fstfar
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# Library: fstfarscript (corresponds to libfstfarscript.la)
# ------------------------------------------------------------------
add_library(fstfarscript
    far-class.cc
    farscript.cc
    getters.cc
    script-impl.cc
    strings.cc
    # (sttable.cc and stlist.cc are linked from the fstfar target)
)

set_target_properties(fstfarscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add headers for IDE integration
target_sources(fstfarscript PRIVATE ${FAR_HEADERS})

# Dependencies (libfstfarscript_la_LIBADD)
target_link_libraries(fstfarscript PUBLIC fstfar fstscript)

# Install settings
install(TARGETS fstfarscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# Executable binaries (only if OPENFST_BUILD_BIN is ON)
# ------------------------------------------------------------------

if(OPENFST_BUILD_BIN)

    set(FAR_BINARIES
        farcompilestrings
        farconvert
        farcreate
        farequal
        farextract
        farinfo
        farisomorphic
        farprintstrings
    )
    
    foreach(target_name IN LISTS FAR_BINARIES)
        add_executable(${target_name}
            ${target_name}.cc
            ${target_name}-main.cc
        )
        
        # Dependencies (Makefile.am's LDADD)
        # (fstfarscript inherits fstfar, fstscript, fst, m, dl)
        target_link_libraries(${target_name} PRIVATE
            fstfarscript
            lib_export_dynamic
        )
    endforeach()
    
    # Install binaries
    install(TARGETS ${FAR_BINARIES}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
