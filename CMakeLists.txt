cmake_minimum_required(VERSION 3.13)
project(openfst)
include(CTest)


set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_definitions(/bigobj)
  add_definitions(-DNOMINMAX)
  #set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
  #this must be disabled unless the previous option (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS) is enabled
  option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
else()
  option(BUILD_SHARED_LIBS "Build shared libraries" ON)
endif(WIN32)

set(SOVERSION "23")
OPTION(BUILD_USE_SOLUTION_FOLDERS "Enable grouping of projects in VS" ON)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ${BUILD_USE_SOLUTION_FOLDERS})


# Optional features (see README for details)
option(HAVE_BIN              "Enable fst::script and executables" ON)           # --enable-bin
option(HAVE_COMPACT          "Enable CompactFst extensions" OFF)                # --enable-compact-fsts
option(HAVE_COMPRESS         "Enable compression extension" OFF)                # --enable-compress
option(HAVE_CONST            "Enable ConstFst extensions" OFF)                  # --enable-const-fsts
option(HAVE_FAR              "Enable FAR extensions" OFF)                       # --enable-far
option(HAVE_FSTS             "Enable all FST SO extensions" OFF)                # --enable-fsts
option(HAVE_GRM              "Enable all dependencies of OpenGrm" OFF)          # --enable-grm
option(HAVE_LINEAR           "Enable LinearTagger/ClassifierFst extensions" OFF)# --enable-linear-fsts
option(HAVE_LOOKAHEAD        "Enable LookAheadFst extensions" OFF)              # --enable-lookahead-fsts
option(HAVE_MPDT             "Enable MPDT extensions" OFF)                      # --enable-mpdt
option(HAVE_NGRAM            "Enable NGramFst extensions" OFF)                  # --enable-ngram-fsts
option(HAVE_PDT              "Enable PDT extensions" OFF)                       # --enable-pdt
option(HAVE_PYTHON           "Enable Python extension" OFF)                     # --enable-python
option(HAVE_SPECIAL          "Enable special-matcher extensions" OFF)           # --enable-special
option(HAVE_SCRIPT           "Build the fstscript" ON)

add_subdirectory(src)
