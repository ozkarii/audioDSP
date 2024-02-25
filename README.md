## Audio player DSP thing
Simple cli application for playing sound, applying filters etc.\
Uses Simple DirectMedia Layer for audio backend.

## Requirements
CMake 3.14 or newer required. Tested on Ubuntu 22.04.\
Install dependencies:
```
sudo apt install cmake
sudo apt install libsdl2-dev
``` 

## Usage
Build using CMake:
```
mkdir build
cd build
cmake ..
make
```
Run:
```
./app help
```

### TODO:
- fir filter
- butterworth filter
- tests (unit, speed/size)
- polished cli
- more comments
- sample rate altering
- optimization
- circular buffer for fft
- more multithreading
- make params and variables const
- windows version (different audio api)

### What I learned
- How to read API reference and implement code based on it
- Using bash efficiently
- C++ developement on Linux (WSL)
- Audio programming
- How makefiles work
- Compiler and linker things
- Working with git branches
