# Building Shipwreck

This guide provides detailed instructions for building Shipwreck from source on various platforms.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Building on Windows](#building-on-windows)
  - [Using Visual Studio](#using-visual-studio)
  - [Using CMake with Visual Studio](#using-cmake-with-visual-studio)
  - [Using MinGW](#using-mingw)
- [Building on Linux](#building-on-linux)
- [Building on macOS](#building-on-macos)
- [Build Configuration](#build-configuration)
- [Troubleshooting](#troubleshooting)

## Prerequisites

### All Platforms

- **Git**: For cloning the repository
- **C++17 compatible compiler**
- **CMake 3.16 or later** (optional but recommended)

### Platform-Specific

#### Windows
- Visual Studio 2019 or later (Community Edition is fine)
- OR MinGW-w64 (for GCC on Windows)
- SFML 2.x (included in repository)

#### Linux
- GCC 7+ or Clang 5+
- SFML 2.x development libraries
- X11 development libraries

```bash
# Ubuntu/Debian
sudo apt-get install build-essential cmake libsfml-dev libx11-dev

# Fedora
sudo dnf install gcc-c++ cmake SFML-devel libX11-devel

# Arch Linux
sudo pacman -S base-devel cmake sfml libx11
```

#### macOS
- Xcode Command Line Tools
- Homebrew (recommended)
- SFML 2.x

```bash
# Install Xcode Command Line Tools
xcode-select --install

# Install SFML via Homebrew
brew install sfml cmake
```

## Building on Windows

### Using Visual Studio

This is the recommended method for Windows development.

#### Step 1: Clone the Repository

```bash
git clone https://github.com/Wadelz/Shipwreck.git
cd Shipwreck
```

#### Step 2: Open in Visual Studio

1. Double-click `Shipwreck.sln` to open in Visual Studio
2. Select your desired configuration:
   - **Release** (recommended) or **Debug**
   - **x64** (recommended) or **Win32**

The project is pre-configured for **C++17**, so no additional setup is needed.

#### Step 3: Build

- Press **F7** or select **Build > Build Solution**
- The executable will be created in `Shipwreck/x64/Debug/` or `Shipwreck/x64/Release/`

#### Step 4: Run

- Press **F5** to run with debugging
- Or **Ctrl+F5** to run without debugging
- The necessary DLLs and assets are automatically copied to the output directory via post-build events

### Using CMake with Visual Studio

For a more modern, CMake-based build experience:

#### Step 1: Generate Visual Studio Project

```bash
# Clone repository
git clone https://github.com/Wadelz/Shipwreck.git
cd Shipwreck

# Create build directory
mkdir build
cd build

# Generate Visual Studio project (VS 2019)
cmake .. -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Release

# Or for Visual Studio 2022
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
```

CMake automatically:
- Sets C++17 standard
- Finds bundled SFML libraries
- Configures include paths
- Sets up post-build asset copying

#### Step 2: Build

```bash
# Build from command line (recommended)
cmake --build . --config Release

# Or open the generated solution in Visual Studio
start Shipwreck.sln
```

#### Step 3: Run

```bash
# Navigate to output directory
cd bin

# Run the game
Shipwreck.exe
```

### Using MinGW

If you prefer GCC on Windows:

```bash
# Clone repository
git clone https://github.com/Wadelz/Shipwreck.git
cd Shipwreck

# Create build directory
mkdir build
cd build

# Configure with MinGW Makefiles
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

# Build with all CPU cores
cmake --build . -j%NUMBER_OF_PROCESSORS%

# Run the game
cd bin
Shipwreck.exe
```

**Note**: The bundled SFML library works with MinGW/GCC compilers.

## Building on Linux

### Using System SFML (Recommended)

```bash
# Install SFML first (see Prerequisites section)
# Ubuntu/Debian: sudo apt-get install libsfml-dev

# Clone repository
git clone https://github.com/Wadelz/Shipwreck.git
cd Shipwreck

# Create build directory
mkdir build && cd build

# Configure (using system SFML)
cmake .. -DUSE_BUNDLED_SFML=OFF -DCMAKE_BUILD_TYPE=Release

# Build using all CPU cores
cmake --build . -j$(nproc)

# Run the game
./bin/Shipwreck
```

### Using Bundled SFML

If you don't have SFML installed system-wide:

```bash
# Configure (using bundled SFML)
cmake .. -DUSE_BUNDLED_SFML=ON -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build . -j$(nproc)

# Run
./bin/Shipwreck
```

### Installation (Optional)

```bash
# Install to /usr/local by default
sudo cmake --install .

# Or specify custom install prefix
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/.local
cmake --build .
cmake --install .

# Run installed version
~/.local/bin/Shipwreck
```

## Building on macOS

### Using Homebrew SFML (Recommended)

```bash
# Step 1: Install dependencies via Homebrew
brew install sfml cmake

# Step 2: Clone repository
git clone https://github.com/Wadelz/Shipwreck.git
cd Shipwreck

# Step 3: Create build directory
mkdir build && cd build

# Step 4: Configure CMake (using system SFML)
cmake .. -DUSE_BUNDLED_SFML=OFF -DCMAKE_BUILD_TYPE=Release

# Step 5: Build using all CPU cores
cmake --build . -j$(sysctl -n hw.ncpu)

# Step 6: Run the game
./bin/Shipwreck
```

### Creating an App Bundle (Optional)

CMake can create a macOS `.app` bundle for easier distribution:

```bash
# The CMake configuration automatically creates an app bundle
# Find it in the build/bin directory
open bin/Shipwreck.app

# Or double-click Shipwreck.app in Finder
```

## Build Configuration

### CMake Options

You can customize the build with these CMake options:

| Option | Default | Description |
|--------|---------|-------------|
| `USE_BUNDLED_SFML` | ON | Use SFML included in repository |
| `CMAKE_BUILD_TYPE` | Debug | Build type: Debug, Release, RelWithDebInfo |
| `CMAKE_INSTALL_PREFIX` | `/usr/local` | Installation directory |

#### Examples

```bash
# Release build with system SFML
cmake .. -DUSE_BUNDLED_SFML=OFF -DCMAKE_BUILD_TYPE=Release

# Debug build with bundled SFML
cmake .. -DUSE_BUNDLED_SFML=ON -DCMAKE_BUILD_TYPE=Debug

# Release with debug info
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo

# Custom install location
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/games
```

### Visual Studio Configurations

When using Visual Studio directly:

- **Debug**: Includes debugging symbols, no optimization
- **Release**: Optimized, no debugging symbols
- **Win32**: 32-bit build
- **x64**: 64-bit build (recommended)

## Build Artifacts

After building, you'll find:

### CMake Build

```
build/
├── bin/
│   ├── Shipwreck          # Executable
│   └── assets/            # Game assets (copied)
└── lib/                   # Libraries
```

### Visual Studio Build

```
Shipwreck/
├── x64/
│   ├── Debug/
│   │   ├── Shipwreck.exe
│   │   ├── *.dll          # Runtime DLLs
│   │   └── assets/        # Assets
│   └── Release/
│       ├── Shipwreck.exe
│       ├── *.dll
│       └── assets/
```

## Troubleshooting

### Common Issues

#### "SFML not found"

**Solution**:
- Install SFML system-wide, or
- Use `-DUSE_BUNDLED_SFML=ON` with CMake

#### "Cannot find assets"

**Issue**: The executable can't find textures/fonts

**Solution**:
- Ensure `assets/` directory is in the same folder as the executable
- CMake automatically copies assets during build
- For Visual Studio, use post-build events or copy manually

#### Windows DLL Errors

**Issue**: Missing `sfml-*.dll` or `openal32.dll`

**Solution**:
- Copy DLLs from `Shipwreck/lib/win64/` to executable directory
- CMake handles this automatically
- For Visual Studio, check post-build events

#### Linux: "cannot find -lsfml-*"

**Solution**:
```bash
# Install SFML development packages
sudo apt-get install libsfml-dev

# Or use bundled SFML
cmake .. -DUSE_BUNDLED_SFML=ON
```

#### macOS: "dylib not found"

**Solution**:
```bash
# Install SFML via Homebrew
brew install sfml

# Or add Homebrew to library path
export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH
```

### Build Errors

#### "C++17 required"

Your compiler is too old. Update to:
- GCC 7+
- Clang 5+
- Visual Studio 2019+

#### Linker Errors

Check that:
1. SFML libraries are correctly installed
2. All source files are included in the build
3. Library paths are correct

### Performance Issues

#### Low Frame Rate

- Build in **Release** mode for optimal performance
- Debug builds are significantly slower
- Check your graphics drivers are up to date

### Getting Help

If you encounter issues not covered here:

1. Check the [GitHub Issues](https://github.com/Wadelz/Shipwreck/issues)
2. Search for similar problems
3. Create a new issue with:
   - Your operating system and version
   - Compiler and version (`gcc --version`, `clang --version`, or Visual Studio version)
   - Full error message (copy the entire output)
   - Build command used
   - Whether you're using bundled or system SFML

## Development Builds

### Quick Rebuild

```bash
# After making code changes
cd build
cmake --build .

# Or use ninja for faster builds
cmake .. -GNinja
ninja
```

### Clean Build

```bash
# Remove build directory and rebuild
rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### IDE Integration

#### Visual Studio Code

1. Install **C/C++** and **CMake Tools** extensions
2. Open project folder
3. Select kit (compiler)
4. Press `F7` to build

#### CLion

1. Open `CMakeLists.txt` as project
2. CLion auto-configures
3. Press `Ctrl+F9` to build

## Creating Distribution Packages

Ready to distribute your build? Use the automated packaging scripts:

### Windows Package

```bash
cd scripts
package.bat
```

Creates:
- `dist/Shipwreck-v{version}-Windows-x64.zip`
- Includes executable, DLLs, assets, and documentation
- Ready for distribution

### Linux/macOS Package

```bash
cd scripts
./package.sh
```

Creates:
- Linux: `dist/Shipwreck-v{version}-Linux-x64.tar.gz`
- macOS: `dist/Shipwreck-v{version}-macOS-x64.zip`
- Includes SHA256 checksums

See [scripts/README.md](../scripts/README.md) for detailed packaging documentation.

## Next Steps

After building successfully:

- Read the [main README](../README.md) for gameplay instructions
- Check [CONTRIBUTING.md](CONTRIBUTING.md) for development guidelines
- Explore the source code in `Shipwreck/src/`
- Create distribution packages using scripts in `scripts/`

Happy building! 🔨
