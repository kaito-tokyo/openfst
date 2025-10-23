# Recursively glob all headers under 'src/include'
# Create a list of relative paths from CMAKE_CURRENT_SOURCE_DIR (src/lib)
file(
    GLOB_RECURSE PUBLIC_HEADERS_H
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ../include/*.h
)
file(
    GLOB_RECURSE PUBLIC_HEADERS_INC
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ../include/*.inc
)
set(PUBLIC_HEADERS ${PUBLIC_HEADERS_H} ${PUBLIC_HEADERS_INC})

# Target: fst (single library based on Makefile.am's libfst_la_SOURCES)
add_library(fst)

set_target_properties(
    fst
    PROPERTIES VERSION "${OPENFST_VERSION}" SOVERSION "${OPENFST_SOVERSION}"
)

# Specify public headers (for IDE integration and installation)
target_sources(
    fst
    PRIVATE
        # --- Source files (.cc) ---
        compat.cc
        encode.cc
        flags.cc
        fst.cc
        fst-types.cc
        mapped-file.cc
        properties.cc
        symbol-table.cc
        symbol-table-ops.cc
        weight.cc
        util.cc
        # --- Header files (.h) ---
        ${PUBLIC_HEADERS}
)

# Include path (via 'fst_headers' target)
target_link_libraries(fst PUBLIC fst_headers)

# Abseil dependency
if(OPENFST_HAS_ABSL)
    target_compile_definitions(fst PUBLIC OPENFST_HAS_ABSL=1)
    target_link_libraries(fst PUBLIC absl::synchronization)
endif()

# Compiler options (suppress warnings)
target_compile_options(
    fst
    PRIVATE
        "$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wno-sign-compare>"
        "$<$<CXX_COMPILER_ID:MSVC>:/wd4018>"
)

# Link libraries (dl, m)
# ${CMAKE_DL_LIBS} is empty on Windows, 'dl' on Linux
target_link_libraries(fst PRIVATE ${CMAKE_DL_LIBS})
if(UNIX)
    target_link_libraries(fst PRIVATE m)
endif()

# Target: lib_export_dynamic
# (Settings for binaries linking to fst, separate from the fst target itself)
add_library(lib_export_dynamic INTERFACE)
set_property(TARGET lib_export_dynamic PROPERTY INTERFACE_ENABLE_EXPORTS ON)
target_link_libraries(lib_export_dynamic INTERFACE fst)

# ------------------------------------------------------------------
# Installation settings
# ------------------------------------------------------------------

include(GNUInstallDirs)

# Install settings for 'fst' target
# 'EXPORT fst-targets' associates 'fst' with the export set
install(
    TARGETS fst
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install header files manually using 'install(DIRECTORY ...)'
# Install the entire 'src/include/' directory
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.inc"
)
