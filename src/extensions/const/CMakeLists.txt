include(GNUInstallDirs)

# Target: fstconst (Makefile.am の libfstconst.la に対応)
add_library(fstconst
    const8-fst.cc
    const16-fst.cc
    const64-fst.cc
)

# バージョン情報を設定 (Makefile.am の -version-info 23:0:0 に対応)
set_target_properties(fstconst PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# 依存関係 (Makefile.am の LIBS に対応)
# 'fst' ターゲットが libfst.la, m, dl の依存関係を継承
target_link_libraries(fstconst PUBLIC fst)

# ライブラリをインストールし、'fst-targets' エクスポートセットに追加
install(TARGETS fstconst
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
