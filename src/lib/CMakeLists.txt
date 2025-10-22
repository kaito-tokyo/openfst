add_library(fst
  compat.cc
  encode.cc
  flags.cc
  fst.cc
  fst-types.cc
  mapped-file.cc
  properties.cc
  symbol-table.cc
  symbol-table-ops.cc
  weight.cc
  util.cc
)

target_include_directories(fst PRIVATE ../include)
set_target_properties(fst PROPERTIES SOVERSION "${SOVERSION}")

install(TARGETS fst
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
