FILE(GLOB HEADER_FILES ../include/fst/extensions/*.h)

add_library(fstextensions
  # No sources for now, placeholder for Windows build compatibility
  ${HEADER_FILES}
)
set_target_properties(fstextensions PROPERTIES
  SOVERSION "${SOVERSION}"
)

if(WIN32)
  target_link_options(fstextensions INTERFACE /WHOLEARCHIVE:$<TARGET_LINKER_FILE:fstextensions>)
endif()

install(TARGETS fstextensions
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION lib)
