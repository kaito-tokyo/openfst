
# Define all FST command binaries as in Makefile.am
set(FST_BINARIES
  fstarcsort fstclosure fstcompile fstcompose fstconcat fstconnect fstconvert
  fstdeterminize fstdifference fstdisambiguate fstdraw fstencode fstepsnormalize
  fstequal fstequivalent fstinfo fstintersect fstinvert fstisomorphic fstmap
  fstminimize fstprint fstproject fstprune fstpush fstrandgen fstrelabel
  fstreplace fstreverse fstreweight fstrmepsilon fstshortestdistance
  fstshortestpath fstsymbols fstsynchronize fsttopsort fstunion
)

foreach(bin ${FST_BINARIES})
  add_executable(${bin}
    ${bin}.cc
    ${bin}-main.cc
  )
  install(TARGETS ${bin} RUNTIME DESTINATION bin)
endforeach()
