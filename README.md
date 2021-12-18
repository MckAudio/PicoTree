# PicoTree

## Description

Very small program that drives the twocolor LEDs of my "christmas tree".
The program runs on the Raspberry PI Pico 2040.

## Build

Development and building works best on Raspberry PI 4/400 with the Pico connected via SWD:

```
mkdir build
cd build
export PICO_SDK_PATH=../../pico-sdk
cmake ..
cd ..
make
```