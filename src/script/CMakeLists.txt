if(HAVE_SCRIPT)
    set(LIBFSTSCRIPT_SOURCES
        arcsort.cc
        arciterator-class.cc
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
        equal.cc
        equivalent.cc
        epsnormalize.cc
        fst-class.cc
        getters.cc
        info.cc
        info-impl.cc
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
        verify.cc
        weight-class.cc
    )

    add_library(fstscript ${LIBFSTSCRIPT_SOURCES})
    target_link_libraries(fstscript PUBLIC fst ${LIBS}) # libfst に依存
    set_property(TARGET fstscript PROPERTY SOVERSION ${SOVERSION})
    install(TARGETS fstscript LIBRARY DESTINATION lib RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)
endif()
