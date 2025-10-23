# CMakeの最小バージョンを指定
cmake_minimum_required(VERSION 3.16)

# プロジェクト名を "openfst" に設定
project(openfst LANGUAGES CXX)

# C++17を標準として設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OPENFST_VERSION 23.0.0)
set(OPENFST_SOVERSION 23)

# ------------------------------------------------------------------
# オプション
# ------------------------------------------------------------------

# Bazelの 'config_setting' と 'select' に対応
option(OPENFST_HAS_ABSL "Enable Abseil support" OFF)

# OFF (デフォルト) の場合、CMakeは 'add_library' で静的ライブラリをビルドします
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# [追加] 実行可能バイナリ (bin/) をビルドするかどうかを制御
option(OPENFST_BUILD_BIN "Build executable binaries" ON)

# ------------------------------------------------------------------
# 外部依存関係 (find_package)
# ------------------------------------------------------------------

if(OPENFST_HAS_ABSL)
    # 必要なコンポーネントを探します
    find_package(absl REQUIRED COMPONENTS synchronization)
    message(STATUS "Found Abseil (via find_package)")
else()
    message(STATUS "Abseil support disabled (OPENFST_HAS_ABSL=OFF)")
endif()

# ------------------------------------------------------------------
# ソースディレクトリの追加
# ------------------------------------------------------------------

# 'src' ディレクトリをビルドに追加
add_subdirectory(src)
