include(GNUInstallDirs)

# Glob all headers under 'src/include/fst/extensions/linear' (for IDE integration)
file(GLOB_RECURSE LINEAR_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/linear/*.h)
file(GLOB_RECURSE LINEAR_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/linear/*.inc)
set(LINEAR_HEADERS ${LINEAR_HEADERS_H} ${LINEAR_HEADERS_INC})

# ------------------------------------------------------------------
# Library: linear-fst (combines linear_tagger-fst.la and linear_classifier-fst.la)
# ------------------------------------------------------------------
add_library(linear-fst
    linear-classifier-fst.cc
    linear-tagger-fst.cc
)

set_target_properties(linear-fst PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add headers for IDE integration
target_sources(linear-fst PRIVATE ${LINEAR_HEADERS})

# Dependencies (Makefile.am's LIBS)
target_link_libraries(linear-fst PUBLIC fst)

# Install settings
install(TARGETS linear-fst
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# Library: linearscript (corresponds to libfstlinearscript.la)
# ------------------------------------------------------------------
add_library(linearscript
    linearscript.cc
)

set_target_properties(linearscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add headers for IDE integration
target_sources(linearscript PRIVATE ${LINEAR_HEADERS})

# Dependencies (libfstlinearscript_la_LIBADD and original file)
target_link_libraries(linearscript PUBLIC
    fstscript
    linear-fst
)

# Install settings
install(TARGETS linearscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# Executable binaries (only if OPENFST_BUILD_BIN is ON)
# ------------------------------------------------------------------

if(OPENFST_BUILD_BIN)

    set(LINEAR_BINARIES
        fstlinear
        fstloglinearapply
    )
    
    foreach(target_name IN LISTS LINEAR_BINARIES)
        add_executable(${target_name}
            ${target_name}.cc
            ${target_name}-main.cc
        )
        
        # Dependencies (Makefile.am's LDADD)
        target_link_libraries(${target_name} PRIVATE
            linearscript
            lib_export_dynamic
        )
    endforeach()
    
    # Install binaries
    install(TARGETS ${LINEAR_BINARIES}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
