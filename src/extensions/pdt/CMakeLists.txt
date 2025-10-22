# CMakeLists.txt for pdt extension

# Library for script
add_library(fstpdtscript SHARED getters.cc pdtscript.cc)
set_target_properties(fstpdtscript PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstpdtscript PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(fstpdtscript PRIVATE fstscript fst m)
if(NOT MSVC)
  target_link_libraries(fstpdtscript PRIVATE dl)
endif()

# Binaries
if(HAVE_BIN)
  foreach(bin pdtcompose pdtexpand pdtinfo pdtreplace pdtreverse pdtshortestpath)
    add_executable(${bin} ${bin}.cc ${bin}-main.cc)
    target_include_directories(${bin} PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
    target_link_libraries(${bin} PRIVATE fstpdtscript fstscript fst)
    if(NOT MSVC)
      target_link_libraries(${bin} PRIVATE dl m)
    endif()
    install(TARGETS ${bin} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  endforeach()
endif()

install(TARGETS fstpdtscript
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
