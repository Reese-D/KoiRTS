project('KoiRTS', ['c', 'cpp'],
    version: '0.1.0',
    default_options: [
        'c_std=c99',
        'cpp_std=c++17',
        'warning_level=2',
    ])

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------

# Raylib — git submodule in lib/raylib, has native Meson support
# Uncomment once submodule is populated:
# raylib_dep = dependency('raylib', fallback: ['raylib', 'raylib_dep'])

# cglm — header-only, has native Meson support
# Uncomment once vendored or submoduled:
# cglm_dep = dependency('cglm', fallback: ['cglm', 'cglm_dep'])

# flecs — vendored single amalgamation (vendor/flecs.h + vendor/flecs.c)
# Uncomment once vendor/flecs.c is present:
# flecs = static_library('flecs', 'vendor/flecs.c',
#     include_directories: include_directories('vendor'))
# flecs_dep = declare_dependency(
#     link_with: flecs,
#     include_directories: include_directories('vendor'))

# miniaudio — single header (vendor/miniaudio.h)
# Uncomment once vendor/miniaudio.h is present:
# miniaudio_dep = declare_dependency(
#     include_directories: include_directories('vendor'))

# ENet — vendored source tree (vendor/enet/)
# Uncomment once vendor/enet/ is populated:
# enet_common_src = files(
#     'vendor/enet/callbacks.c',
#     'vendor/enet/compress.c',
#     'vendor/enet/host.c',
#     'vendor/enet/list.c',
#     'vendor/enet/packet.c',
#     'vendor/enet/peer.c',
#     'vendor/enet/protocol.c',
# )
# enet_platform_src = host_machine.system() == 'windows' \
#     ? files('vendor/enet/win32.c') \
#     : files('vendor/enet/unix.c')
# enet = static_library('enet',
#     enet_common_src + enet_platform_src,
#     include_directories: include_directories('vendor/enet/include'))
# enet_dep = declare_dependency(
#     link_with: enet,
#     include_directories: include_directories('vendor/enet/include'))

# cimgui — subproject with hand-written meson definition (subprojects/cimgui/)
# Dear ImGui is C++; cimgui is a C wrapper. Requires lib/cimgui submodule.
# Uncomment once submodule and subproject definition are in place:
# cimgui_dep = dependency('cimgui', fallback: ['cimgui', 'cimgui_dep'])

# ---------------------------------------------------------------------------
# Hand-written C/C++ (performance-critical hot paths)
# ---------------------------------------------------------------------------

# Uncomment once source files are implemented:
# csrc = static_library('csrc',
#     'csrc/flowfield.c',
#     'csrc/spatial_hash.c',
#     'csrc/imgui_impl.cpp',
#     include_directories: include_directories('include'),
#     dependencies: [raylib_dep, flecs_dep, cimgui_dep])

# ---------------------------------------------------------------------------
# Carp compilation
# ---------------------------------------------------------------------------
# Carp compiler reads src/main.carp and emits C into out/
# Requires Carp to be installed and on PATH

# carp_out = custom_target('carp_compile',
#     input: 'src/main.carp',
#     output: 'main.c',
#     command: ['carp', '--no-repl', '-b', '@INPUT@'],
#     build_by_default: true)

# ---------------------------------------------------------------------------
# Final executable
# ---------------------------------------------------------------------------

# executable('KoiRTS',
#     carp_out,
#     link_with: csrc,
#     dependencies: [
#         raylib_dep,
#         flecs_dep,
#         enet_dep,
#         cimgui_dep,
#         miniaudio_dep,
#         cglm_dep,
#     ])
