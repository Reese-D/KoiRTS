project('KoiRTS', ['c', 'cpp'],
    version: '0.1.0',
    default_options: [
        'c_std=c99',
        'cpp_std=c++17',
        'warning_level=2',
    ])

cmake = import('cmake')

carp_core_inc = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/carp_stdbool.h" | head -n 1); dirname "$p"',
    check: true
).stdout().strip()

raylib_prefix_paths = [
    run_command(
        'sh', '-c',
        'p=$(find /gnu/store -path "*/include/X11/Xlib.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
        check: true
    ).stdout().strip(),
    run_command(
        'sh', '-c',
        'p=$(find /gnu/store -path "*/include/X11/X.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
        check: true
    ).stdout().strip(),
    run_command(
        'sh', '-c',
        'p=$(find /gnu/store -path "*/include/X11/Xcursor/Xcursor.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
        check: true
    ).stdout().strip(),
    run_command(
        'sh', '-c',
        'p=$(find /gnu/store -path "*/include/X11/extensions/Xrandr.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
        check: true
    ).stdout().strip(),
    run_command(
        'sh', '-c',
        'p=$(find /gnu/store -path "*/include/X11/extensions/Xinerama.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
        check: true
    ).stdout().strip(),
    run_command(
        'sh', '-c',
        'p=$(find /gnu/store -path "*/include/X11/extensions/XInput2.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
        check: true
    ).stdout().strip(),
    run_command(
        'sh', '-c',
        'p=$(find /gnu/store -path "*/include/X11/extensions/Xext.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
        check: true
    ).stdout().strip(),
    run_command(
        'sh', '-c',
        'p=$(find /gnu/store -path "*/include/GL/gl.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
        check: true
    ).stdout().strip(),
    run_command(
        'sh', '-c',
        'p=$(find /gnu/store -path "*/include/AL/al.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
        check: true
    ).stdout().strip(),
]

raylib_x11_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/X.h" | head -n 1); dirname "$(dirname "$p")"',
    check: true
).stdout().strip()

raylib_x11_xlib_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/Xlib.h" | head -n 1); dirname "$(dirname "$p")"',
    check: true
).stdout().strip()

raylib_x11_xkblib_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/XKBlib.h" | head -n 1); dirname "$(dirname "$p")"',
    check: true
).stdout().strip()

raylib_x11_xkb_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/extensions/XKB.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
    check: true
).stdout().strip()

raylib_x11_include_combo = raylib_x11_xlib_include + ';' + raylib_x11_include

raylib_x11_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libX11.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

raylib_xcursor_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/Xcursor/Xcursor.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
    check: true
).stdout().strip()

raylib_xcursor_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libXcursor.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

raylib_xext_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/extensions/Xext.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
    check: true
).stdout().strip()

raylib_xshape_include = raylib_xext_include

raylib_xext_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libXext.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

raylib_xi_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/extensions/XInput.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
    check: true
).stdout().strip()

raylib_xi_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libXi.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

raylib_xinerama_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/extensions/Xinerama.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
    check: true
).stdout().strip()

raylib_xinerama_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libXinerama.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

raylib_xrandr_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/extensions/Xrandr.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
    check: true
).stdout().strip()

raylib_xrandr_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libXrandr.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

raylib_xrender_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/extensions/Xrender.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
    check: true
).stdout().strip()

raylib_xrender_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libXrender.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

raylib_xrandr_include_combo = raylib_xrandr_include + ';' + raylib_xrender_include

raylib_xfixes_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/X11/extensions/Xfixes.h" | head -n 1); dirname "$(dirname "$(dirname "$p")")"',
    check: true
).stdout().strip()

raylib_xfixes_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libXfixes.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

raylib_gl_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libGL.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

raylib_opengl_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/GL/gl.h" | head -n 1); dirname "$(dirname "$p")"',
    check: true
).stdout().strip()

raylib_openal_include = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -path "*/include/AL/al.h" | head -n 1); dirname "$(dirname "$p")"',
    check: true
).stdout().strip()

raylib_openal_lib = run_command(
    'sh', '-c',
    'p=$(find /gnu/store -name "libopenal.so" | head -n 1); printf "%s\n" "$p"',
    check: true
).stdout().strip()

add_project_arguments(
    '-I' + carp_core_inc,
    '-D_POSIX_C_SOURCE=199309L',
    '-D_XOPEN_SOURCE=500',
    '-D_GNU_SOURCE',
    language: 'c',
)

raylib_opts = cmake.subproject_options()
raylib_opts.add_cmake_defines({
    'PLATFORM': 'Desktop',
    'BUILD_EXAMPLES': 'OFF',
    'CUSTOMIZE_BUILD': 'OFF',
    'BUILD_SHARED_LIBS': 'OFF',
    'GLFW_BUILD_WAYLAND': 'OFF',
    'GLFW_BUILD_X11': 'ON',
    'USE_EXTERNAL_GLFW': 'OFF',
    'WITH_PIC': 'ON',
    'CMAKE_PREFIX_PATH': ';'.join(raylib_prefix_paths),
    'X11_X11_INCLUDE_PATH': raylib_x11_include_combo,
    'X11_X11_LIB': raylib_x11_lib,
    'X11_Xlib_INCLUDE_PATH': raylib_x11_xlib_include,
    'X11_Xkblib_INCLUDE_PATH': raylib_x11_xkblib_include,
    'X11_Xkb_INCLUDE_PATH': raylib_x11_xkb_include,
    'X11_Xcursor_INCLUDE_PATH': raylib_xcursor_include,
    'X11_Xcursor_LIB': raylib_xcursor_lib,
    'X11_Xext_INCLUDE_PATH': raylib_xext_include,
    'X11_Xext_LIB': raylib_xext_lib,
    'X11_Xshape_INCLUDE_PATH': raylib_xshape_include,
    'X11_Xi_INCLUDE_PATH': raylib_xi_include,
    'X11_Xi_LIB': raylib_xi_lib,
    'X11_Xinerama_INCLUDE_PATH': raylib_xinerama_include,
    'X11_Xinerama_LIB': raylib_xinerama_lib,
    'X11_Xrandr_INCLUDE_PATH': raylib_xrandr_include_combo,
    'X11_Xrandr_LIB': raylib_xrandr_lib,
    'X11_Xrender_INCLUDE_PATH': raylib_xrender_include,
    'X11_Xrender_LIB': raylib_xrender_lib,
    'X11_Xfixes_INCLUDE_PATH': raylib_xfixes_include,
    'X11_Xfixes_LIB': raylib_xfixes_lib,
    'OPENGL_INCLUDE_DIR': raylib_opengl_include,
    'OPENGL_gl_LIBRARY': raylib_gl_lib,
    'OPENAL_INCLUDE_DIR': raylib_openal_include,
    'OPENAL_LIBRARY': raylib_openal_lib,
})
raylib_proj = cmake.subproject('raylib', options: raylib_opts)
raylib_dep = raylib_proj.dependency('raylib')

carp_out = custom_target('carp_compile',
    input: 'src/main.carp',
    output: 'main.c',
    command: ['carp', '--generate-only', '--eval-preload', '(Project.config "output-directory" ".")', '-b', '@INPUT@'],
    build_by_default: true)

executable('KoiRTS',
    carp_out,
    dependencies: [raylib_dep])
