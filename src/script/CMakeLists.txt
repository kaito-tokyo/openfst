# 'src/include/fst/script' 以下の全ヘッダを glob して取得 (IDE連携用)
file(GLOB_RECURSE SCRIPT_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/script/*.h)
file(GLOB_RECURSE SCRIPT_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/script/*.inc)
set(SCRIPT_HEADERS ${SCRIPT_HEADERS_H} ${SCRIPT_HEADERS_INC})

# 'src/script' 以下の全 .cc ソースファイルを glob して取得
# (Makefile.am の libfstscript_la_SOURCES に対応)
file(GLOB SCRIPT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
)

# Target: fstscript (libfstscript.la に対応する単一ライブラリ)
add_library(fstscript)

# バージョン情報 (Makefile.am の -version-info 23:0:0 に対応)
# (変数はルートの CMakeLists.txt で定義されていると仮定)
set_target_properties(fstscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ソースファイルとヘッダファイルをターゲットに関連付け
target_sources(fstscript PRIVATE
    ${SCRIPT_SOURCES}
    ${SCRIPT_HEADERS}
)

# コンパイラオプション (警告抑制)
target_compile_options(fstscript PRIVATE
    "$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wno-sign-compare>"
    "$<$<CXX_COMPILER_ID:MSVC>:/wd4018>"
)

# 依存関係 (Makefile.am の libfstscript_la_LIBADD に対応)
# fst (libfst.la) に PUBLIC でリンクし、インクルードパス (fst_headers) を継承
target_link_libraries(fstscript PUBLIC fst)
# m と dl (Windowsでは空)
target_link_libraries(fstscript PRIVATE ${CMAKE_DL_LIBS})
if(UNIX)
    target_link_libraries(fstscript PRIVATE m)
endif()

# インストール設定
# 'fstscript' ターゲットを 'fst-targets' エクスポートセットに追加
# (ヘッダは src/lib/CMakeLists.txt で既にインストール済み)
install(TARGETS fstscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)