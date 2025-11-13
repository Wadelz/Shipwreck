# Contributing to Shipwreck

Thank you for your interest in contributing to Shipwreck! This document provides guidelines and instructions for contributing to the project.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Process](#development-process)
- [Coding Standards](#coding-standards)
- [Submitting Changes](#submitting-changes)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Features](#suggesting-features)

## Code of Conduct

### Our Pledge

We are committed to providing a welcoming and inclusive experience for everyone. We expect all contributors to:

- Be respectful and constructive
- Accept feedback gracefully
- Focus on what's best for the project
- Show empathy towards other contributors

### Unacceptable Behavior

- Harassment, trolling, or discriminatory language
- Personal attacks or insults
- Spam or off-topic discussions
- Publishing others' private information

## Getting Started

### 1. Fork and Clone

```bash
# Fork the repository on GitHub, then clone your fork
git clone https://github.com/YOUR-USERNAME/Shipwreck.git
cd Shipwreck

# Add upstream remote
git remote add upstream https://github.com/Wadelz/Shipwreck.git
```

### 2. Set Up Development Environment

Follow the instructions in [BUILDING.md](BUILDING.md) to set up your development environment.

### 3. Create a Branch

```bash
# Update your main branch
git checkout main
git pull upstream main

# Create a feature branch
git checkout -b feature/your-feature-name
```

Use descriptive branch names:
- `feature/add-sound-effects`
- `bugfix/fix-collision-detection`
- `docs/improve-readme`
- `refactor/simplify-game-loop`

## Development Process

### Understanding the Codebase

```
Shipwreck/src/
├── main.cpp              # Entry point - minimal, delegates to Game class
├── core/                 # Core game systems
│   ├── Game.h/cpp       # Main game loop, state management
│   └── Constants.h      # Centralized game configuration
├── entities/            # Game entity classes
│   ├── Ship.h/cpp       # Player-controlled boat
│   ├── Wave.h/cpp       # Moving hazard
│   ├── Rock.h/cpp       # Static obstacles with safe zones
│   ├── Survivor.h/cpp   # Collectible survivors
│   ├── Flag.h/cpp       # Win condition trigger
│   └── Ball.h/cpp       # Easter egg beach ball
└── utils/               # Utility classes (future)
```

### Key Architecture Principles

1. **Separation of Concerns**: Each class has a single, well-defined responsibility
2. **Game Class**: Central coordinator for game loop, entity management, collision detection
3. **Entity Classes**: Self-contained game objects with their own update/render logic
4. **Constants**: All magic numbers and strings centralized in `Constants.h`
5. **SFML Integration**: Use SFML for graphics, window management, input handling

### Making Changes

#### 1. Adding New Constants

Add to `src/core/Constants.h`:

```cpp
namespace GameConstants {
    const int NEW_CONSTANT = 42;

    namespace Assets {
        const char* NEW_TEXTURE = "assets/textures/new_texture.png";
    }
}
```

#### 2. Creating New Entities

Create header and source files in `src/entities/`:

```cpp
// NewEntity.h
#pragma once
#include <SFML/Graphics.hpp>

class NewEntity {
private:
    sf::Vector2f position;
    sf::RectangleShape shape;

public:
    NewEntity(float x, float y);
    void update();
    sf::FloatRect getPosition() const;
    sf::RectangleShape getShape() const;
};
```

Register in `Game` class:
- Add as member variable
- Create in `createEntities()`
- Update in `update()`
- Render in `render()`

#### 3. Modifying Game Logic

Most game logic belongs in `Game` class:
- Input handling → `handleInput()`
- Collision detection → `checkCollisions()`
- Win/lose conditions → `checkWinCondition()`
- HUD updates → `updateHUD()`

### Testing Your Changes

```bash
# Build in Debug mode for testing
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .

# Run the game
./bin/Shipwreck

# Test thoroughly:
# - Normal gameplay
# - Edge cases (boundaries, timing)
# - Win condition
# - Lose condition
# - Replay functionality
```

## Coding Standards

### C++ Style Guide

We follow a consistent style for readability:

#### Naming Conventions

```cpp
// Classes: PascalCase
class GameEntity { };

// Functions/Methods: camelCase
void movePlayer() { }

// Variables: camelCase
int playerScore = 0;

// Constants: UPPER_SNAKE_CASE
const int MAX_LIVES = 3;

// Private members: camelCase (no prefix)
private:
    float velocity;
```

#### Code Formatting

```cpp
// Braces: Opening brace on same line
if (condition) {
    doSomething();
}

// Spaces around operators
int result = a + b;

// Indentation: 4 spaces (no tabs)
void function() {
    if (condition) {
        doSomething();
    }
}
```

#### Comments

```cpp
// Single-line comments for brief explanations
// Use proper grammar and punctuation

/**
 * @brief Multi-line doc comments for functions
 *
 * Describe what the function does, parameters, and return value
 *
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @return True if successful
 */
bool initialize(float x, float y);
```

### Best Practices

#### 1. Use Constants

**Bad:**
```cpp
window.setSize(1024, 768);
```

**Good:**
```cpp
window.setSize(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT);
```

#### 2. Error Handling

```cpp
if (!texture.loadFromFile(path)) {
    std::cerr << "Error: Could not load texture: " << path << "\n";
    return false;
}
```

#### 3. Resource Management

Use RAII and smart pointers:
```cpp
std::unique_ptr<Entity> entity = std::make_unique<Entity>();
```

#### 4. Const Correctness

```cpp
sf::FloatRect getPosition() const;  // Methods that don't modify state
const char* getAssetPath() const;   // Return const for read-only data
```

### File Organization

#### Header Files (.h)

```cpp
#pragma once  // Use instead of include guards

#include <SFML/Graphics.hpp>
#include <memory>

// Forward declarations when possible
class OtherClass;

class MyClass {
private:
    // Private members first
    int privateMember;

public:
    // Public interface
    MyClass();
    void publicMethod();
};
```

#### Source Files (.cpp)

```cpp
#include "MyClass.h"

// System includes
#include <iostream>
#include <cmath>

// Project includes
#include "OtherClass.h"

// Implementation
MyClass::MyClass() {
    // Constructor
}
```

## Submitting Changes

### 1. Commit Your Changes

Write clear, descriptive commit messages:

```bash
git add .
git commit -m "Add sound effects to wave collision

- Load wave crash sound effect
- Play sound when ship hits wave
- Add volume control constant
- Update Constants.h with audio paths"
```

#### Commit Message Guidelines

- First line: Brief summary (50 chars or less)
- Blank line
- Detailed description if needed
- Reference issues: `Fixes #123` or `Related to #456`

### 2. Push to Your Fork

```bash
git push origin feature/your-feature-name
```

### 3. Create Pull Request

1. Go to your fork on GitHub
2. Click "Pull Request"
3. Select your feature branch
4. Fill out the PR template:

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
How you tested your changes

## Screenshots
If applicable

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-reviewed code
- [ ] Commented complex code
- [ ] Updated documentation
- [ ] No new warnings
- [ ] Added tests if applicable
```

### 4. Code Review

- Respond to feedback constructively
- Make requested changes
- Push updates to your branch (PR updates automatically)

### 5. Merge

Once approved, maintainers will merge your PR!

## Reporting Bugs

### Before Submitting

1. **Search existing issues** - your bug might already be reported
2. **Use latest version** - ensure you're using the latest code
3. **Test on clean build** - rebuild from scratch to rule out build issues

### Bug Report Template

```markdown
## Bug Description
Clear description of the bug

## To Reproduce
Steps to reproduce:
1. Launch game
2. Press arrow key
3. Collision occurs
4. See error

## Expected Behavior
What should happen

## Actual Behavior
What actually happens

## Environment
- OS: Windows 10 / Ubuntu 22.04 / macOS 13
- Compiler: Visual Studio 2022 / GCC 11.3 / Clang 14
- Build Type: Debug / Release
- SFML Version: 2.5.1

## Screenshots
If applicable

## Additional Context
Any other relevant information
```

## Suggesting Features

### Feature Request Template

```markdown
## Feature Description
Clear description of the proposed feature

## Problem it Solves
What problem does this address?

## Proposed Solution
How would you implement this?

## Alternatives Considered
Other approaches you've thought about

## Additional Context
Mockups, examples, references
```

### Guidelines for Features

- **Fits project scope**: Aligns with game's arcade style
- **User benefit**: Clear value to players
- **Feasible**: Can be implemented with current tech stack
- **Maintainable**: Doesn't overcomplicate the codebase

## Development Tips

### Debugging

```bash
# Build with debug symbols
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Use debugger
gdb ./bin/Shipwreck
# Or Visual Studio debugger (F5)
```

### Common Tasks

#### Adding New Texture

1. Add PNG to `Shipwreck/assets/textures/`
2. Add path constant to `Constants.h`
3. Load in entity constructor:
```cpp
texture.loadFromFile(GameConstants::Assets::NEW_TEXTURE);
```

#### Adding New Entity Type

1. Create `NewEntity.h` and `NewEntity.cpp` in `src/entities/`
2. Add to `Game.h` as member variable
3. Create in `Game::createEntities()`
4. Update in `Game::update()`
5. Render in `Game::render()`

#### Modifying Game Constants

1. Update `src/core/Constants.h`
2. Rebuild project
3. Test affected gameplay

### Resources

- [SFML Documentation](https://www.sfml-dev.org/documentation/)
- [C++ Reference](https://en.cppreference.com/)
- [Game Programming Patterns](https://gameprogrammingpatterns.com/)

## Questions?

- Open a [Discussion](https://github.com/Wadelz/Shipwreck/discussions)
- Check existing [Issues](https://github.com/Wadelz/Shipwreck/issues)
- Read the [README](../README.md) and [BUILDING.md](BUILDING.md)

---

Thank you for contributing to Shipwreck! 🎮⛵
