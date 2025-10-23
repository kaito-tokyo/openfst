# Extension: Compact

set(COMPACT_TYPES
    compact16_acceptor
    compact16_string
    compact16_unweighted
    compact16_unweighted_acceptor
    compact16_weighted_string
    compact64_acceptor
    compact64_string
    compact64_unweighted
    compact64_unweighted_acceptor
    compact64_weighted_string
    compact8_acceptor
    compact8_string
    compact8_unweighted
    compact8_unweighted_acceptor
    compact8_weighted_string
)

# Include GNUInstallDirs to access CMAKE_INSTALL_LIBDIR and related variables
include(GNUInstallDirs)

# Define all Compact libraries in a loop
foreach(type IN LISTS COMPACT_TYPES)
    # Define target (e.g., compact16_acceptor-fst)
    add_library(${type}-fst
        ${type}-fst.cc
    )

    # Set version information (using variables defined in the root CMakeLists.txt)
    set_target_properties(${type}-fst PROPERTIES
        VERSION "${OPENFST_VERSION}"
        SOVERSION "${OPENFST_SOVERSION}"
    )

    # Link to the main 'fst' library
    target_link_libraries(${type}-fst PUBLIC fst)

    # Install the library and add it to the 'fst-targets' export set
    install(TARGETS ${type}-fst
        EXPORT fst-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endforeach()
