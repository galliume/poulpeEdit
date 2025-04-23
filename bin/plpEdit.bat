@echo off
pushd %1

tclsh90 %cd%\src\main.tcl

popd

Pause