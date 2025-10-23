# [変更] 'src/include' 以下のヘッダを再帰的に glob して取得
# CMAKE_CURRENT_SOURCE_DIR (src/lib) からの相対パスでリストを作成
file(GLOB_RECURSE PUBLIC_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/*.h)
file(GLOB_RECURSE PUBLIC_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/*.inc)
set(PUBLIC_HEADERS ${PUBLIC_HEADERS_H} ${PUBLIC_HEADERS_INC})

# Target: fst (Makefile.am の libfst_la_SOURCES に基づく単一ライブラリ)
add_library(fst)

set_target_properties(fst PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# 公開ヘッダの指定 (IDE連携とインストールのため)
target_sources(fst PRIVATE
    # --- ソースファイル (.cc) ---
    compat.cc
    encode.cc
    flags.cc
    fst.cc
    fst-types.cc
    mapped-file.cc
    properties.cc
    symbol-table.cc
    symbol-table-ops.cc
    weight.cc
    util.cc

    # --- ヘッダファイル (.h) ---
    ${PUBLIC_HEADERS}
)

# インクルードパス ('fst_headers' ターゲットを経由)
target_link_libraries(fst PUBLIC fst_headers)

# Abseil 依存関係
if(OPENFST_HAS_ABSL)
    target_compile_definitions(fst PUBLIC OPENFST_HAS_ABSL=1)
    target_link_libraries(fst PUBLIC absl::synchronization)
endif()

# コンパイラオプション (警告抑制)
target_compile_options(fst PRIVATE
    "$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wno-sign-compare>"
    "$<$<CXX_COMPILER_ID:MSVC>:/wd4018>"
)

# リンクライブラリ (dl, m)
# ${CMAKE_DL_LIBS} はWindowsでは空、Linuxでは 'dl'
target_link_libraries(fst PRIVATE ${CMAKE_DL_LIBS})
if(UNIX)
    target_link_libraries(fst PRIVATE m)
endif()

# Target: lib_export_dynamic
# (fst ターゲット自体とは別に、これにリンクするバイナリ用の設定)
add_library(lib_export_dynamic INTERFACE)
set_property(TARGET lib_export_dynamic PROPERTY INTERFACE_ENABLE_EXPORTS ON)
target_link_libraries(lib_export_dynamic INTERFACE fst)


# ------------------------------------------------------------------
# [追加] インストール設定
# ------------------------------------------------------------------

include(GNUInstallDirs)

# 'fst' ターゲットのインストール設定
# [変更なし] 'EXPORT fst-targets' で 'fst' をエクスポートセットに関連付けます
install(TARGETS fst
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# [変更] ヘッダファイルのインストールを 'install(DIRECTORY ...)' で手動実行
# 'src/lib/../include/' (つまり 'src/include/') ディレクトリを丸ごとインストール
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.inc"
)
