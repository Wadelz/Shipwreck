cmake_minimum_required(VERSION 3.16)
project(Shipwreck VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Option to use bundled SFML or system SFML
option(USE_BUNDLED_SFML "Use bundled SFML library" ON)

# Find SFML
if(USE_BUNDLED_SFML)
    # Use bundled SFML
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/Shipwreck/external/SFML/lib/cmake/SFML")
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
else()
    # Use system SFML
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
endif()

# Collect source files
file(GLOB_RECURSE SOURCES
    "Shipwreck/src/*.cpp"
)

# Collect header files
file(GLOB_RECURSE HEADERS
    "Shipwreck/src/*.h"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Shipwreck/src
    ${CMAKE_SOURCE_DIR}/Shipwreck/src/core
    ${CMAKE_SOURCE_DIR}/Shipwreck/src/entities
    ${CMAKE_SOURCE_DIR}/Shipwreck/src/utils
)

if(USE_BUNDLED_SFML)
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/Shipwreck/external/SFML/include
    )
endif()

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    if(MSVC)
        # Disable console window for release builds
        set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE $<CONFIG:Release>
        )

        # Copy DLLs to output directory for Windows
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Shipwreck/lib/win64
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()

    # MinGW settings
    if(MINGW)
        target_link_libraries(${PROJECT_NAME} PRIVATE
            -static-libgcc
            -static-libstdc++
        )
    endif()
elseif(UNIX AND NOT APPLE)
    # Linux-specific settings
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
elseif(APPLE)
    # macOS-specific settings
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
    )
endif()

# Copy assets to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Shipwreck/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copying assets to build directory"
)

# Installation rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/Shipwreck/assets
    DESTINATION bin
)

if(WIN32)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/Shipwreck/lib/win64/
        DESTINATION bin
    )
endif()

# Print configuration summary
message(STATUS "")
message(STATUS "Shipwreck Configuration Summary")
message(STATUS "================================")
message(STATUS "Version:           ${PROJECT_VERSION}")
message(STATUS "Build type:        ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard:      ${CMAKE_CXX_STANDARD}")
message(STATUS "Use bundled SFML:  ${USE_BUNDLED_SFML}")
message(STATUS "Install prefix:    ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
