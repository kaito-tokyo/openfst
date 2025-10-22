set(LIBFST_SOURCES
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

add_library(fst ${LIBFST_SOURCES})
target_link_libraries(fst PUBLIC ${LIBS})

find_package(Threads)
find_library(DL_LIBRARY dl)
if(DL_LIBRARY)
    target_link_libraries(fst PUBLIC ${DL_LIBRARY} Threads::Threads)
else()
    target_link_libraries(fst PUBLIC Threads::Threads)
endif()

set_property(TARGET fst PROPERTY SOVERSION ${SOVERSION})
install(TARGETS fst LIBRARY DESTINATION lib RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)
