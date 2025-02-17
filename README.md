# vrooom
A motion controller for the VIAM Rover V1 written in C++. 

This program is intended to run on a Raspberry Pi.

### Dependencies
- `lcm` for interprocess-communication (locally or between machines)
- `lgpio` for controlling the Pi pins.

### build instructions

To compile:

```
mkdir build
cd build
```

CMake Options:
 - USE_LGPIO: Compiles the components that use `lgpio` for interfacing with the Pi pins.

```
cmake <add your desired options here> ..
make [or make install if you want install the modules in a known path]
```

To run:

```
cd build
./rover
```
