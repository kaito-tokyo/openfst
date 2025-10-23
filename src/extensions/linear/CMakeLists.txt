include(GNUInstallDirs)

# 'src/include/fst/extensions/linear' 以下の全ヘッダを glob して取得 (IDE連携用)
file(GLOB_RECURSE LINEAR_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/linear/*.h)
file(GLOB_RECURSE LINEAR_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../include/fst/extensions/linear/*.inc)
set(LINEAR_HEADERS ${LINEAR_HEADERS_H} ${LINEAR_HEADERS_INC})

# ------------------------------------------------------------------
# ライブラリ (linear-fst: linear_tagger-fst.la と linear_classifier-fst.la を統合)
# ------------------------------------------------------------------
add_library(linear-fst
    linear-classifier-fst.cc
    linear-tagger-fst.cc
)

set_target_properties(linear-fst PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
target_sources(linear-fst PRIVATE ${LINEAR_HEADERS})

# 依存関係 (Makefile.am の LIBS)
target_link_libraries(linear-fst PUBLIC fst)

# インストール設定
install(TARGETS linear-fst
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# ライブラリ (libfstlinearscript.la)
# ------------------------------------------------------------------
add_library(linearscript
    linearscript.cc
)

set_target_properties(linearscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
target_sources(linearscript PRIVATE ${LINEAR_HEADERS})

# 依存関係 (libfstlinearscript_la_LIBADD と元のファイル)
target_link_libraries(linearscript PUBLIC
    fstscript
    linear-fst
)

# インストール設定
install(TARGETS linearscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# 実行可能バイナリ (OPENFST_BUILD_BIN が ON の場合のみ)
# ------------------------------------------------------------------

if(OPENFST_BUILD_BIN)

    set(LINEAR_BINARIES
        fstlinear
        fstloglinearapply
    )
    
    foreach(target_name IN LISTS LINEAR_BINARIES)
        add_executable(${target_name}
            ${target_name}.cc
            ${target_name}-main.cc
        )
        
        # 依存関係 (Makefile.am の LDADD)
        target_link_libraries(${target_name} PRIVATE
            linearscript
            lib_export_dynamic
        )
    endforeach()
    
    # バイナリをインストール
    install(TARGETS ${LINEAR_BINARIES}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
