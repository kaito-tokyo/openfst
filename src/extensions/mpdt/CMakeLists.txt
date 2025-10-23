include(GNUInstallDirs)

# 'src/include/fst/extensions/mpdt' 以下の全ヘッダを glob して取得 (IDE連携用)
file(GLOB_RECURSE MPDT_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/mpdt/*.h)
file(GLOB_RECURSE MPDT_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/mpdt/*.inc)
set(MPDT_HEADERS ${MPDT_HEADERS_H} ${MPDT_HEADERS_INC})

# ------------------------------------------------------------------
# ライブラリ (libfstmpdtscript.la)
# ------------------------------------------------------------------

# Target: mpdtscript (libfstmpdtscript.la に対応)
add_library(mpdtscript
    mpdtscript.cc
)

# バージョン情報を設定 (Makefile.am の -version-info 23:0:0 に対応)
set_target_properties(mpdtscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
target_sources(mpdtscript PRIVATE ${MPDT_HEADERS})

# 依存関係 (Makefile.am の libfstmpdtscript_la_LIBADD に対応)
# fstscript が fst, m, dl を継承
target_link_libraries(mpdtscript PUBLIC fstscript)

# ライブラリをインストールし、'fst-targets' エクスポートセットに追加
install(TARGETS mpdtscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# 実行可能バイナリ (OPENFST_BUILD_BIN が ON の場合のみ)
# ------------------------------------------------------------------

if(OPENFST_BUILD_BIN)

    set(MPDT_BINARIES
        mpdtcompose
        mpdtexpand
        mpdtinfo
        mpdtreverse
    )
    
    foreach(target_name IN LISTS MPDT_BINARIES)
        add_executable(${target_name}
            ${target_name}.cc
            ${target_name}-main.cc
        )
        
        # 依存関係 (Makefile.am の LDADD に対応)
        # 'pdtscript' が ../pdt/libfstpdtscript.la に対応
        # 'mpdtscript' が libfstmpdtscript.la に対応
        target_link_libraries(${target_name} PRIVATE
            mpdtscript
            pdtscript
            lib_export_dynamic
        )
    endforeach()
    
    # バイナリをインストール
    install(TARGETS ${MPDT_BINARIES}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()