FILE(GLOB HEADER_FILES ../include/fst/*.h)

add_executable(fstbin
  # Add your binary source files here
  ${HEADER_FILES}
)
set_target_properties(fstbin PROPERTIES
  SOVERSION "${SOVERSION}"
)

if(WIN32)
  target_link_options(fstbin INTERFACE /WHOLEARCHIVE:$<TARGET_LINKER_FILE:fstbin>)
endif()

install(TARGETS fstbin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin)
