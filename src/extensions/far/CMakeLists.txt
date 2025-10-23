include(GNUInstallDirs)

# 'src/include/fst/extensions/far' 以下の全ヘッダを glob して取得 (IDE連携用)
file(GLOB_RECURSE FAR_HEADERS_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../include/fst/extensions/far/*.h)
file(GLOB_RECURSE FAR_HEADERS_INC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../include/fst/extensions/far/*.inc)
set(FAR_HEADERS ${FAR_HEADERS_H} ${FAR_HEADERS_INC})

# ------------------------------------------------------------------
# ライブラリ (libfstfar.la)
# ------------------------------------------------------------------
add_library(fstfar
    sttable.cc
    stlist.cc
)

set_target_properties(fstfar PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
target_sources(fstfar PRIVATE ${FAR_HEADERS})

# 依存関係 (libfstfar_la_LIBADD)
target_link_libraries(fstfar PUBLIC fst)

# インストール設定
install(TARGETS fstfar
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# ライブラリ (libfstfarscript.la)
# ------------------------------------------------------------------
add_library(fstfarscript
    far-class.cc
    farscript.cc
    getters.cc
    script-impl.cc
    strings.cc
    # (sttable.cc と stlist.cc は fstfar ターゲットからリンクするため除外)
)

set_target_properties(fstfarscript PROPERTIES
    VERSION "${OPENFST_VERSION}"
    SOVERSION "${OPENFST_SOVERSION}"
)

# ヘッダをIDE連携のために PRIVATE で追加
target_sources(fstfarscript PRIVATE ${FAR_HEADERS})

# 依存関係 (libfstfarscript_la_LIBADD)
target_link_libraries(fstfarscript PUBLIC fstfar fstscript)

# インストール設定
install(TARGETS fstfarscript
    EXPORT fst-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ------------------------------------------------------------------
# 実行可能バイナリ (OPENFST_BUILD_BIN が ON の場合のみ)
# ------------------------------------------------------------------

if(OPENFST_BUILD_BIN)

    set(FAR_BINARIES
        farcompilestrings
        farconvert
        farcreate
        farequal
        farextract
        farinfo
        farisomorphic
        farprintstrings
    )
    
    foreach(target_name IN LISTS FAR_BINARIES)
        add_executable(${target_name}
            ${target_name}.cc
            ${target_name}-main.cc
        )
        
        # 依存関係 (Makefile.am の LDADD)
        # (fstfarscript が fstfar, fstscript, fst, m, dl を継承)
        target_link_libraries(${target_name} PRIVATE
            fstfarscript
            lib_export_dynamic
        )
    endforeach()
    
    # バイナリをインストール
    install(TARGETS ${FAR_BINARIES}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
