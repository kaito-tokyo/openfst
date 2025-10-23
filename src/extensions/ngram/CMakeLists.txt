include(GNUInstallDirs)

# Glob all headers under 'src/include/fst/extensions/ngram' (for IDE integration)
file(GLOB_RECURSE NGRAM_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../include/fst/extensions/ngram/*.h)

# Target: ngram (corresponds to libfstngram.la)
add_library(fstngram
    bitmap-index.cc
    ngram-fst.cc
    nthbit.cc
)

# Set version information (corresponds to Makefile.am's -version-info 23:0:0)
set_target_properties(fstngram PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Add headers for IDE integration
target_sources(fstngram PRIVATE ${NGRAM_HEADERS})

# Dependencies (corresponds to Makefile.am's LIBS)
# 'fst' target inherits dependencies from libfst.la, m, dl
target_link_libraries(fstngram PUBLIC fst)

# Install the library and add it to the 'fst-targets' export set
install(TARGETS fstngram
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
