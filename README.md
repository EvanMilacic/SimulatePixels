# SimulatePixels

A pixel-based falling-sand simulation where every pixel is a cell made of a
material (sand, water, salt, fire, wood, smoke, steam, blood, ...), each with
its own density, movement rules and interactions. The simulation field can
optionally be split into sub-domains and advanced in parallel with OpenMP
(see `MT_sd_Controller` / `MT_subDomain`).

Rendering/windowing is built on **SDL2** via a CMake build, so the same
source builds and runs natively on **Windows** and **Linux**, and also
compiles to **WebAssembly** (runs in the browser) via Emscripten. A legacy
Win32/GDI-only entry point (`win32_platform.cpp`) is also still present for
anyone who specifically wants a pure Win32 build in Visual Studio, but it's
not part of the CMake build below.

## Option A: Native build (Windows or Linux)

### 1. Install prerequisites

- **CMake** (3.13+) and a C++17 compiler.
- **SDL2** development libraries:
  - Linux (Debian/Ubuntu): `sudo apt install libsdl2-dev cmake build-essential`
  - Windows: easiest via [vcpkg](https://github.com/microsoft/vcpkg):
    ```powershell
    vcpkg install sdl2:x64-windows
    ```
    (or install SDL2 some other way and make sure `find_package(SDL2)` can
    find it — e.g. set `CMAKE_TOOLCHAIN_FILE` to vcpkg's
    `scripts/buildsystems/vcpkg.cmake`).

### 2. Configure and build

From the repo root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# if using vcpkg on Windows, add:
#   -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
cmake --build build -j
```

This produces a `SimulatePixels` (or `SimulatePixels.exe` on Windows)
executable inside `build/`.

### 3. Run it

```bash
./build/SimulatePixels        # Linux
.\build\SimulatePixels.exe    # Windows
```

A resizable window opens and the simulation starts immediately: sand, salt,
blood, water, steam and smoke are continuously dropped at fixed points (see
`Simulator::setCenterSand`) and fall/flow/settle according to each
material's density and movement rules. Close the window to exit.

## Option B: Run it in the browser (WebAssembly via Emscripten)

The same CMake project builds with [Emscripten](https://emscripten.org/)
instead of a native compiler — no code changes needed, just a different
toolchain.

1. Install the official **emsdk** toolchain (recommended — the `emscripten`
   package in Debian/Ubuntu's apt repos ships with a read-only, "frozen"
   cache that cannot fetch the SDL2 port and fails to link; `emsdk` doesn't
   have this problem):
   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh   # run this in every new shell before building
   ```
2. Configure and build with the Emscripten CMake wrapper:
   ```bash
   emcmake cmake -S . -B build-web -DCMAKE_BUILD_TYPE=Release
   cmake --build build-web -j
   ```
   This produces `build-web/SimulatePixels.html` (plus matching `.js`/`.wasm`
   files) — Emscripten's SDL2 port is used automatically, so no system SDL2
   package is required for this build. Note: OpenMP is intentionally not
   linked in for this target (it would require `-pthread`, `SharedArrayBuffer`
   and cross-origin isolation headers), so the `#pragma omp parallel for` in
   `MT_sd_Controller.cpp` is simply ignored by the compiler and the
   simulation runs single-threaded in the browser.
3. Serve the output directory over HTTP (opening the `.html` file directly
   via `file://` won't work due to browser restrictions on loading `.wasm`):
   ```bash
   cd build-web
   python3 -m http.server 8000
   ```
4. Open `http://localhost:8000/SimulatePixels.html` in a browser. The
   simulation runs on an HTML5 canvas, driven by the browser's animation
   loop.

## Legacy option: pure Win32/GDI build in Visual Studio

If you specifically want to avoid the SDL2 dependency on Windows, the
original Win32/GDI entry point still works:

1. Install **Visual Studio** (2019+) with the **Desktop development with
   C++** workload.
2. Create a new C++ project and add every `.cpp`/`.h` file from
   [TestScreenOutput/](TestScreenOutput) **except `platform_sdl.cpp`**.
3. Project Properties → **C/C++ → Language**: set **C++ Language Standard**
   to ISO C++17 (or later) and **Open MP Support** to **Yes (/openmp)**.
4. Project Properties → **Linker → System**: set **SubSystem** to
   **Windows** (`/SUBSYSTEM:WINDOWS`), since the entry point is `WinMain`.
5. Build (Ctrl+Shift+B) and run (F5).

### Unit tests

[UnitTests/](UnitTests) uses MSTest's `CppUnitTestFramework` and requires the
**Test Development** workload component in Visual Studio.

## Project layout

- [TestScreenOutput/](TestScreenOutput) — the simulation itself:
  - `Index2` / `Motion2` — a 2D cell position (`Index_t`, unsigned) and a 2D
    movement delta (signed `int`), respectively. `FieldData` describes a
    field's width/height/size.
  - `Field<T>` / `LargeVector<T>` — a templated 2D grid of `T` built on a
    flat `std::vector<T>` wrapper, addressable by either a linear `Index_t`
    or an `Index2`.
  - `Domain` — the single-threaded view over a `Field<MatType>`, used by the
    main `Simulator` loop (movement, edge handling, density swaps), entirely
    `Index2`-based (no linear indexing exposed).
  - `MT_sd_Controller` / `MT_subDomain` — divides the field into a grid of
    boxes and simulates them in parallel using a 4-colour (red/black-style)
    checkerboard scheme via OpenMP, so adjacent boxes are never updated at
    the same time. Each sub-domain iterates its `Index2` range directly and
    calls `Simulator::simulateCellAt(Index2)` per cell.
  - `Simulator` — owns the `Domain`, the active-cell list, and runs the
    per-frame move + density simulation passes.
  - `Sand.h`, `Water.h`, `Salt.h`, `Fire.h`, `Wood.h`, `Smoke.h`, `Steam.h`,
    `Blood.h`, `Default.h` — per-material behaviour (`Material` subclasses).
  - `platform_sdl.cpp` — cross-platform entry point (Windows/Linux/browser)
    built on SDL2: window/canvas creation, the main loop, and uploading the
    simulation's pixel buffer to a texture each frame.
  - `win32_platform.cpp` — legacy Win32-only entry point (GDI `CreateWindow`
    + `StretchDIBits`), not used by the CMake build.
  - `ScreenRenderer` — draws the simulation field into the platform's
    backing pixel buffer (`RenderState`), independent of how that buffer
    ends up on screen.
- [UnitTests/](UnitTests) — MSTest-based unit tests (Visual Studio only).
- [CMakeLists.txt](CMakeLists.txt) — builds the SDL2 platform layer plus the
  simulation core natively, or via Emscripten for the browser.

