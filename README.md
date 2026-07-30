# NBody-Thermal-Exchange-System

A program written in C++ using SDL3 that shows the laws of thermodynamics, showing exchange between objects via conduction and radiation .

## OVERVIEW

This project simulates how objects in deep space radiate their heat to space and other objects via conduction when touching and radiation when apart.
This project includes blackbody radiation colour mapping to simulate how an object would look at specific temperatures.

## CURRENT FEATURES

* Blackbody radiation colour mapping
* Temperature loss to deep space using Stefan-Boltzmann's law
* Draggable objects

## IN DEVELOPMENT FEATURES

* Temperature Equilibrium between objects when touching

## FUTURE FEATURES

* Changeable mass and physics states of objects
* Spawnable objects
* Barnes-Hutt Algorithm
* Basic UI system
* etc.

## FUTURE PROJECT GOALS

* Add test folder of internal code and mathematical / physics logic

## REQUIREMENTS

* SDL3
* Visual Studio 2022+
* C++ 17 or newer

## BUILD

Create a new C++ project in Visual Studio 2022 (or newer).
Download or clone the SDL3 Development Kit.
Configure the project's Additional Include Directories, Library Directories, and Linker Dependencies using the paths provided by the SDL3 Development Kit.
Ensure the project references the required include directories using relative paths where possible.
Copy SDL3.dll into the executable output directory (or build first, then place the DLL beside the executable).
Build and run the project.
>**Note:** The SDL3 Development Kit is designed to be reused across multiple SDL3 projects. The project configuration should only require updating the SDL3 paths to match the user's local installation.

>**Contingency:** If the project's own header files are not able to be found, either add them to the project's local 'src' file, or link your relative path under both projects Additional Include Directories configuration settings.

## KNOWN LIMITATIONS

* Need to internally change and add objects in C++
* Current Stefan-Boltzmann logic has not been verified yet
* Objects do not obey conservation of energy when touching
