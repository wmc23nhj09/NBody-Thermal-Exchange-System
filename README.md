# NBody-Thermal-Exchange-System

A program written in C++ using SDL3 that shows the laws of thermodynamics, showing exchange between objects via conduction and radiation .

## OVERVIEW

This project simulates how objects in deep space radiate their heat to space and other objects via conduction when touching and radiation when apart.
This project includes blackbody radiation colour mapping to simulate how an object would look at specific temperatures.

## CURRENT FEATURES

* Blackbody radiation colour mapping
* Temperature loss to deep space using Stefan-Boltzmann's law
* Temperature Equilibrium between objects at a distance due to radiation
* Obey Conservation of energy at a distance *
* Draggable objects

## IN DEVELOPMENT FEATURES

* Temperature Equilibrium between objects when touching

## FUTURE FEATURES

* Changeable mass and physics states of objects
* Spawnable objects
* Barnes-Hutt Algorithm
* Basic UI system
* etc.

## TEST VALIDATIONS
### ADDED
* Stefan-Boltzmann Single Step Deep Space Cooling
  >**NOTE:** As temperature increases, the margin of error increases due to the non-linear `(T^4)` relationship in Stefan-Boltzmann radiation. This test allows up to 1% error for single-step calculations. A future multi-step simulation stability test will verify accuracy using smaller timesteps and improve high-temperature accuracy.

### TO ADD
* Multi-step simulation stability
* Blackbody radiation -> RGB colour mapping validation
* etc.

## REQUIREMENTS

* SDL3
* Visual Studio 2022+
* C++ 17 or newer

## BUILD

1. Create a new C++ project in Visual Studio 2022 (or newer).
2. Download or clone the [SDL3 Development Kit](https://github.com/wmc23nhj09/SDL3_Development_Kit).
3. Configure the project's Additional Include Directories, Library Directories, and Linker Dependencies using the paths provided by the SDL3 Development Kit.
4. Copy SDL3.dll into the executable output directory (or build first, then place the DLL beside the executable).
5. Build and run the project.
   
>**Note:** The SDL3 Development Kit is designed to be reused across multiple SDL3 projects. The project configuration should only require updating the SDL3 paths to match the user's local installation. This repository assumes basic knowledge of Visual Studio C++ project configuration. Users should configure their project include paths and linker settings to point to this development kit.

>**Contingency:** All of this project's own header files are already configured for the ease of building, only the [SDL3 Development Kit](https://github.com/wmc23nhj09/SDL3_Development_Kit)'s files need to be configured (Step 3). If the project's own header files are not able to be found, either add them to the project's local `src` file, or link your relative path under both projects Additional Include Directories configuration settings.

## KNOWN LIMITATIONS

* Need to internally change and add objects in C++
* Objects do not obey conservation of energy when touching
* Temperatures end up overflowing as objects starting temps rise, limit unknown yet
