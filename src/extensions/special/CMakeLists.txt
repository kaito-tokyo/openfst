include(GNUInstallDirs)

# 'src/include/fst/extensions/special' 以下の全ヘッダを glob して取得 (IDE連携用)
file(GLOB_RECURSE SPECIAL_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/special/*.h)
file(GLOB_RECURSE SPECIAL_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/special/*.inc)
set(SPECIAL_HEADERS ${SPECIAL_HEADERS_H} ${SPECIAL_HEADERS_INC})

# ------------------------------------------------------------------
# ライブラリ (libfstspecial.la)
# ------------------------------------------------------------------

# Target: fstspecial (libfstspecial.la に対応)
# (Makefile.am の phi-fst.la 等のモジュールもこの単一ライブラリに統合)
add_library(fstspecial
    phi-fst.cc
    rho-fst.cc
    sigma-fst.cc
)

# バージョン情報を設定 (Makefile.am の -version-info 23:0:0 に対応)
set_target_properties(fstspecial PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
target_sources(fstspecial PRIVATE ${SPECIAL_HEADERS})

# 依存関係 (Makefile.am の LIBS に対応)
target_link_libraries(fstspecial PUBLIC fst)

# ライブラリをインストールし、'fst-targets' エクスポートセットに追加
install(TARGETS fstspecial
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# 実行可能バイナリ (OPENFST_BUILD_BIN が ON の場合のみ)
# ------------------------------------------------------------------

if(OPENFST_BUILD_BIN)

    # [変更] 実行可能ファイルのCMakeターゲット名を 'fstspecial_bin' に変更
    add_executable(fstspecial_bin
        # Makefile.am の fstspecial_SOURCES に従い、fstspecial.cc を使用
        fstspecial.cc
        # (phi-fst.cc 等はライブラリ 'fstspecial' からリンクする)
    )
    
    # [追加] 実行可能ファイルの出力ファイル名 (bin_PROGRAMS) は 'fstspecial' のままにする
    set_target_properties(fstspecial_bin PROPERTIES
        OUTPUT_NAME "fstspecial"
    )

    # [変更] ターゲット名を 'fstspecial_bin' に変更
    target_include_directories(fstspecial_bin PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../bin
    )

    # [変更] ターゲット名を 'fstspecial_bin' に変更
    # (Makefile.am の LDADD と SOURCES をCMake流にリンクで解釈)
    target_link_libraries(fstspecial_bin PRIVATE
        fstscript
        fstspecial
        lib_export_dynamic
    )

    # [変更] インストールするターゲット名を 'fstspecial_bin' に変更
    install(TARGETS fstspecial_bin
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()