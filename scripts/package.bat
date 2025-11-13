@echo off
REM Shipwreck Release Packaging Script for Windows
REM This script builds the project in Release mode and packages it for distribution

setlocal enabledelayedexpansion

echo ========================================
echo Shipwreck Release Packaging Script
echo ========================================
echo.

REM Get version from git tag or use default
for /f "tokens=*" %%i in ('git describe --tags --abbrev=0 2^>nul') do set VERSION=%%i
if "%VERSION%"=="" set VERSION=v1.0.0
set VERSION=%VERSION:~1%
echo Version: %VERSION%

REM Configuration
set BUILD_DIR=build
set DIST_DIR=dist
set PACKAGE_NAME=Shipwreck-v%VERSION%-Windows-x64
set PACKAGE_DIR=%DIST_DIR%\%PACKAGE_NAME%

echo.
echo Step 1: Cleaning previous builds...
if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
if exist "%DIST_DIR%" rmdir /s /q "%DIST_DIR%"

echo Step 2: Creating build directory...
mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

echo.
echo Step 3: Configuring CMake (Release mode)...
cmake .. -G "Visual Studio 17 2022" -A x64
if errorlevel 1 (
    echo ERROR: CMake configuration failed!
    cd ..
    exit /b 1
)

echo.
echo Step 4: Building project (Release)...
cmake --build . --config Release
if errorlevel 1 (
    echo ERROR: Build failed!
    cd ..
    exit /b 1
)

cd ..

echo.
echo Step 5: Creating distribution package...
mkdir "%DIST_DIR%"
mkdir "%PACKAGE_DIR%"

echo Copying executable...
copy "%BUILD_DIR%\bin\Release\Shipwreck.exe" "%PACKAGE_DIR%\" >nul
if errorlevel 1 (
    echo ERROR: Failed to copy executable!
    exit /b 1
)

echo Copying runtime DLLs...
xcopy /y /q "Shipwreck\lib\win64\*.dll" "%PACKAGE_DIR%\" >nul
if errorlevel 1 (
    echo ERROR: Failed to copy DLLs!
    exit /b 1
)

echo Copying assets...
xcopy /y /q /e /i "Shipwreck\assets" "%PACKAGE_DIR%\assets\" >nul
if errorlevel 1 (
    echo ERROR: Failed to copy assets!
    exit /b 1
)

echo Copying documentation...
copy "README.md" "%PACKAGE_DIR%\" >nul
copy "LICENSE" "%PACKAGE_DIR%\" >nul

echo Creating README-RELEASE.txt...
(
    echo Shipwreck - Wave Break v%VERSION%
    echo =====================================
    echo.
    echo Thank you for downloading Shipwreck!
    echo.
    echo QUICK START:
    echo 1. Extract all files to a folder
    echo 2. Run Shipwreck.exe
    echo 3. Follow the on-screen instructions
    echo.
    echo CONTROLS:
    echo - Arrow Keys: Move the rowboat
    echo - Space: Continue ^(after winning^)
    echo - Escape: Quit game
    echo.
    echo REQUIREMENTS:
    echo - Windows 10 or later
    echo - All DLL files must be in the same directory as Shipwreck.exe
    echo.
    echo For more information, see README.md
    echo.
    echo SUPPORT:
    echo - Report issues: https://github.com/Wadelz/Shipwreck/issues
    echo - Documentation: https://github.com/Wadelz/Shipwreck
    echo.
    echo License: MIT
) > "%PACKAGE_DIR%\README-RELEASE.txt"

echo.
echo Step 6: Creating ZIP archive...
powershell -command "Compress-Archive -Path '%PACKAGE_DIR%' -DestinationPath '%DIST_DIR%\%PACKAGE_NAME%.zip' -Force"
if errorlevel 1 (
    echo ERROR: Failed to create ZIP archive!
    exit /b 1
)

echo.
echo ========================================
echo SUCCESS! Package created:
echo %DIST_DIR%\%PACKAGE_NAME%.zip
echo ========================================
echo.
echo Package contents:
dir "%PACKAGE_DIR%"
echo.
echo Package size:
for %%A in ("%DIST_DIR%\%PACKAGE_NAME%.zip") do echo %%~zA bytes

echo.
echo The package is ready for distribution!
echo Location: %CD%\%DIST_DIR%\%PACKAGE_NAME%.zip
echo.
pause
