@echo off

endlocal
setlocal

set CURREN_DIR=%cd%
echo %CURREN_DIR%

call "%VS140COMNTOOLS%..\..\VC\bin\x86_amd64\vcvarsx86_amd64.bat"

echo Prepare configuration
cmake -H. -Bwin-tmp -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release
if %ERRORLEVEL% GEQ 1 (
    echo "Problem cmake"
    EXIT /B 1
)

echo Build
cmake --build win-tmp --config Release
if %ERRORLEVEL% GEQ 1 (
    echo "Problem cmake build"
    EXIT /B 1
)