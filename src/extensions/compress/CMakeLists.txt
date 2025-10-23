# GNUInstallDirs は親スコープでインクルード済みですが、
# CMAKE_INSTALL_LIBDIR 等の変数を参照するためにここでもインクルードします
include(GNUInstallDirs)

# Target: compressscript (libfstcompressscript.la に対応)
add_library(compressscript
    compressscript.cc
)

# バージョン情報を設定 (Makefile.am の -version-info 23:0:0 に対応)
set_target_properties(compressscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
# (インストールは src/lib/CMakeLists.txt の glob で処理済み)
target_sources(compressscript PRIVATE
    ../../include/fst/extensions/compress/compressscript.h
)

# 依存関係 (Makefile.am の libfstcompressscript_la_LIBADD に対応)
# fstscript が fst, m, dl を継承
target_link_libraries(compressscript PUBLIC fstscript)

# ライブラリをインストールし、'fst-targets' エクスポートセットに追加
install(TARGETS compressscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# 実行可能バイナリ (OPENFST_BUILD_BIN が ON の場合のみ)
# ------------------------------------------------------------------

# Makefile.am の 'if HAVE_BIN' に対応
if(OPENFST_BUILD_BIN)

    # Target: fstcompress
    add_executable(fstcompress
        fstcompress.cc
        fstcompress-main.cc
    )
    
    # 依存関係 (Makefile.am の LDADD に対応)
    # compressscript が fstscript, fst, m, dl を継承
    target_link_libraries(fstcompress PRIVATE
        compressscript
        lib_export_dynamic
    )

    # バイナリをインストール
    install(TARGETS fstcompress
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
