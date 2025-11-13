@echo off
REM Shipwreck Development Setup Script for Windows
REM This script helps set up the development environment

setlocal enabledelayedexpansion

echo ========================================
echo Shipwreck Development Setup
echo ========================================
echo.

echo Checking prerequisites...
echo.

REM Check for Git
where git >nul 2>&1
if errorlevel 1 (
    echo [ERROR] Git is not installed or not in PATH
    echo Please install Git from: https://git-scm.com/download/win
    echo.
    pause
    exit /b 1
) else (
    echo [OK] Git found
)

REM Check for CMake
where cmake >nul 2>&1
if errorlevel 1 (
    echo [WARNING] CMake not found in PATH
    echo CMake is required for building. Install from:
    echo - Visual Studio Installer (C++ CMake tools)
    echo - Or standalone: https://cmake.org/download/
    echo.
) else (
    for /f "tokens=3" %%i in ('cmake --version ^| findstr /C:"cmake version"') do set CMAKE_VER=%%i
    echo [OK] CMake found (version !CMAKE_VER!)
)

REM Check for Visual Studio
set VS_FOUND=0
if exist "C:\Program Files\Microsoft Visual Studio\2022" (
    echo [OK] Visual Studio 2022 found
    set VS_FOUND=1
) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019" (
    echo [OK] Visual Studio 2019 found
    set VS_FOUND=1
) else (
    echo [WARNING] Visual Studio not found in default location
    echo Visual Studio 2019+ is recommended for development
)

echo.
echo ----------------------------------------
echo Setup Options:
echo ----------------------------------------
echo 1. Quick Build (CMake + Build)
echo 2. Open in Visual Studio
echo 3. Clean Build Directory
echo 4. Run Tests (if available)
echo 5. Exit
echo.

set /p CHOICE="Enter your choice (1-5): "

if "%CHOICE%"=="1" goto :quick_build
if "%CHOICE%"=="2" goto :open_vs
if "%CHOICE%"=="3" goto :clean_build
if "%CHOICE%"=="4" goto :run_tests
if "%CHOICE%"=="5" goto :end

echo Invalid choice!
pause
exit /b 1

:quick_build
echo.
echo ========================================
echo Quick Build
echo ========================================
echo.

if exist "build" (
    echo Build directory exists. Use option 3 to clean first if needed.
    echo Continuing with existing build directory...
)

echo Creating build directory...
if not exist "build" mkdir build
cd build

echo.
echo Configuring with CMake...
cmake .. -G "Visual Studio 17 2022" -A x64
if errorlevel 1 (
    echo.
    echo [ERROR] CMake configuration failed!
    echo Make sure you have Visual Studio 2022 installed.
    echo Or modify the generator in this script for your VS version.
    cd ..
    pause
    exit /b 1
)

echo.
echo Building (Debug configuration)...
cmake --build . --config Debug
if errorlevel 1 (
    echo [ERROR] Build failed! Check the output above for errors.
    cd ..
    pause
    exit /b 1
)

cd ..

echo.
echo ========================================
echo Build successful!
echo ========================================
echo.
echo Executable location: build\bin\Debug\Shipwreck.exe
echo.
echo Run the game:
echo   cd build\bin\Debug
echo   Shipwreck.exe
echo.
pause
goto :end

:open_vs
echo.
echo Opening in Visual Studio...
if exist "Shipwreck\Shipwreck.sln" (
    start "" "Shipwreck\Shipwreck.sln"
    echo Visual Studio solution opened.
) else (
    echo [ERROR] Solution file not found: Shipwreck\Shipwreck.sln
)
echo.
pause
goto :end

:clean_build
echo.
echo Cleaning build directory...
if exist "build" (
    rmdir /s /q "build"
    echo Build directory removed.
) else (
    echo Build directory does not exist.
)
if exist "dist" (
    echo.
    set /p CLEAN_DIST="Also clean dist directory? (y/n): "
    if /i "!CLEAN_DIST!"=="y" (
        rmdir /s /q "dist"
        echo Dist directory removed.
    )
)
echo.
echo Clean complete!
pause
goto :end

:run_tests
echo.
echo ========================================
echo Running Tests
echo ========================================
echo.
if not exist "build" (
    echo [ERROR] Build directory not found. Build the project first.
    pause
    goto :end
)

cd build
if exist "bin\Debug\Tests.exe" (
    echo Running tests...
    bin\Debug\Tests.exe
) else if exist "bin\Release\Tests.exe" (
    echo Running tests...
    bin\Release\Tests.exe
) else (
    echo [INFO] No test executable found.
    echo Tests are not yet implemented for this project.
)
cd ..
echo.
pause
goto :end

:end
echo.
echo Setup script finished.
