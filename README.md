# vrooom
A motion controller for the VIAM Rover V1 written in C++. 

This program is intended to run on a Raspberry Pi.


### Demo

![](assets/rover.mp4)

### Dependencies
- `lcm` for interprocess-communication (locally or between machines)
- `lgpio` for controlling the Pi pins.

### Build instructions

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

### Running the modules

To run modules:

```
cd build
```

To launch the Rover module, run

```
./Rover/rover [--sim or --rover]
```

Use `--sim` if you want ro just emulate the hardware, `--rover` if you are on the Pi and using the GPIO (and therefore you have enabled the compilation with USE_LGPIO).


To launch the JoypadControl module, run

```
./JoypadControl/joypad-control-rover [--sim or --rover]
```