include(GNUInstallDirs)

# 'src/include/fst/extensions/ngram' 以下の全ヘッダを glob して取得 (IDE連携用)
file(GLOB_RECURSE NGRAM_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/ngram/*.h)
file(GLOB_RECURSE NGRAM_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/ngram/*.inc)
set(NGRAM_HEADERS ${NGRAM_HEADERS_H} ${NGRAM_HEADERS_INC})

# Target: ngram (Makefile.am の libfstngram.la に対応)
add_library(ngram
    bitmap-index.cc
    ngram-fst.cc
    nthbit.cc
)

# バージョン情報を設定 (Makefile.am の -version-info 23:0:0 に対応)
set_target_properties(ngram PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
target_sources(ngram PRIVATE ${NGRAM_HEADERS})

# 依存関係 (Makefile.am の LIBS に対応)
# 'fst' ターゲットが libfst.la, m, dl の依存関係を継承
target_link_libraries(ngram PUBLIC fst)

# ライブラリをインストールし、'fst-targets' エクスポートセットに追加
install(TARGETS ngram
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
