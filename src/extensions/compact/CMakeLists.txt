# Extension: Compact

# Include GNUInstallDirs to access CMAKE_INSTALL_LIBDIR and related variables
include(GNUInstallDirs)

add_library(fstcompact STATIC
    compact16_acceptor-fst.cc
    compact16_string-fst.cc
    compact16_unweighted-fst.cc
    compact16_unweighted_acceptor-fst.cc
    compact16_weighted_string-fst.cc
    compact64_acceptor-fst.cc
    compact64_string-fst.cc
    compact64_unweighted-fst.cc
    compact64_unweighted_acceptor-fst.cc
    compact64_weighted_string-fst.cc
    compact8_acceptor-fst.cc
    compact8_string-fst.cc
    compact8_unweighted-fst.cc
    compact8_unweighted_acceptor-fst.cc
    compact8_weighted_string-fst.cc
)

target_link_libraries(fstcompact PUBLIC fst)
set_target_properties(fstcompact PROPERTIES
    OUTPUT_NAME "fstcompact"
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)
install(TARGETS fstcompact
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
