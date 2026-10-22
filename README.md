# SimulatePixels

A pixel-based falling-sand simulation where every pixel is a cell made of a
material (sand, water, salt, fire, wood, smoke, steam, blood, ...), each with
its own density, movement rules and interactions. Rendering and windowing use
the raw Win32 API (`CreateWindow`, `StretchDIBits`), and the simulation field
can optionally be split into sub-domains and advanced in parallel with OpenMP
(see `MT_sd_Controller` / `MT_subDomain`).

There is currently no checked-in `.sln`/`.vcxproj` or Makefile, so pick one of
the two options below depending on your platform.

## Option A: Build on Windows with Visual Studio (recommended)

This is the intended target platform — the app opens a real Win32 window and
draws directly into it.

1. Install **Visual Studio** (2019 or later) with the **Desktop development
   with C++** workload.
2. Create a new **Windows Desktop Application (C++)** project (or an empty
   C++ project) and add all `.cpp`/`.h` files from [TestScreenOutput/](TestScreenOutput)
   to it.
3. Project Properties → **C/C++ → Language**:
   - **C++ Language Standard**: ISO C++17 or later (the code uses `inline`
     member layout and modern initializer syntax that needs at least C++17).
   - **Open MP Support**: **Yes (/openmp)** — required for the
     `#pragma omp parallel for` loops in `MT_sd_Controller.cpp`.
4. Project Properties → **Linker → System**:
   - **SubSystem**: Windows (`/SUBSYSTEM:WINDOWS`), since the entry point is
     `WinMain`, not `main`.
5. Build the project (Ctrl+Shift+B) and run it (F5). A window should open and
   the simulation starts automatically, dropping sand/water/salt/blood/
   steam/smoke at fixed points on the field (see `Simulator::setCenterSand`).

If you'd rather add a proper `.sln`/`.vcxproj` to the repo so this is a
one-click build, let me know and I can generate one.

### Unit tests

[UnitTests/](UnitTests) uses MSTest's `CppUnitTestFramework` and requires the
**Test Development** workload component in Visual Studio. Note:
`TestDomain.cpp` currently targets an older `BaseDomain` API (a 2-argument
constructor, before the `Field`/`FieldController` split) and will need to be
updated before it builds against the current `TestScreenOutput` sources.

## Option B: Cross-compile on Linux (for quick checks, no window/rendering)

You can compile and link the whole project into a Windows `.exe` using
`mingw-w64`, which is useful for verifying the code builds without needing a
Windows machine. You won't be able to run the resulting `.exe` natively on
Linux (it needs a Win32 GUI), but Wine can run it if you have a display.

1. Install the cross-compiler and Windows headers/libs:
   ```bash
   sudo apt install g++-mingw-w64-x86-64 mingw-w64-x86-64-dev
   ```
2. Build and link everything from [TestScreenOutput/](TestScreenOutput):
   ```bash
   cd TestScreenOutput
   x86_64-w64-mingw32-g++ -std=c++17 -fopenmp -O2 \
     *.cpp -o SimulatePixels.exe -lgdi32 -luser32
   ```
   > On a case-sensitive filesystem (e.g. Linux), mingw's header is named
   > `windows.h` (lowercase) while the source includes `<Windows.h>`, so the
   > compiler won't find it by default. Point it at a shim directory with a
   > correctly-cased symlink:
   > ```bash
   > mkdir -p /tmp/winhdr && ln -sf /usr/x86_64-w64-mingw32/include/windows.h /tmp/winhdr/Windows.h
   > x86_64-w64-mingw32-g++ -std=c++17 -fopenmp -O2 -I /tmp/winhdr *.cpp -o SimulatePixels.exe -lgdi32 -luser32
   > ```
3. (Optional) Run it under Wine if available:
   ```bash
   wine SimulatePixels.exe
   ```

## Project layout

- [TestScreenOutput/](TestScreenOutput) — the simulation itself:
  - `Field` / `FieldController` — owns the raw grid of `MatType` cells and
    low-level indexing/get/set/flip operations.
  - `Domain` (`BaseDomain`) — the single-threaded view over a `Field`, used
    by the main `Simulator` loop (movement, edge handling, density swaps).
  - `DomainInterface` / `DomainController` — an in-progress interface layer
    intended to unify `BaseDomain` and the multithreaded sub-domains behind
    one API.
  - `MT_sd_Controller` / `MT_subDomain` — divides the field into a grid of
    boxes and simulates them in parallel using a 4-colour (red/black-style)
    checkerboard scheme via OpenMP, so adjacent boxes are never updated at
    the same time.
  - `Simulator` — owns the `Field`/`Domain`, the active-cell list, and runs
    the per-frame move + density simulation passes.
  - `Sand.h`, `Water.h`, `Salt.h`, `Fire.h`, `Wood.h`, `Smoke.h`, `Steam.h`,
    `Blood.h`, `Default.h` — per-material behaviour (`Material` subclasses).
  - `win32_platform.cpp` — Win32 entry point, window creation and the main
    loop.
  - `ScreenRenderer` — draws the simulation field into the window's backing
    bitmap.
- [UnitTests/](UnitTests) — MSTest-based unit tests (Visual Studio only).
