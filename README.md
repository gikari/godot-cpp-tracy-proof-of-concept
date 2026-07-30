# Godot GDExtension Tracy Profiling — Proof of Concept

This demo shows how to profile both **GDScript** and **C++ GDExtension** code together in a single [Tracy](https://github.com/wolfpld/tracy) capture on Windows (MinGW).

## What the demo does

`main.gd` runs a loop for ~3 seconds. Each frame it calls a chain of short sleeps both from GDScript and from the C++ `ProfilingExample` GDExtension node, so the resulting Tracy trace shows both GDSCript and C++ calls.

## Prerequisites

- Godot Editor and Export templates compiled from this branch https://github.com/gikari/godot/tree/feature/tracy_gdextension
- [CMake](https://cmake.org/) ≥ 3.21
- [Ninja](https://ninja-build.org/)
- [MinGW-w64 (GCC v14.2.0)](https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-12.0.0-ucrt-r3/winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r3.7z)
- [Tracy v12.2.0](https://github.com/wolfpld/tracy/releases) for viewing captures

## Quick start

### 1. Build the GDExtension (Tracy-enabled)

```bash
cmake --preset tracy
cmake --build --preset tracy
```

### 2. Export the game

Open the precompiled Godot editor from the `presets/godot.windows.editor.x86_64.exe`.
Then export via **Project → Export → Windows Desktop (Tracy)**

### 3. Run the game

Start the Tracy client **before** launching the game, then connect to `localhost`. The capture will show GDScript and C++ frames side by side.

```bash
./exports/profiling_example_tracy.exe
```

The process exits automatically after ~3 seconds.

Pre-recorded captures are available in `traces/` if you want to explore the result without building anything.


## Implementation Caveats

1. Tracy.dll must be deployed to the final directory. Godot does not currently deploy the dll dependencies. It must learn to do that.
2. When using MinGW, no static runtime (libstdc++ etc.) must be used, as the ones from tracy.dll and app.exe would clash. It must be put into .dlls too, that must be deployed together with the export template.
3. Tracy needs to be started by Godot (TRACY_DELAYED_INIT + TRACY_MANUAL_LIFETIME) to prevent leaving editor zombie process, when Tracy is launched automatically through GDExtension DLL
