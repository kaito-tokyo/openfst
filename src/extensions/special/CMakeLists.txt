# CMakeLists.txt for special extension

add_library(fstspecial SHARED phi-fst.cc rho-fst.cc sigma-fst.cc)
set_target_properties(fstspecial PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstspecial PRIVATE ${CMAKE_SOURCE_DIR}/src/include ${CMAKE_SOURCE_DIR}/src/bin)
if(NOT MSVC)
  target_link_libraries(fstspecial PRIVATE fst dl)
else()
  target_link_libraries(fstspecial PRIVATE fst)
endif()

# Module libraries
add_library(phi_fst MODULE phi-fst.cc)
set_target_properties(phi_fst PROPERTIES PREFIX "" SUFFIX ".so")
target_link_libraries(phi_fst PRIVATE fst)
if(NOT MSVC)
  target_link_libraries(phi_fst PRIVATE fst dl)
else()
  target_link_libraries(phi_fst PRIVATE fst)
endif()

add_library(rho_fst MODULE rho-fst.cc)
set_target_properties(rho_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(rho_fst PRIVATE fst dl)
else()
  target_link_libraries(rho_fst PRIVATE fst)
endif()

add_library(sigma_fst MODULE sigma-fst.cc)
set_target_properties(sigma_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(sigma_fst PRIVATE fst dl)
else()
  target_link_libraries(sigma_fst PRIVATE fst)
endif()

# Optional binary
if(HAVE_BIN)
  add_executable(fstspecial fstspecial.cc phi-fst.cc rho-fst.cc sigma-fst.cc)
  target_include_directories(fstspecial PRIVATE ${CMAKE_SOURCE_DIR}/src/include ${CMAKE_SOURCE_DIR}/src/bin)
  if(NOT MSVC)
    target_link_libraries(fstspecial PRIVATE fstscript fst dl)
  else()
    target_link_libraries(fstspecial PRIVATE fstscript fst)
  endif()
  install(TARGETS fstspecial RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

install(TARGETS fstspecial
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS phi_fst rho_fst sigma_fst
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
