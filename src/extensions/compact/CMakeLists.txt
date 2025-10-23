# Extension: Compact
#
set(COMPACT_TYPES
    compact16_acceptor
    compact16_string
    compact16_unweighted
    compact16_unweighted_acceptor
    compact16_weighted_string
    compact64_acceptor
    compact64_string
    compact64_unweighted
    compact64_unweighted_acceptor
    compact64_weighted_string
    compact8_acceptor
    compact8_string
    compact8_unweighted
    compact8_unweighted_acceptor
    compact8_weighted_string
)

# GNUInstallDirs は親スコープ (src/CMakeLists.txt) でインクルード済みですが、
# CMAKE_INSTALL_LIBDIR 等の変数を参照するためにここでもインクルードします
include(GNUInstallDirs)

# ループですべての Compact ライブラリを定義
# 
foreach(type IN LISTS COMPACT_TYPES)
    # ターゲットを定義 (例: compact16_acceptor-fst)
    add_library(${type}-fst
        ${type}-fst.cc
    )

    # バージョン情報を設定 (ルートの CMakeLists.txt で定義された変数を使用)
    set_target_properties(${type}-fst PROPERTIES
        VERSION "${OPENFST_VERSION}"
        SOVERSION "${OPENFST_SOVERSION}"
    )

    # メインの 'fst' ライブラリにリンク
    target_link_libraries(${type}-fst PUBLIC fst)

    # ライブラリをインストールし、'fst-targets' エクスポートセットに追加
    install(TARGETS ${type}-fst
        EXPORT fst-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endforeach()
