# CMakeLists.txt for lookahead extension

# Shared library
add_library(fstlookahead SHARED arc_lookahead-fst.cc ilabel_lookahead-fst.cc olabel_lookahead-fst.cc)
set_target_properties(fstlookahead PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstlookahead PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
if(NOT MSVC)
  target_link_libraries(fstlookahead PRIVATE fst dl m)
else()
  target_link_libraries(fstlookahead PRIVATE fst m)
endif()

# Module libraries
add_library(arc_lookahead_fst MODULE arc_lookahead-fst.cc)
set_target_properties(arc_lookahead_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(arc_lookahead_fst PRIVATE fst dl m)
else()
  target_link_libraries(arc_lookahead_fst PRIVATE fst m)
endif()

add_library(ilabel_lookahead_fst MODULE ilabel_lookahead-fst.cc)
set_target_properties(ilabel_lookahead_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(ilabel_lookahead_fst PRIVATE fst dl m)
else()
  target_link_libraries(ilabel_lookahead_fst PRIVATE fst m)
endif()

add_library(olabel_lookahead_fst MODULE olabel_lookahead-fst.cc)
set_target_properties(olabel_lookahead_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(olabel_lookahead_fst PRIVATE fst dl m)
else()
  target_link_libraries(olabel_lookahead_fst PRIVATE fst m)
endif()

install(TARGETS fstlookahead
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS arc_lookahead_fst ilabel_lookahead_fst olabel_lookahead_fst
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
