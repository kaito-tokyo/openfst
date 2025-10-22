
# Define all FST command binaries as in Makefile.am
set(FST_BINARIES
  fstarcsort fstclosure fstcompile fstcompose fstconcat fstconnect fstconvert
  fstdeterminize fstdifference fstdisambiguate fstdraw fstencode fstepsnormalize
  fstequal fstequivalent fstinfo fstintersect fstinvert fstisomorphic fstmap
  fstminimize fstprint fstproject fstprune fstpush fstrandgen fstrelabel
  fstreplace fstreverse fstreweight fstrmepsilon fstshortestdistance
  fstshortestpath fstsymbols fstsynchronize fsttopsort fstunion
)


# Use add_executable2 for all binaries to ensure proper linking
function (add_executable2 _name)
    add_executable(${ARGV})
    if (TARGET ${_name})
        target_link_libraries(${_name} fstscript fst ${CMAKE_DL_LIBS})
        set_target_properties(${_name} PROPERTIES FOLDER bin)
    endif()
    install(TARGETS ${_name} RUNTIME DESTINATION bin)
endfunction()

include_directories(../include ../script/)

foreach(bin ${FST_BINARIES})
  add_executable2(${bin}
    ${bin}.cc
    ${bin}-main.cc
  )
endforeach()
