include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ヘッダファイルを管理する INTERFACE ターゲットを定義します。
#
# この 'fst_headers' ターゲットにリンクするだけで、
# 'src/include' ディレクトリが自動的にインクルードパスに追加されます。
# これにより、各サブプロジェクトでの include_directories() の呼び出しが不要になります。
add_library(fst_headers INTERFACE)
target_include_directories(fst_headers INTERFACE
    # $<BUILD_INTERFACE:...> : ビルドツリー内で 'fst_headers' にリンクした時のパス
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    
    # $<INSTALL_INTERFACE:...> : インストール先で 'fst_headers' にリンクした時のパス
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
install(TARGETS fst_headers EXPORT fst-targets)

# 各コンポーネントのディレクトリをビルドに追加
add_subdirectory(lib)
add_subdirectory(script)
if(OPENFST_BUILD_BIN)
  add_subdirectory(bin)
endif()
add_subdirectory(extensions)

# (ユーザーの指示に基づき、'add_subdirectory(test)' は削除されました)
# [追加] 'src/lib/' から移動した install(EXPORT ...) コマンド
# すべての add_subdirectory が完了した後、
# 'fst-targets' セットに蓄積された全ターゲット（fst, fst_headers）を
# パッケージファイルに書き出します。
install(EXPORT fst-targets
    FILE fst-targets.cmake
    NAMESPACE OpenFst::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/openfst
)

# [追加] 'OpenFstConfig.cmake.in' をテンプレートとして 'OpenFstConfig.cmake' を生成
configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/OpenFstConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/OpenFstConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/openfst
    # OpenFstConfig.cmake.in の @PACKAGE_INIT@ が使う変数を渡す
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

# [追加] 生成された 'OpenFstConfig.cmake' をインストール
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/OpenFstConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/openfst
)
