cmake_minimum_required(VERSION 3.30.1)
project(cppLearning)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/ProgramData/vcpkg/installed/x64-mingw-static/share/sfml")

# Optionally ensure static linking of the MinGW runtime libraries
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# Define SFML_STATIC for static linking
add_definitions(-DSFML_STATIC)

# Use the vcpkg toolchain if needed:
# -DCMAKE_TOOLCHAIN_FILE=C:/ProgramData/vcpkg/scripts/buildsystems/vcpkg.cmake

find_package(SFML CONFIG REQUIRED COMPONENTS graphics window system)

add_executable(cppLearning main.cpp)

target_link_libraries(cppLearning PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        opengl32
        freetype
        winmm
        gdi32
        comdlg32
        shell32
        ws2_32
)
