@echo off
REM Shipwreck Release Packaging Script for Windows
REM This script builds the project in Release mode and packages it for distribution

setlocal enabledelayedexpansion

echo ========================================
echo Shipwreck Release Packaging Script
echo ========================================
echo.

REM Navigate to project root
cd ..

REM Get version from git tag or use default
for /f "tokens=*" %%i in ('git describe --tags --abbrev=0 2^>nul') do set VERSION=%%i
if "%VERSION%"=="" set VERSION=v1.0.0
set VERSION=%VERSION:~1%
echo Version: %VERSION%

REM Configuration
set DIST_DIR=dist
set PACKAGE_NAME=Shipwreck-v%VERSION%-Windows-x64
set PACKAGE_DIR=%DIST_DIR%\%PACKAGE_NAME%
set BUILD_CONFIG=Release
set BUILD_PLATFORM=x64

echo.
echo Step 1: Cleaning previous builds...
if exist "%DIST_DIR%" rmdir /s /q "%DIST_DIR%"
if exist "Shipwreck\x64\%BUILD_CONFIG%" rmdir /s /q "Shipwreck\x64\%BUILD_CONFIG%"

echo Step 2: Locating MSBuild...
REM Try to find MSBuild
set MSBUILD=""

REM Check for VS 2022
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
    echo Found Visual Studio 2022 Community
) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe"
    echo Found Visual Studio 2022 Professional
) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
    echo Found Visual Studio 2022 Enterprise
)

REM Check for VS 2019
if %MSBUILD%=="" (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" (
        set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
        echo Found Visual Studio 2019 Community
    ) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe" (
        set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe"
        echo Found Visual Studio 2019 Professional
    ) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\MSBuild.exe" (
        set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
        echo Found Visual Studio 2019 Enterprise
    )
)

if %MSBUILD%=="" (
    echo ERROR: MSBuild not found!
    echo Please install Visual Studio 2019 or 2022 with C++ development tools.
    echo.
    pause
    exit /b 1
)

echo.
echo Step 3: Building project (Release x64)...
%MSBUILD% "Shipwreck\Shipwreck.vcxproj" /p:Configuration=%BUILD_CONFIG% /p:Platform=%BUILD_PLATFORM% /t:Rebuild /v:minimal /nologo
if errorlevel 1 (
    echo.
    echo ERROR: Build failed! Check the output above for errors.
    echo.
    echo Common issues:
    echo - SFML not installed or not found
    echo - Missing Visual Studio C++ components
    echo.
    pause
    exit /b 1
)

echo.
echo Step 4: Creating distribution package...
mkdir "%DIST_DIR%"
mkdir "%PACKAGE_DIR%"

echo Copying executable...
copy "Shipwreck\x64\%BUILD_CONFIG%\Shipwreck.exe" "%PACKAGE_DIR%\" >nul
if errorlevel 1 (
    echo ERROR: Failed to copy executable!
    echo Make sure the build succeeded and check: Shipwreck\x64\%BUILD_CONFIG%\Shipwreck.exe
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
echo Step 5: Creating ZIP archive...
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
