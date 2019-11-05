SET CMAKE_PATH=C:\Program Files\CMake\bin

SET LLVM=C:/Program Files/LLVM/bin
SET NINJA=%USERPROFILE%\Downloads\ninja.exe

REM SET PATH=%PATH%;%CMAKE_PATH%

IF NOT EXIST "%NINJA%" (
    echo Download Ninja to %NINJA%
    GOTO :eof
)

MD build-dir
CD build-dir

REM generate build files
"%CMAKE_PATH%\cmake" -G "Ninja" -DCMAKE_MAKE_PROGRAM="%NINJA%" -DCMAKE_C_COMPILER="%LLVM%/clang.exe" -DCMAKE_CXX_COMPILER="%LLVM%/clang++.exe" -DCMAKE_RC_COMPILER="%LLVM%/llvm-rc.exe" ..

REM compile our project
"%CMAKE_PATH%\cmake" --build .

REM run the tests
"%CMAKE_PATH%\cmake" --build . --target test

CD ..
