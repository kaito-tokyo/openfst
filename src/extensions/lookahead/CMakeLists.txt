set(LIBFSTLOOKAHEAD_SOURCES
    arc_lookahead-fst.cc
    ilabel_lookahead-fst.cc
    olabel_lookahead-fst.cc
)

add_library(fstlookahead ${LIBFSTLOOKAHEAD_SOURCES})
target_link_libraries(fstlookahead PUBLIC fst ${LIBS})
set_property(TARGET fstlookahead PROPERTY SOVERSION ${SOVERSION})
install(TARGETS fstlookahead LIBRARY DESTINATION lib RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)

add_library(arc_lookahead-fst MODULE arc_lookahead-fst.cc)
target_link_libraries(arc_lookahead-fst PUBLIC fst ${LIBS})
install(TARGETS arc_lookahead-fst LIBRARY DESTINATION lib/fst)

add_library(ilabel_lookahead-fst MODULE ilabel_lookahead-fst.cc)
target_link_libraries(ilabel_lookahead-fst PUBLIC fst ${LIBS})
install(TARGETS ilabel_lookahead-fst LIBRARY DESTINATION lib/fst)

add_library(olabel_lookahead-fst MODULE olabel_lookahead-fst.cc)
target_link_libraries(olabel_lookahead-fst PUBLIC fst ${LIBS})
install(TARGETS olabel_lookahead-fst LIBRARY DESTINATION lib/fst)
