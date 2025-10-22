# CMakeLists.txt for compress extension

# Shared library for script
add_library(fstcompressscript SHARED compressscript.cc)
set_target_properties(fstcompressscript PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstcompressscript PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
if(NOT MSVC)
  target_link_libraries(fstcompressscript PRIVATE fstscript fst dl m)
else()
  target_link_libraries(fstcompressscript PRIVATE fstscript fst m)
endif()

# Binary
if(HAVE_BIN)
  add_executable(fstcompress fstcompress.cc fstcompress-main.cc)
  target_include_directories(fstcompress PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
  if(NOT MSVC)
    target_link_libraries(fstcompress PRIVATE fstcompressscript fstscript fst dl m)
  else()
    target_link_libraries(fstcompress PRIVATE fstcompressscript fstscript fst m)
  endif()
  install(TARGETS fstcompress RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

install(TARGETS fstcompressscript
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
