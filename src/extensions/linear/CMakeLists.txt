# CMakeLists.txt for linear extension

# Shared library for script
add_library(fstlinearscript SHARED linearscript.cc)
set_target_properties(fstlinearscript PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstlinearscript PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
if(NOT MSVC)
  target_link_libraries(fstlinearscript PRIVATE fstscript fst dl m)
else()
  target_link_libraries(fstlinearscript PRIVATE fstscript fst m)
endif()

# Binaries
if(HAVE_BIN)
  add_executable(fstlinear fstlinear.cc fstlinear-main.cc)
  target_include_directories(fstlinear PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
  if(NOT MSVC)
    target_link_libraries(fstlinear PRIVATE fstlinearscript fstscript fst dl m)
  else()
    target_link_libraries(fstlinear PRIVATE fstlinearscript fstscript fst m)
  endif()
  install(TARGETS fstlinear RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  add_executable(fstloglinearapply fstloglinearapply.cc fstloglinearapply-main.cc)
  target_include_directories(fstloglinearapply PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
  if(NOT MSVC)
    target_link_libraries(fstloglinearapply PRIVATE fstlinearscript fstscript fst dl m)
  else()
    target_link_libraries(fstloglinearapply PRIVATE fstlinearscript fstscript fst m)
  endif()
  install(TARGETS fstloglinearapply RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

# Module libraries
add_library(linear_tagger_fst MODULE linear-tagger-fst.cc)
set_target_properties(linear_tagger_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(linear_tagger_fst PRIVATE fst dl m)
else()
  target_link_libraries(linear_tagger_fst PRIVATE fst m)
endif()

add_library(linear_classifier_fst MODULE linear-classifier-fst.cc)
set_target_properties(linear_classifier_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(linear_classifier_fst PRIVATE fst dl m)
else()
  target_link_libraries(linear_classifier_fst PRIVATE fst m)
endif()

install(TARGETS fstlinearscript
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS linear_tagger_fst linear_classifier_fst
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
