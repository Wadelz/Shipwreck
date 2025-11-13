# Shipwreck - Wave Break

A 2D arcade-style rescue game built with C++ and SFML. Navigate treacherous waters in your rowboat to save your crew members who fell overboard during a storm!

![Game Status](https://img.shields.io/badge/status-active-success)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![SFML](https://img.shields.io/badge/SFML-2.x-green)

## Game Description

Your pirate crew has gone overboard due to rough waters just offshore. Take control of a rowboat and navigate through dangerous waves to rescue all 6 survivors, then return safely to your mothership through the flag markers.

### Gameplay Features

- **Rescue Mission**: Save 6 crew members scattered across the waters
- **Dynamic Hazards**: Avoid powerful waves that sweep across the screen
- **Safe Zones**: Hide behind rocks to protect yourself from waves
- **Lives System**: Start with 3 lives - don't get caught by the waves!
- **Time Attack**: Complete the mission as fast as possible and beat your best time
- **Progressive Difficulty**: Ship speed reduces after rescuing 4 survivors
- **Easter Egg**: Unlock a special beach ball bonus after winning

## Screenshots

```
┌────────────────────────────────────────────────┐
│  Survivors saved: 4    Lives: 3   Time: 45    │
├────────────────────────────────────────────────┤
│                                                │
│     🎌                                 🌊     │
│                                                │
│     👤  ⛰️      👤                           │
│                                                │
│            ⛰️           🚣      ⛰️            │
│                                                │
│     👤                     👤                 │
│                                                │
└────────────────────────────────────────────────┘
```

## Table of Contents

- [Installation](#installation)
- [Building from Source](#building-from-source)
- [How to Play](#how-to-play)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Development](#development)
- [Technical Details](#technical-details)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Windows (Pre-built)

1. Download the latest release from the Releases page
2. Extract the ZIP file
3. Run `Shipwreck.exe`
4. Ensure all DLL files are in the same directory as the executable

### Linux / macOS

Currently, you need to build from source. See [Building from Source](#building-from-source).

## Building from Source

For detailed build instructions, see [BUILDING.md](docs/BUILDING.md).

### Quick Start

#### Using CMake (Recommended - Cross-platform)

```bash
# Clone the repository
git clone https://github.com/yourusername/Shipwreck.git
cd Shipwreck

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .

# Run the game
./bin/Shipwreck  # Linux/macOS
.\bin\Shipwreck.exe  # Windows
```

#### Using Visual Studio (Windows)

```bash
# Open Shipwreck.sln in Visual Studio
# Select your configuration (Debug/Release, Win32/x64)
# Press F5 to build and run
```

### Prerequisites

- **C++ Compiler**: C++17 or later
  - Windows: Visual Studio 2019+ or MinGW
  - Linux: GCC 7+ or Clang 5+
  - macOS: Xcode 10+
- **SFML 2.x**: Included in the repository
- **CMake 3.16+**: For CMake builds (optional)

## How to Play

### Objective

1. Navigate your rowboat around the playing field
2. Collect all 6 survivors (indicated by head icons)
3. Avoid the moving wave hazard
4. Hide behind rocks when the wave approaches
5. Return to the mothership by reaching the flag markers
6. Try to beat your best time!

### Game Mechanics

- **Wave Hazard**: A powerful wave continuously sweeps down the screen
- **Safe Zones**: Standing behind rocks protects you from the wave
- **Collision**: Hitting rocks will bounce you back slightly
- **Lives**: You have 3 chances - getting hit by waves costs a life
- **Speed Penalty**: Your boat slows down after rescuing 4 survivors
- **Win Condition**: Collect all 6 survivors AND reach the flag area

### Scoring

- Track your completion time
- Best time is saved across game sessions
- Challenge yourself to improve your personal record!

## Controls

| Key | Action |
|-----|--------|
| **Arrow Keys** | Move the rowboat |
| ↑ | Move up |
| ↓ | Move down |
| ← | Move left |
| → | Move right |
| **Space** | Continue (after winning) |
| **Escape** | Quit game |

## Project Structure

```
Shipwreck/
├── CMakeLists.txt              # CMake build configuration
├── Shipwreck.sln               # Visual Studio solution
├── README.md                   # This file
├── LICENSE                     # License information
│
├── Shipwreck/                  # Main project directory
│   ├── src/                    # Source code
│   │   ├── main.cpp           # Entry point
│   │   ├── core/              # Core game systems
│   │   │   ├── Game.h/cpp     # Main game class
│   │   │   └── Constants.h    # Game constants
│   │   ├── entities/          # Game entities
│   │   │   ├── Ship.h/cpp     # Player boat
│   │   │   ├── Wave.h/cpp     # Wave hazard
│   │   │   ├── Rock.h/cpp     # Obstacles
│   │   │   ├── Survivor.h/cpp # Collectibles
│   │   │   ├── Flag.h/cpp     # Finish line
│   │   │   └── Ball.h/cpp     # Easter egg
│   │   └── utils/             # Utility classes
│   │
│   ├── assets/                # Game assets
│   │   ├── textures/          # PNG sprites
│   │   └── fonts/             # TTF/OTF fonts
│   │
│   ├── lib/                   # Runtime libraries
│   │   └── win64/             # Windows DLLs
│   │
│   ├── external/              # Third-party dependencies
│   │   └── SFML/              # SFML library
│   │
│   └── Shipwreck.vcxproj      # Visual Studio project
│
├── docs/                      # Documentation
│   ├── BUILDING.md           # Build instructions
│   └── CONTRIBUTING.md       # Contribution guidelines
│
└── scripts/                   # Build/deployment scripts
    ├── setup.bat             # Windows setup
    └── package.sh            # Package for distribution
```

## Development

### Code Architecture

The game uses an object-oriented architecture with clean separation of concerns:

- **Game Class**: Central game loop and state management
- **Entity Classes**: Individual game objects (Ship, Wave, Rock, etc.)
- **Constants**: Centralized game configuration
- **Main**: Minimal entry point that delegates to Game class

### Key Classes

- `Game`: Main game loop, entity management, collision detection
- `Ship`: Player-controlled boat with movement and collision
- `Wave`: Moving hazard with animation
- `Rock`: Static obstacles that provide safe zones
- `Survivor`: Collectible items
- `Flag`: Win condition trigger

### Adding New Features

1. Add constants to `src/core/Constants.h`
2. Create entity classes in `src/entities/`
3. Update `Game` class to manage new entities
4. Add assets to appropriate `assets/` subdirectories

See [CONTRIBUTING.md](docs/CONTRIBUTING.md) for detailed guidelines.

## Technical Details

### Technologies

- **Language**: C++17
- **Graphics Library**: SFML 2.x
- **Build Systems**: CMake 3.16+, MSBuild (Visual Studio)
- **Platform**: Windows (primary), Linux, macOS (with SFML installed)

### Performance

- Target Frame Rate: 144 FPS
- Window Resolution: 1024x768 pixels
- Sprite-based rendering with texture management
- Efficient collision detection using SFML's FloatRect

### Dependencies

- **SFML 2.x**: Graphics, window, system, audio modules
- **OpenAL**: Audio backend (Windows)
- **FreeType**: Font rendering

All dependencies are included in the repository for Windows builds.

## Known Issues

- Audio system is included but not currently utilized
- No sound effects or music (future enhancement)
- Windows-specific DLLs require bundling for distribution
- No gamepad support (keyboard only)

## Future Enhancements

- [ ] Add sound effects and background music
- [ ] Implement power-ups and bonus items
- [ ] Multiple difficulty levels
- [ ] Level progression system
- [ ] High score leaderboard
- [ ] Gamepad/controller support
- [ ] Configuration file for custom settings
- [ ] More survivor types with different behaviors
- [ ] Additional obstacles and hazards

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](docs/CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

### Quick Contribution Guide

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Credits

### Development

- Original game concept and implementation

### Assets

- Font: RetroTeam by [Font Source]
- Font: DS-DIGIT by [Font Source]
- Sprites: Custom game artwork

### Libraries

- [SFML](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library

## Acknowledgments

- SFML community for excellent documentation
- Inspiration from classic arcade rescue games
- All contributors and testers

## Contact

- Project Repository: [https://github.com/yourusername/Shipwreck](https://github.com/yourusername/Shipwreck)
- Issue Tracker: [https://github.com/yourusername/Shipwreck/issues](https://github.com/yourusername/Shipwreck/issues)

---

Made with ❤️ and C++. Happy sailing! ⛵
