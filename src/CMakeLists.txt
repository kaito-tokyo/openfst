include_directories(./include/)
install(DIRECTORY include/ DESTINATION include/
        FILES_MATCHING PATTERN "*.h")

add_subdirectory(lib)
add_subdirectory(script)

if(HAVE_BIN)
  add_subdirectory(bin)
endif(HAVE_BIN)

add_subdirectory(extensions)
