# CMakeLists.txt for ngram extension

# Shared library
add_library(fstngram SHARED bitmap-index.cc ngram-fst.cc nthbit.cc)
set_target_properties(fstngram PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstngram PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
if(NOT MSVC)
  target_link_libraries(fstngram PRIVATE fst dl m)
else()
  target_link_libraries(fstngram PRIVATE fst m)
endif()

# Module library
add_library(ngram_fst MODULE bitmap-index.cc ngram-fst.cc nthbit.cc)
set_target_properties(ngram_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(ngram_fst PRIVATE fst dl m)
else()
  target_link_libraries(ngram_fst PRIVATE fst m)
endif()

install(TARGETS fstngram
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS ngram_fst
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
