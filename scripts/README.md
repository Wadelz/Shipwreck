# Build and Packaging Scripts

This directory contains scripts for building and packaging Shipwreck for distribution.

## Available Scripts

### `package.bat` - Windows Release Packaging

Creates a distributable Windows release package with executable, DLLs, assets, and documentation.

**Requirements:**
- Windows
- Visual Studio 2019+ with CMake support
- Git (for version detection)

**Usage:**
```batch
cd scripts
package.bat
```

**Output:**
- Creates `dist/Shipwreck-v{version}-Windows-x64/` directory
- Creates `dist/Shipwreck-v{version}-Windows-x64.zip` archive
- Package includes:
  - `Shipwreck.exe` (Release build)
  - All required DLLs (SFML, OpenAL)
  - `assets/` directory with textures and fonts
  - `README.md` and `LICENSE`
  - `README-RELEASE.txt` with quick start guide

**What it does:**
1. Detects version from git tags (or uses v1.0.0)
2. Cleans previous builds
3. Configures project with CMake (Visual Studio generator)
4. Builds in Release mode
5. Copies executable, DLLs, assets, and docs to distribution folder
6. Creates README-RELEASE.txt with quick start instructions
7. Creates ZIP archive for distribution

### `package.sh` - Linux/macOS Release Packaging

Creates a distributable Linux or macOS release package.

**Requirements:**
- Linux or macOS
- CMake 3.16+
- C++ compiler (GCC/Clang)
- SFML 2.x development libraries
- Git (for version detection)

**Usage:**
```bash
cd scripts
./package.sh
```

**Output:**
- Creates `dist/Shipwreck-v{version}-{Platform}-x64/` directory
- Creates archive:
  - Linux: `Shipwreck-v{version}-Linux-x64.tar.gz`
  - macOS: `Shipwreck-v{version}-macOS-x64.zip`
- Package includes:
  - `Shipwreck` executable (or `Shipwreck.app` on macOS)
  - `assets/` directory
  - `README.md` and `LICENSE`
  - `README-RELEASE.txt` with quick start guide
  - `install.sh` (Linux only) - optional installation script
- SHA256 checksum file

**What it does:**
1. Detects platform and version
2. Cleans previous builds
3. Configures project with CMake
4. Builds in Release mode (using all CPU cores)
5. Copies executable, assets, and docs to distribution folder
6. Creates platform-specific package structure
7. Creates installation script (Linux)
8. Creates compressed archive
9. Generates SHA256 checksum

## Version Detection

Both scripts automatically detect the version from git tags:

```bash
# To create a version tag:
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0
```

If no git tag is found, the scripts default to `v1.0.0`.

## Manual Building

If you prefer to build manually without packaging:

### Windows (CMake + Visual Studio)
```batch
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

### Linux/macOS (CMake + Make)
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)  # Linux
cmake --build . -j$(sysctl -n hw.ncpu)  # macOS
```

## Distribution

After running the packaging script:

1. **Test the package** on a clean system without development tools
2. **Upload to GitHub Releases**:
   ```bash
   # Create a release on GitHub
   gh release create v1.0.0 dist/Shipwreck-*.zip --title "Shipwreck v1.0.0" --notes "Release notes here"
   ```
3. **Include checksums** in release notes (automatically generated for Linux/macOS)

## Troubleshooting

### Windows

**Issue:** CMake not found
- Ensure Visual Studio with CMake support is installed
- Or install standalone CMake from https://cmake.org/

**Issue:** Build fails
- Open Visual Studio and build manually first to diagnose issues
- Check that SFML paths are correct in CMakeLists.txt

### Linux/macOS

**Issue:** SFML not found
```bash
# Ubuntu/Debian
sudo apt-get install libsfml-dev

# Fedora
sudo dnf install SFML-devel

# macOS
brew install sfml
```

**Issue:** Permission denied
```bash
chmod +x package.sh
```

**Issue:** Build fails
- Ensure all dependencies are installed
- Try building manually first to diagnose issues

## Creating GitHub Releases

To create an official release:

1. **Tag the release:**
   ```bash
   git tag -a v1.0.0 -m "Release version 1.0.0"
   git push origin v1.0.0
   ```

2. **Run packaging scripts** on each platform:
   ```bash
   # Windows
   scripts\package.bat

   # Linux
   scripts/package.sh

   # macOS (on a Mac)
   scripts/package.sh
   ```

3. **Create GitHub release:**
   - Go to repository → Releases → Draft a new release
   - Select the version tag
   - Upload the ZIP/tar.gz files from `dist/`
   - Include SHA256 checksums in release notes
   - Add release notes with changelog

4. **Test downloads:**
   - Download and test on clean systems
   - Verify all files are included and game runs

## Notes

- The scripts create self-contained packages with all dependencies
- Windows packages include all required DLLs
- Linux/macOS users may need to install SFML via package manager
- Always test packages on systems without development tools installed
- Consider creating packages for multiple platforms for each release

## Future Improvements

Potential enhancements to packaging scripts:

- [ ] AppImage creation for Linux (portable)
- [ ] DMG creation for macOS (installer)
- [ ] Windows installer (NSIS or WiX)
- [ ] Automated CI/CD pipeline (GitHub Actions)
- [ ] Code signing for Windows/macOS
- [ ] Auto-update functionality
- [ ] Multi-language support in packages

## Support

For issues with packaging scripts:
- Report bugs: https://github.com/Wadelz/Shipwreck/issues
- Documentation: https://github.com/Wadelz/Shipwreck/docs
