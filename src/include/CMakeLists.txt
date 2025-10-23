# Install all header files under fst/ regardless of conditions
install(DIRECTORY fst/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fst FILES_MATCHING PATTERN "*.h" PATTERN "*.inc")
