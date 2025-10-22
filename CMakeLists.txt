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

set(SOVERSION "16")
OPTION(BUILD_USE_SOLUTION_FOLDERS "Enable grouping of projects in VS" ON)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ${BUILD_USE_SOLUTION_FOLDERS})

option(HAVE_BIN          "Build the fst binaries" ON)
option(HAVE_SCRIPT       "Build the fstscript" ON)
option(HAVE_COMPACT      "Build compact" ON)
option(HAVE_COMPRESS "Build compress" OFF)
option(HAVE_CONST   "Build const" ON)
option(HAVE_FAR  "Build far" ON)
option(HAVE_GRM "Build grm" ON)
option(HAVE_PDT "Build pdt" ON)
option(HAVE_MPDT "Build mpdt" ON)

add_subdirectory(src)
