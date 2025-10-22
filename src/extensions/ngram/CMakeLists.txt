set(LIBFSTNGRAM_SOURCES
    bitmap-index.cc
    ngram-fst.cc
    nthbit.cc
)

add_library(fstngram ${LIBFSTNGRAM_SOURCES})
target_link_libraries(fstngram PUBLIC fst ${LIBS})
set_property(TARGET fstngram PROPERTY SOVERSION ${SOVERSION})
install(TARGETS fstngram LIBRARY DESTINATION lib RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)

add_library(ngram-fst MODULE ${LIBFSTNGRAM_SOURCES})
target_link_libraries(ngram-fst PUBLIC fst ${LIBS})
install(TARGETS ngram-fst LIBRARY DESTINATION lib/fst)
