include(GNUInstallDirs)

add_subdirectory(lib)
add_subdirectory(script)
add_subdirectory(include)

if(HAVE_BIN)
  add_subdirectory(bin)
endif(HAVE_BIN)

add_subdirectory(extensions)
