include(GNUInstallDirs)

# Target: fstconst (corresponds to libfstconst.la)
add_library(fstconst
    const8-fst.cc
    const16-fst.cc
    const64-fst.cc
)

# Set version information (corresponds to Makefile.am's -version-info 23:0:0)
set_target_properties(fstconst PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Dependencies (corresponds to Makefile.am's LIBS)
# 'fst' target inherits dependencies from libfst.la, m, dl
target_link_libraries(fstconst PUBLIC fst)

# Install the library and add it to the 'fst-targets' export set
install(TARGETS fstconst
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
