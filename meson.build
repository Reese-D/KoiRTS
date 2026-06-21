project('KoiRTS', 'c',
    version: '0.0.1',
    default_options: [
        'c_std=c99',
        'warning_level=2',
    ])

cmake = import('cmake')
cc = meson.get_compiler('c')
carp_prog = find_program('carp', required: false)
stack_prog = find_program('stack', required: carp_prog.found() == false)

carp_core_inc = include_directories('vendor/carp-core')
carp_stack_yaml = join_paths(meson.project_source_root(), 'subprojects', 'Carp', 'stack.yaml')

raylib_opts = cmake.subproject_options()
raylib_opts.add_cmake_defines({
    'PLATFORM': 'Desktop',
    'BUILD_EXAMPLES': 'OFF',
    'BUILD_SHARED_LIBS': 'OFF',
    'USE_EXTERNAL_GLFW': 'OFF',
})

if host_machine.system() == 'windows'
    raylib_opts.add_cmake_defines({
        'GLFW_BUILD_X11': 'OFF',
        'GLFW_BUILD_WAYLAND': 'OFF',
    })
else
    raylib_opts.add_cmake_defines({
        'GLFW_BUILD_X11': 'ON',
        'GLFW_BUILD_WAYLAND': 'OFF',
    })
endif

raylib_proj = cmake.subproject('raylib', options: raylib_opts)
raylib_dep = raylib_proj.dependency('raylib')
math_dep = cc.find_library('m', required: false)
appleframeworks_dep = []
if host_machine.system() == 'darwin'
    appleframeworks_dep += dependency(
        'appleframeworks',
        modules: ['Cocoa', 'IOKit', 'CoreFoundation'],
    )
endif

c_args = []
if host_machine.system() == 'linux'
    c_args += [
        '-D_POSIX_C_SOURCE=199309L',
        '-D_XOPEN_SOURCE=500',
        '-D_GNU_SOURCE',
    ]
elif host_machine.system() == 'darwin'
    c_args += [
        '-D_DARWIN_C_SOURCE',
    ]
else
    c_args += [
        '-DWIN32_LEAN_AND_MEAN',
        '-DNOGDI',
        '-DNOUSER',
    ]
endif

if carp_prog.found()
    message('Using system carp to generate build/main.c')
    carp_cmd = [
        carp_prog,
        '--generate-only',
        '--eval-preload',
        '(Project.config "output-directory" ".")',
        '-b',
    ]
else
    message('Using vendored Carp via stack to generate build/main.c')
    carp_cmd = [
        stack_prog,
        '--stack-yaml',
        carp_stack_yaml,
        'exec',
        'carp',
        '--',
        '--generate-only',
        '--eval-preload',
        '(Project.config "output-directory" ".")',
        '-b',
    ]
endif

main_c = custom_target('main_c_from_carp',
    input: 'src/main.carp',
    output: 'main.c',
    command: carp_cmd + ['@INPUT@'],
    build_always_stale: true,
    build_by_default: true)


executable('KoiRTS',
    main_c,
    include_directories: carp_core_inc,
    dependencies: [raylib_dep, math_dep] + appleframeworks_dep,
    c_args: c_args,
    install: true)
