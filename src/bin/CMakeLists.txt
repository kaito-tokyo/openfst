# Define all executable target names listed in Makefile.am's 'bin_PROGRAMS'
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

# Define all binaries in a single loop
foreach(target_name IN LISTS FST_BINARIES)
    # Add executable (e.g., fstarcsort.cc, fstarcsort-main.cc)
    add_executable(${target_name} ${target_name}.cc ${target_name}-main.cc)

    # Corresponds to AM_CPPFLAGS -I$(srcdir)/../script
    target_include_directories(
        ${target_name}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../script
    )

    # Corresponds to LDADD (fstscript inherits fst, m, dl)
    target_link_libraries(${target_name} PRIVATE fstscript lib_export_dynamic)
endforeach()

# ------------------------------------------------------------------
# Installation settings
# ------------------------------------------------------------------

include(GNUInstallDirs)

# Install all executables defined in this CMakeLists.txt
# (using the FST_BINARIES list directly)
install(
    TARGETS ${FST_BINARIES}
    # Installation path for executables (.exe or binaries)
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    # Installation path for non-.exe binaries on Mac/Linux
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)
