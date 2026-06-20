# KoiRTS — Project Plan & Reference

## Overview

A 2D real-time strategy game built with a functional/Lisp-oriented tech stack,
prioritising performance, cross-platform support, and control over dependencies.

---

## Tech Stack

### Language: Carp
- Lisp (Clojure-influenced syntax) that compiles to C
- No garbage collector — uses a borrow checker for memory management
- No GC pauses, important for real-time gameplay with large entity counts
- Native code performance via C compilation
- C interop is essentially free (it compiles to C)

### ECS: flecs
- C99 entity component system library
- Archetype-based (cache-friendly iteration over large entity sets)
- Built-in support for hierarchies and relationships (units, factions, squads)
- Vendored as single amalgamation (flecs.h + flecs.c)
- Chosen over ENTT because ENTT is C++ and Carp compiles to C

### Rendering / Framework: Raylib
- C library handling 2D rendering, audio, input, and windowing
- Cross-platform: Linux, macOS, Windows
- Used as a git submodule, built from source per platform
- Covers most rendering needs for a 2D RTS

### Networking: ENet
- UDP-based networking library designed for games
- Provides reliable/unreliable channels, sequencing, congestion control
- C library, vendored directly
- Architecture: lockstep networking (sync inputs, deterministic simulation)
  is preferred over state sync for bandwidth efficiency

### UI: cimgui (Dear ImGui)
- cimgui is a C wrapper around Dear ImGui (C++)
- Immediate-mode UI well-suited to RTS HUD needs:
  unit panels, resource bars, build queues, minimap overlays
- Used as a git submodule with a hand-written meson subproject definition

### Audio: miniaudio
- Single-header C library for audio playback and mixing
- More control than Raylib's built-in audio
- Useful for positional audio (unit acknowledgement sounds, ambient audio)
- Vendored as single header (miniaudio.h)

### Math: cglm
- C99 linear algebra library (vectors, matrices, quaternions)
- Header-only
- Used for camera transforms, collision math, pathfinding geometry

### Build System: Meson
- Cleaner syntax than CMake, Ninja backend for fast builds
- Raylib and cglm have native Meson support
- cimgui requires a hand-written meson subproject definition (see subprojects/cimgui/)
- ENet platform handling (unix.c vs win32.c) is explicit in meson.build

### CI: GitHub Actions
- Multi-platform matrix: ubuntu-latest, macos-latest, windows-latest
- Submodules checked out recursively (raylib, cimgui both have nested submodules)

---

## Architecture

### Dependency Map

```
Carp source (src/)
    └── compiles to C (out/) via carp --no-repl -b
            └── linked with:
                    ├── flecs          (ECS)
                    ├── raylib         (rendering/input/audio)
                    ├── enet           (networking)
                    ├── cimgui         (UI)
                    ├── miniaudio      (audio)
                    ├── cglm           (math)
                    └── csrc/          (hand-written C/C++ hot paths)
                            ├── flowfield.c      (pathfinding)
                            ├── spatial_hash.c   (spatial queries)
                            └── imgui_impl.cpp   (ImGui backend glue)
```

### Performance Strategy

- Game logic, AI state machines, event handling in Carp
- Hot paths (entity movement, pathfinding, spatial queries) in hand-written C (csrc/)
- Entity data kept in flecs components (contiguous memory, cache-friendly)
- Flow field pathfinding: one computation per destination, all units follow
  (avoids per-unit A* which is too expensive at scale)
- Spatial hash for neighbour queries, collision, and line-of-sight

### Networking Architecture

- Lockstep model: only inputs are synced over the network
- Simulation must be fully deterministic (avoid floats where possible,
  or use fixed-point math for game state)
- ENet handles the transport layer

---

## Directory Structure

```
KoiRTS/
├── src/                    # Carp source files
│   ├── main.carp           # Entry point
│   ├── game/               # Core game state and logic
│   │   ├── world.carp
│   │   ├── units.carp
│   │   └── faction.carp
│   ├── systems/            # ECS systems called each frame
│   │   ├── movement.carp
│   │   ├── combat.carp
│   │   ├── pathfinding.carp
│   │   └── network.carp
│   └── ui/
│       └── hud.carp
├── csrc/                   # Hand-written C/C++ (performance-critical)
│   ├── flowfield.c
│   ├── flowfield.h
│   ├── spatial_hash.c
│   ├── spatial_hash.h
│   └── imgui_impl.cpp      # cimgui/ImGui platform backend glue
├── include/                # Headers for csrc
├── vendor/                 # Vendored single-file libraries
│   ├── flecs.h
│   ├── flecs.c
│   ├── miniaudio.h
│   ├── cglm/               # Header-only
│   └── enet/               # Small source tree
├── lib/                    # Git submodules (larger deps)
│   ├── raylib/
│   └── cimgui/
├── subprojects/            # Meson subproject definitions
│   └── cimgui/
│       └── meson.build     # Hand-written (cimgui has no native Meson support)
├── assets/
│   ├── sprites/
│   ├── sounds/
│   ├── maps/
│   └── fonts/
├── out/                    # Carp-generated C output (gitignored)
├── build/                  # Meson build directory (gitignored)
├── .github/
│   └── workflows/
│       └── build.yml
├── .gitignore
├── meson.build
└── PLAN.md                 # This file
```

---

## Dependencies — Setup Checklist

### Git Submodules (run after cloning)

```bash
git submodule add https://github.com/raysan5/raylib lib/raylib
git submodule add https://github.com/cimgui/cimgui lib/cimgui
git submodule update --init --recursive
```

### Vendored Libraries (copy source files into vendor/)

- **flecs** — download `flecs.h` and `flecs.c` from https://github.com/SanderMertens/flecs
  (use the single-file amalgamation release)
- **miniaudio** — download `miniaudio.h` from https://github.com/mackron/miniaudio
- **cglm** — copy `cglm/` headers from https://github.com/recp/cglm
- **ENet** — copy source from https://github.com/lsalzman/enet into `vendor/enet/`

### Carp

Install Carp from https://github.com/carp-lang/Carp
On Guix: check `guix search carp` — may require manual install or a channel package.

---

## Build Instructions

```bash
# First time setup
git clone <repo-url> KoiRTS
cd KoiRTS
git submodule update --init --recursive
# (vendor the single-file libraries per checklist above)

# Build
meson setup build
meson compile -C build

# Run
./build/KoiRTS
```

---

## Development Phases

### Phase 1 — Foundation
- [ ] Meson build working end-to-end (Carp → C → binary)
- [ ] Raylib window opening
- [ ] flecs world initialised
- [ ] Basic Carp/C FFI bindings verified

### Phase 2 — Core Gameplay Systems
- [ ] Unit entities (position, velocity, health components)
- [ ] Spatial hash for neighbour queries
- [ ] Flow field pathfinding (csrc/flowfield.c)
- [ ] Basic unit movement and collision avoidance
- [ ] Unit selection (click and drag box)

### Phase 3 — RTS Features
- [ ] Faction/player ownership relationships (flecs)
- [ ] Combat system
- [ ] Resource system
- [ ] Building placement
- [ ] Basic AI opponent

### Phase 4 — UI
- [ ] cimgui HUD (resource bars, unit panel, minimap)
- [ ] Main menu
- [ ] In-game settings

### Phase 5 — Networking
- [ ] ENet session setup (host/join)
- [ ] Lockstep input synchronisation
- [ ] Determinism audit (fixed-point or careful float usage)

### Phase 6 — Polish
- [ ] Audio (miniaudio positional sounds)
- [ ] Asset pipeline (sprites, maps)
- [ ] Cross-platform build verification

---

## Key Decisions Log

| Decision | Choice | Rationale |
|---|---|---|
| Language | Carp | Lisp + no GC + compiles to C |
| ECS | flecs | C99, archetype-based, good for large entity counts |
| Rendering | Raylib | C, cross-platform, 2D-focused |
| Networking | ENet | UDP game networking, C, lockstep-friendly |
| UI | cimgui | C wrapper for Dear ImGui, practical for RTS HUD |
| Audio | miniaudio | Single header C, more control than Raylib audio |
| Build | Meson | Cleaner than CMake, Ninja backend |
| Hosting | GitHub | Best CI/CD ecosystem for multi-platform C builds |
| Engine | None | Libraries only, full control |
| Pathfinding | Flow fields | Cheaper than per-unit A* at RTS scale |
