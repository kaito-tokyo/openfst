include(GNUInstallDirs)

# 'src/include/fst/extensions/pdt' 以下の全ヘッダを glob して取得 (IDE連携用)
file(GLOB_RECURSE PDT_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/pdt/*.h)
file(GLOB_RECURSE PDT_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/pdt/*.inc)
set(PDT_HEADERS ${PDT_HEADERS_H} ${PDT_HEADERS_INC})

# ------------------------------------------------------------------
# ライブラリ (libfstpdtscript.la)
# ------------------------------------------------------------------

# Target: pdtscript (libfstpdtscript.la に対応)
add_library(pdtscript
    getters.cc
    pdtscript.cc
)

# バージョン情報を設定 (Makefile.am の -version-info 23:0:0 に対応)
set_target_properties(pdtscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
target_sources(pdtscript PRIVATE ${PDT_HEADERS})

# 依存関係 (Makefile.am の libfstpdtscript_la_LIBADD に対応)
# fstscript が fst, m, dl を継承
target_link_libraries(pdtscript PUBLIC fstscript)

# ライブラリをインストールし、'fst-targets' エクスポートセットに追加
install(TARGETS pdtscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# 実行可能バイナリ (OPENFST_BUILD_BIN が ON の場合のみ)
# ------------------------------------------------------------------

if(OPENFST_BUILD_BIN)

    set(PDT_BINARIES
        pdtcompose
        pdtexpand
        pdtinfo
        pdtreplace
        pdtreverse
        pdtshortestpath
    )
    
    foreach(target_name IN LISTS PDT_BINARIES)
        add_executable(${target_name}
            ${target_name}.cc
            ${target_name}-main.cc
        )
        
        # 依存関係 (Makefile.am の LDADD に対応)
        # (pdtscript が fstscript, fst, m, dl を継承)
        target_link_libraries(${target_name} PRIVATE
            pdtscript
            lib_export_dynamic
        )
    endforeach()
    
    # バイナリをインストール
    install(TARGETS ${PDT_BINARIES}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
