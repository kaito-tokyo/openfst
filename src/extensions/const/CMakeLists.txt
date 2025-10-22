# CMakeLists.txt for const extension

# Shared library
add_library(fstconst SHARED const8-fst.cc const16-fst.cc const64-fst.cc)
set_target_properties(fstconst PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstconst PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
if(NOT MSVC)
  target_link_libraries(fstconst PRIVATE fst dl m)
else()
  target_link_libraries(fstconst PRIVATE fst m)
endif()

# Module libraries
add_library(const8_fst MODULE const8-fst.cc)
set_target_properties(const8_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(const8_fst PRIVATE fst dl m)
else()
  target_link_libraries(const8_fst PRIVATE fst m)
endif()

add_library(const16_fst MODULE const16-fst.cc)
set_target_properties(const16_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(const16_fst PRIVATE fst dl m)
else()
  target_link_libraries(const16_fst PRIVATE fst m)
endif()

add_library(const64_fst MODULE const64-fst.cc)
set_target_properties(const64_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(const64_fst PRIVATE fst dl m)
else()
  target_link_libraries(const64_fst PRIVATE fst m)
endif()

install(TARGETS fstconst
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS const8_fst const16_fst const64_fst
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
