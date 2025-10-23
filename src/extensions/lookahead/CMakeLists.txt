include(GNUInstallDirs)

# Glob all headers under 'src/include/fst/extensions/lookahead' (for IDE integration)
file(GLOB_RECURSE LOOKAHEAD_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../include/fst/extensions/lookahead/*.h)

# Target: fstlookahead (corresponds to libfstlookahead.la)
add_library(fstlookahead
    arc_lookahead-fst.cc
    ilabel_lookahead-fst.cc
    olabel_lookahead-fst.cc
)

# Set version information (corresponds to Makefile.am's -version-info 23:0:0)
set_target_properties(fstlookahead PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add headers for IDE integration
target_sources(fstlookahead PRIVATE ${LOOKAHEAD_HEADERS})

# Dependencies (corresponds to Makefile.am's LIBS)
# 'fst' target inherits dependencies from libfst.la, m, dl
target_link_libraries(fstlookahead PUBLIC fst)

# Install the library and add it to the 'fst-targets' export set
install(TARGETS fstlookahead
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
