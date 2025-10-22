# CMakeLists.txt for far extension

# Core library
add_library(fstfar SHARED sttable.cc stlist.cc)
set_target_properties(fstfar PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstfar PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
if(NOT MSVC)
  target_link_libraries(fstfar PRIVATE fst dl m)
else()
  target_link_libraries(fstfar PRIVATE fst m)
endif()

# Script library
if(HAVE_SCRIPT)
  add_library(fstfarscript SHARED far-class.cc farscript.cc getters.cc script-impl.cc strings.cc sttable.cc stlist.cc)
  set_target_properties(fstfarscript PROPERTIES VERSION 23.0.0 SOVERSION 23)
  target_include_directories(fstfarscript PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
  if(NOT MSVC)
    target_link_libraries(fstfarscript PRIVATE fstfar fstscript fst dl m)
  else()
    target_link_libraries(fstfarscript PRIVATE fstfar fstscript fst m)
  endif()
endif()

# Binaries
if(HAVE_BIN)
  foreach(bin farcompilestrings farconvert farcreate farequal farextract farinfo farisomorphic farprintstrings)
    add_executable(${bin} ${bin}.cc ${bin}-main.cc)
    target_include_directories(${bin} PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
    if(HAVE_SCRIPT)
      if(NOT MSVC)
        target_link_libraries(${bin} PRIVATE fstfarscript fstscript fst dl m)
      else()
        target_link_libraries(${bin} PRIVATE fstfarscript fstscript fst m)
      endif()
    else()
      if(NOT MSVC)
        target_link_libraries(${bin} PRIVATE fstfar fst dl m)
      else()
        target_link_libraries(${bin} PRIVATE fstfar fst m)
      endif()
    endif()
    install(TARGETS ${bin} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  endforeach()
endif()

install(TARGETS fstfar
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

if(HAVE_SCRIPT)
  install(TARGETS fstfarscript
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
