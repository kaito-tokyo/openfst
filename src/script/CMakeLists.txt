# Glob all headers under 'src/include/fst/script' (for IDE integration)
file(GLOB_RECURSE SCRIPT_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/script/*.h)
file(GLOB_RECURSE SCRIPT_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/script/*.inc)
set(SCRIPT_HEADERS ${SCRIPT_HEADERS_H} ${SCRIPT_HEADERS_INC})

# Glob all .cc source files under 'src/script'
# (corresponds to Makefile.am's libfstscript_la_SOURCES)
file(GLOB SCRIPT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
)

# Target: fstscript (single library corresponding to libfstscript.la)
add_library(fstscript)

# Version information (corresponds to Makefile.am's -version-info 23:0:0)
# (Assumes variables are defined in the root CMakeLists.txt)
set_target_properties(fstscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# Associate source and header files with the target
target_sources(fstscript PRIVATE
    ${SCRIPT_SOURCES}
    ${SCRIPT_HEADERS}
)

# Compiler options (suppress warnings)
target_compile_options(fstscript PRIVATE
    "$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wno-sign-compare>"
    "$<$<CXX_COMPILER_ID:MSVC>:/wd4018>"
)

# Dependencies (corresponds to Makefile.am's libfstscript_la_LIBADD)
# Link to fst (libfst.la) as PUBLIC and inherit include path (fst_headers)
target_link_libraries(fstscript PUBLIC fst)
# Link to m and dl (empty on Windows)
target_link_libraries(fstscript PRIVATE ${CMAKE_DL_LIBS})
if(UNIX)
    target_link_libraries(fstscript PRIVATE m)
endif()

# Install settings
# Add 'fstscript' target to the 'fst-targets' export set
# (headers are already installed in src/lib/CMakeLists.txt)
install(TARGETS fstscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)