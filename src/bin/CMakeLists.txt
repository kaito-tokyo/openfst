# Makefile.am の 'bin_PROGRAMS' にリストされている
# 全ての実行可能ファイルターゲット名を定義します
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

# 単一のループですべてのバイナリを定義します
foreach(target_name IN LISTS FST_BINARIES)
    # 実行可能ファイルを追加 (例: fstarcsort.cc, fstarcsort-main.cc)
    add_executable(${target_name}
        ${target_name}.cc
        ${target_name}-main.cc
    )
    
    # AM_CPPFLAGS の -I$(srcdir)/../script に対応
    target_include_directories(${target_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../script
    )

    # LDADD に対応 (fstscript が fst, m, dl を継承)
    target_link_libraries(${target_name} PRIVATE
        fstscript
        lib_export_dynamic
    )
endforeach()

# ------------------------------------------------------------------
# インストール設定
# ------------------------------------------------------------------

include(GNUInstallDirs)

# この CMakeLists.txt で定義された全ての実行可能ファイルをインストール
# (FST_BINARIES リストをそのまま使用)
install(TARGETS ${FST_BINARIES}
    # 実行可能ファイル (.exe やバイナリ) のインストール先
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    # (Mac/Linuxで .exe がない場合のインストール先)
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)