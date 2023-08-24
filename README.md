# Tetris_SDL

A Tetris clone made using the [SDL](https://www.libsdl.org/) development library.

**Screenshot here**

### Dependencies

Tetris_SDL requires the following libraries:
- `SDL2` - latest releases [here](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.2).
- `SDL2_ttf` - latest releases [here](https://github.com/libsdl-org/SDL_ttf/releases).

Versions of the required SDL2 libraries for Visual Studio are contained in the `dependencies` directory.

## Build in Visual Studio 

Clone the repository, open the solution file and build the `Tetris_SDL` project.

Build files are placed in the `bin` folder located in this directory.

## Future additions & improvements

Here are some of my ideas of how to add to the project.

### Game
- Add sound using the SDL mixer library
- Graphical enhancements
- Save multiple highscores with player name

### Project
- Add support for non-Visual Studio builds
- Change console logging to a log file
- Create top-level game engine class and clean up MainMenu & Tetris classes