# CMakeLists.txt for mpdt extension

# Shared library for script
add_library(fstmpdtscript SHARED mpdtscript.cc)
set_target_properties(fstmpdtscript PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstmpdtscript PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
if(NOT MSVC)
  target_link_libraries(fstmpdtscript PRIVATE fstscript fst dl m)
else()
  target_link_libraries(fstmpdtscript PRIVATE fstscript fst m)
endif()

# Binaries
if(HAVE_BIN)
  foreach(bin mpdtcompose mpdtexpand mpdtinfo mpdtreverse)
    add_executable(${bin} ${bin}.cc ${bin}-main.cc)
    target_include_directories(${bin} PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
    if(NOT MSVC)
      target_link_libraries(${bin} PRIVATE fstmpdtscript fstpdtscript fstscript fst dl m)
    else()
      target_link_libraries(${bin} PRIVATE fstmpdtscript fstpdtscript fstscript fst m)
    endif()
    install(TARGETS ${bin} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  endforeach()
endif()

install(TARGETS fstmpdtscript
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
