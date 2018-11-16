# pics-trigger
Create a "Triggered" effect out of an image.

# Prerequisites
[CMake](https://cmake.org/) version 3.1 or higher and a C++ compiler. Also [SFML](https://www.sfml-dev.org/index.php) version 2.5 and Make for GNU/Linux.

# Compilation
## Common
Change directory to the root of the project. Then, type `mkdir build`, `cd build` and `cmake ..`.
## GNU/Linux
Call `cmake --build .` from the build/ folder and, if the compilation succeed, a binary named pics-trigger will appear at the root of the build/ folder.
## Windows
Call `cmake --build . --target ALL_BUILD --config Release` from the build/ forlder. A binary named pics-trigger will appear in the build/Release/ folder along its required .dll. These .dll must stay in the same folder of pics-trigger in order for it to work.

# Usage
pics-trigger [OPTIONS] [image-file]

Where OPTIONS is:
```
-h,--help		Display usage information
-v,--version		Display program version, author and licensing
-f,--frames		Number of frames in the output sheet, must be greater than zero
-p,--no-playback	Stop the program once the sprite sheet is completed
```
