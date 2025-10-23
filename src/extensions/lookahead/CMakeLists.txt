include(GNUInstallDirs)

# 'src/include/fst/extensions/lookahead' 以下の全ヘッダを glob して取得 (IDE連携用)
file(GLOB_RECURSE LOOKAHEAD_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/lookahead/*.h)
set(LOOKAHEAD_HEADERS ${LOOKAHEAD_HEADERS_H})

# Target: fstlookahead (Makefile.am の libfstlookahead.la に対応)
add_library(fstlookahead
    arc_lookahead-fst.cc
    ilabel_lookahead-fst.cc
    olabel_lookahead-fst.cc
)

# バージョン情報を設定 (Makefile.am の -version-info 23:0:0 に対応)
set_target_properties(fstlookahead PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
target_sources(fstlookahead PRIVATE ${LOOKAHEAD_HEADERS})

# 依存関係 (Makefile.am の LIBS に対応)
# 'fst' ターゲットが libfst.la, m, dl の依存関係を継承
target_link_libraries(fstlookahead PUBLIC fst)

# ライブラリをインストールし、'fst-targets' エクスポートセットに追加
install(TARGETS fstlookahead
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
