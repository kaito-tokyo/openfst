add_library(fstscript
  arciterator-class.cc
  arcsort.cc
  closure.cc
  compile.cc
  compose.cc
  concat.cc
  connect.cc
  convert.cc
  decode.cc
  determinize.cc
  difference.cc
  disambiguate.cc
  draw.cc
  encode.cc
  encodemapper-class.cc
  epsnormalize.cc
  equal.cc
  equivalent.cc
  fst-class.cc
  getters.cc
  info-impl.cc
  info.cc
  intersect.cc
  invert.cc
  isomorphic.cc
  map.cc
  minimize.cc
  print.cc
  project.cc
  prune.cc
  push.cc
  randequivalent.cc
  randgen.cc
  relabel.cc
  replace.cc
  reverse.cc
  reweight.cc
  rmepsilon.cc
  shortest-distance.cc
  shortest-path.cc
  stateiterator-class.cc
  synchronize.cc
  text-io.cc
  topsort.cc
  union.cc
  weight-class.cc
  verify.cc
)

target_include_directories(fstscript PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(fstscript PRIVATE fst)
set_target_properties(fstscript PROPERTIES SOVERSION "${SOVERSION}")
set_target_properties(fstscript PROPERTIES
  SOVERSION "${SOVERSION}"
)

if(MSVC)
  target_link_options(fstscript INTERFACE /WHOLEARCHIVE:$<TARGET_LINKER_FILE:fstscript>)
else()
  target_link_libraries(fstscript PRIVATE dl)
endif()

install(TARGETS fstscript
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
