# NBody Thermal Exchange System

A C++ simulation of thermal exchange between multiple bodies, including radiation, conduction, and temperature-based visualisation.

This started as me wanting to see if I could actually build a thermal simulation from scratch. It ended up becoming a much bigger project than I originally expected.

## What does it do?

The simulation models multiple objects which can exchange thermal energy through:

* Blackbody radiation
* Radiative thermal exchange between objects
* Conduction when objects are touching
* Cooling to deep space
* Energy conservation during radiative exchange
* Radiation blocking / occultation

Objects also change colour based on their temperature, allowing the thermal state of the simulation to be seen directly.

The simulation can be interacted with in real time. Objects can be dragged around, spawned, and have their physical properties changed while the simulation is running.

## Physics

### Blackbody Radiation

Objects radiate energy according to the Stefan-Boltzmann law:

```text
P = εσAT⁴
```

This is used both for radiation into deep space and for calculating thermal exchange between objects.

### Thermal Exchange

Two objects at different temperatures exchange radiation. The net exchange depends on their temperatures, surface areas, emissivities, and geometry.

The simulation also accounts for objects blocking radiation between other objects.

### Conduction

When objects come into contact, thermal conduction is applied between them.

### Energy Conservation

One of the main goals of the project was to make sure that thermal energy wasn't simply appearing or disappearing during radiative exchange.

I created tests to compare the energy and temperature state before and after systems reach equilibrium.

Under the conditions tested, the equilibrium temperature differed by approximately **7.5 ppm (0.000075%)**.

This is a numerical simulation, so conservation is measured within a tolerance rather than assumed to be exact.

## Visualisation

The simulation uses SDL3 for rendering and interaction.

SDL3 is part of the visualisation and UI side of the project rather than the physics itself. The simulation logic can therefore be tested independently of the graphical interface.

Temperature is represented visually using colour, making it possible to see heat moving through the system without having to inspect numerical values constantly.

## Project Structure

The project is roughly split into:

* `src/` - implementation
* `include/` - headers
* `tests/` - physics and validation tests
* `third_party/` - external dependencies

The simulation and rendering code are kept separate where possible.

This project was also where I was learning how to structure a larger C++ program, so the architecture isn't perfect. There are definitely things I would structure differently if I started again.

## Testing

The physics has been tested against several expected behaviours, including:

* Stefan-Boltzmann cooling
* Thermal equilibrium
* Energy conservation during radiative exchange
* Temperature changes caused by thermal interaction
* Radiation blocking

The tests are intended to validate the physics rather than just checking whether the program runs.

## Current State

### IN DEVELOPMENT FEATURES

**None as of now.**

The core feature set I originally wanted to build is complete.

This doesn't mean the simulation is "finished" forever. There are plenty of things I'd still like to experiment with, but the original project is now at the point where I'm happy to call it complete.

## Future Ideas

### Barnes-Hut

The current implementation can become expensive as the number of bodies increases because interactions have to be calculated between bodies.

A Barnes-Hut implementation could reduce the number of calculations required and allow significantly larger simulations.

This is currently a future optimisation rather than part of the core project.

Other possible future work includes improving numerical accuracy, performance profiling, and further separating/refactoring parts of the architecture.

## Why I Made This

This project started mostly because I wanted to know whether I could make a simulation like this myself.

The actual development took roughly a month, but the idea had been sitting around for much longer. There was a lot of thinking, stopping, coming back to it, changing how I thought the physics should work, and then finally actually building the thing.

The project ended up teaching me quite a lot about:

* C++
* numerical simulation
* thermal physics
* energy conservation
* testing physical systems
* performance considerations
* and, perhaps most importantly, how to structure a project once it gets too big to comfortably keep everything in your head.

It works.

That's the important bit.
