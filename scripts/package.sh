#!/bin/bash
# Shipwreck Release Packaging Script for Linux/macOS
# This script builds the project in Release mode and packages it for distribution

set -e  # Exit on error

echo "========================================"
echo "Shipwreck Release Packaging Script"
echo "========================================"
echo

# Detect platform
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="Linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
else
    PLATFORM="Unix"
fi

# Get version from git tag or use default
VERSION=$(git describe --tags --abbrev=0 2>/dev/null || echo "v1.0.0")
VERSION=${VERSION#v}  # Remove 'v' prefix
echo "Platform: $PLATFORM"
echo "Version: $VERSION"

# Configuration
BUILD_DIR="build"
DIST_DIR="dist"
PACKAGE_NAME="Shipwreck-v${VERSION}-${PLATFORM}-x64"
PACKAGE_DIR="${DIST_DIR}/${PACKAGE_NAME}"

echo
echo "Step 1: Cleaning previous builds..."
rm -rf "$BUILD_DIR"
rm -rf "$DIST_DIR"

echo "Step 2: Creating build directory..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo
echo "Step 3: Configuring CMake (Release mode)..."
cmake .. -DCMAKE_BUILD_TYPE=Release

echo
echo "Step 4: Building project (Release)..."
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS: Use number of processors
    CORES=$(sysctl -n hw.ncpu)
else
    # Linux: Use number of processors
    CORES=$(nproc)
fi
cmake --build . -j${CORES}

cd ..

echo
echo "Step 5: Creating distribution package..."
mkdir -p "$PACKAGE_DIR"

echo "Copying executable..."
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS: Copy .app bundle if it exists, otherwise copy executable
    if [ -d "$BUILD_DIR/bin/Shipwreck.app" ]; then
        cp -r "$BUILD_DIR/bin/Shipwreck.app" "$PACKAGE_DIR/"
    else
        cp "$BUILD_DIR/bin/Shipwreck" "$PACKAGE_DIR/"
    fi
else
    # Linux: Copy executable
    cp "$BUILD_DIR/bin/Shipwreck" "$PACKAGE_DIR/"
fi

echo "Copying assets..."
cp -r "Shipwreck/assets" "$PACKAGE_DIR/"

echo "Copying documentation..."
cp "README.md" "$PACKAGE_DIR/"
cp "LICENSE" "$PACKAGE_DIR/"

echo "Creating README-RELEASE.txt..."
cat > "$PACKAGE_DIR/README-RELEASE.txt" << EOF
Shipwreck - Wave Break v${VERSION}
=====================================

Thank you for downloading Shipwreck!

QUICK START:
1. Extract all files to a folder
2. Run ./Shipwreck (or open Shipwreck.app on macOS)
3. Follow the on-screen instructions

CONTROLS:
- Arrow Keys: Move the rowboat
- Space: Continue (after winning)
- Escape: Quit game

REQUIREMENTS:
- $PLATFORM
- SFML 2.x (included or installed via package manager)

For more information, see README.md

SUPPORT:
- Report issues: https://github.com/Wadelz/Shipwreck/issues
- Documentation: https://github.com/Wadelz/Shipwreck

License: MIT
EOF

# Create install script for Linux
if [[ "$PLATFORM" == "Linux" ]]; then
    echo "Creating install script..."
    cat > "$PACKAGE_DIR/install.sh" << 'EOF'
#!/bin/bash
# Shipwreck Installation Script

echo "Installing Shipwreck..."

INSTALL_DIR="${HOME}/.local/share/shipwreck"
BIN_DIR="${HOME}/.local/bin"

# Create directories
mkdir -p "$INSTALL_DIR"
mkdir -p "$BIN_DIR"

# Copy files
echo "Copying game files..."
cp -r assets "$INSTALL_DIR/"
cp Shipwreck "$INSTALL_DIR/"
chmod +x "$INSTALL_DIR/Shipwreck"

# Create launcher script
echo "Creating launcher..."
cat > "$BIN_DIR/shipwreck" << LAUNCHER
#!/bin/bash
cd "$INSTALL_DIR"
./Shipwreck
LAUNCHER

chmod +x "$BIN_DIR/shipwreck"

echo
echo "Installation complete!"
echo "Run 'shipwreck' from terminal or add $BIN_DIR to your PATH"
EOF
    chmod +x "$PACKAGE_DIR/install.sh"
fi

echo
echo "Step 6: Creating archive..."
cd "$DIST_DIR"
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS: Create ZIP (more common on macOS)
    zip -r "${PACKAGE_NAME}.zip" "$PACKAGE_NAME" > /dev/null
    ARCHIVE="${PACKAGE_NAME}.zip"
else
    # Linux: Create tar.gz
    tar -czf "${PACKAGE_NAME}.tar.gz" "$PACKAGE_NAME"
    ARCHIVE="${PACKAGE_NAME}.tar.gz"
fi
cd ..

echo
echo "========================================"
echo "SUCCESS! Package created:"
echo "${DIST_DIR}/${ARCHIVE}"
echo "========================================"
echo
echo "Package contents:"
ls -lh "$PACKAGE_DIR"
echo
echo "Archive size:"
ls -lh "${DIST_DIR}/${ARCHIVE}"

echo
echo "The package is ready for distribution!"
echo "Location: $(pwd)/${DIST_DIR}/${ARCHIVE}"
echo

# Create SHA256 checksum
echo "Creating checksum..."
cd "$DIST_DIR"
if command -v sha256sum &> /dev/null; then
    sha256sum "$ARCHIVE" > "${ARCHIVE}.sha256"
    echo "SHA256: $(cat ${ARCHIVE}.sha256)"
elif command -v shasum &> /dev/null; then
    shasum -a 256 "$ARCHIVE" > "${ARCHIVE}.sha256"
    echo "SHA256: $(cat ${ARCHIVE}.sha256)"
fi
cd ..

echo
echo "Done!"
