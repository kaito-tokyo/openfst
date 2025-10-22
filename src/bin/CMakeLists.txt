set(FST_BINARIES
    fstarcsort
    fstclosure
    fstcompile
    fstcompose
    fstconcat
    fstconnect
    fstconvert
    fstdeterminize
    fstdifference
    fstdisambiguate
    fstdraw
    fstencode
    fstepsnormalize
    fstequal
    fstequivalent
    fstinfo
    fstintersect
    fstinvert
    fstisomorphic
    fstmap
    fstminimize
    fstprint
    fstproject
    fstprune
    fstpush
    fstrandgen
    fstrelabel
    fstreplace
    fstreverse
    fstreweight
    fstrmepsilon
    fstshortestdistance
    fstshortestpath
    fstsymbols
    fstsynchronize
    fsttopsort
    fstunion
)

foreach(bin ${FST_BINARIES})
    add_executable(${bin} ${bin}.cc ${bin}-main.cc)
    if(TARGET ${bin})
        target_include_directories(
            ${bin}
            PRIVATE
                ${CMAKE_SOURCE_DIR}/src/include
                ${CMAKE_SOURCE_DIR}/src/script
        )
        target_link_libraries(${bin} fstscript fst)
        if(NOT MSVC)
            target_link_libraries(${bin} dl)
        endif()
        set_target_properties(${bin} PROPERTIES FOLDER bin)
    endif()
    install(TARGETS ${bin} RUNTIME DESTINATION bin)
endforeach()
