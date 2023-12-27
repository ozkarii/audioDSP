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
