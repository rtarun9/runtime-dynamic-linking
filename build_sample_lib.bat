@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

mkdir build
pushd build

mkdir sample_lib
pushd sample_lib

cl /LD ../../sample_lib/lib.c 
popd
popd

