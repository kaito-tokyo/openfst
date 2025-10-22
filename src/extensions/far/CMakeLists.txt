set(LIBFSTFAR_SOURCES
    sttable.cc
    stlist.cc
)

add_library(fstfar ${LIBFSTFAR_SOURCES})
target_link_libraries(fstfar PUBLIC fst ${LIBS})
set_property(TARGET fstfar PROPERTY SOVERSION ${SOVERSION})
install(TARGETS fstfar LIBRARY DESTINATION lib RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)

if(HAVE_SCRIPT)
    set(LIBFSTFARSCRIPT_SOURCES
        far-class.cc
        farscript.cc
        getters.cc
        script-impl.cc
        strings.cc
        sttable.cc
        stlist.cc
    )

    add_library(fstfarscript ${LIBFSTFARSCRIPT_SOURCES})
    target_link_libraries(fstfarscript PUBLIC fstfar fstscript ${LIBS})
    set_property(TARGET fstfarscript PROPERTY SOVERSION ${SOVERSION})
    install(TARGETS fstfarscript LIBRARY DESTINATION lib RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)
endif()
