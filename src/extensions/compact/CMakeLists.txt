# CMakeLists.txt for compact extension

# Shared library
add_library(fstcompact SHARED
  compact8_acceptor-fst.cc compact8_string-fst.cc compact8_unweighted-fst.cc compact8_unweighted_acceptor-fst.cc compact8_weighted_string-fst.cc
  compact16_acceptor-fst.cc compact16_string-fst.cc compact16_unweighted-fst.cc compact16_unweighted_acceptor-fst.cc compact16_weighted_string-fst.cc
  compact64_acceptor-fst.cc compact64_string-fst.cc compact64_unweighted-fst.cc compact64_unweighted_acceptor-fst.cc compact64_weighted_string-fst.cc
)
set_target_properties(fstcompact PROPERTIES VERSION 23.0.0 SOVERSION 23)
target_include_directories(fstcompact PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
if(NOT MSVC)
  target_link_libraries(fstcompact PRIVATE fst dl m)
else()
  target_link_libraries(fstcompact PRIVATE fst m)
endif()

# Module libraries
add_library(compact8_acceptor_fst MODULE compact8_acceptor-fst.cc)
set_target_properties(compact8_acceptor_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact8_acceptor_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact8_acceptor_fst PRIVATE fst m)
endif()

add_library(compact8_string_fst MODULE compact8_string-fst.cc)
set_target_properties(compact8_string_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact8_string_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact8_string_fst PRIVATE fst m)
endif()

add_library(compact8_unweighted_fst MODULE compact8_unweighted-fst.cc)
set_target_properties(compact8_unweighted_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact8_unweighted_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact8_unweighted_fst PRIVATE fst m)
endif()

add_library(compact8_unweighted_acceptor_fst MODULE compact8_unweighted_acceptor-fst.cc)
set_target_properties(compact8_unweighted_acceptor_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact8_unweighted_acceptor_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact8_unweighted_acceptor_fst PRIVATE fst m)
endif()

add_library(compact8_weighted_string_fst MODULE compact8_weighted_string-fst.cc)
set_target_properties(compact8_weighted_string_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact8_weighted_string_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact8_weighted_string_fst PRIVATE fst m)
endif()

add_library(compact16_acceptor_fst MODULE compact16_acceptor-fst.cc)
set_target_properties(compact16_acceptor_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact16_acceptor_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact16_acceptor_fst PRIVATE fst m)
endif()

add_library(compact16_string_fst MODULE compact16_string-fst.cc)
set_target_properties(compact16_string_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact16_string_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact16_string_fst PRIVATE fst m)
endif()

add_library(compact16_unweighted_fst MODULE compact16_unweighted-fst.cc)
set_target_properties(compact16_unweighted_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact16_unweighted_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact16_unweighted_fst PRIVATE fst m)
endif()

add_library(compact16_unweighted_acceptor_fst MODULE compact16_unweighted_acceptor-fst.cc)
set_target_properties(compact16_unweighted_acceptor_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact16_unweighted_acceptor_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact16_unweighted_acceptor_fst PRIVATE fst m)
endif()

add_library(compact16_weighted_string_fst MODULE compact16_weighted_string-fst.cc)
set_target_properties(compact16_weighted_string_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact16_weighted_string_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact16_weighted_string_fst PRIVATE fst m)
endif()

add_library(compact64_acceptor_fst MODULE compact64_acceptor-fst.cc)
set_target_properties(compact64_acceptor_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact64_acceptor_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact64_acceptor_fst PRIVATE fst m)
endif()

add_library(compact64_string_fst MODULE compact64_string-fst.cc)
set_target_properties(compact64_string_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact64_string_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact64_string_fst PRIVATE fst m)
endif()

add_library(compact64_unweighted_fst MODULE compact64_unweighted-fst.cc)
set_target_properties(compact64_unweighted_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact64_unweighted_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact64_unweighted_fst PRIVATE fst m)
endif()

add_library(compact64_unweighted_acceptor_fst MODULE compact64_unweighted_acceptor-fst.cc)
set_target_properties(compact64_unweighted_acceptor_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact64_unweighted_acceptor_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact64_unweighted_acceptor_fst PRIVATE fst m)
endif()

add_library(compact64_weighted_string_fst MODULE compact64_weighted_string-fst.cc)
set_target_properties(compact64_weighted_string_fst PROPERTIES PREFIX "" SUFFIX ".so")
if(NOT MSVC)
  target_link_libraries(compact64_weighted_string_fst PRIVATE fst dl m)
else()
  target_link_libraries(compact64_weighted_string_fst PRIVATE fst m)
endif()

install(TARGETS fstcompact
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS
  compact8_acceptor_fst compact8_string_fst compact8_unweighted_fst compact8_unweighted_acceptor_fst compact8_weighted_string_fst
  compact16_acceptor_fst compact16_string_fst compact16_unweighted_fst compact16_unweighted_acceptor_fst compact16_weighted_string_fst
  compact64_acceptor_fst compact64_string_fst compact64_unweighted_fst compact64_unweighted_acceptor_fst compact64_weighted_string_fst
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
