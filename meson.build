project('KoiRTS', 'c',
    version: '0.1.0',
    default_options: [
        'c_std=c99',
        'warning_level=2',
    ])

cmake = import('cmake')
cc = meson.get_compiler('c')

carp_core_inc = include_directories('vendor/carp-core')

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

c_args = []
if host_machine.system() != 'windows'
    c_args += [
        '-D_POSIX_C_SOURCE=199309L',
        '-D_XOPEN_SOURCE=500',
        '-D_GNU_SOURCE',
    ]
endif

if get_option('build_from_carp')
    main_c = custom_target('main_c_from_carp',
        input: 'src/main.carp',
        output: 'main.c',
        command: [
            'carp',
            '--generate-only',
            '--eval-preload',
            '(Project.config "output-directory" ".")',
            '-b',
            '@INPUT@',
        ],
        build_by_default: true)
else
    main_c = files('out/main.c')
endif

executable('KoiRTS',
    main_c,
    include_directories: carp_core_inc,
    dependencies: [raylib_dep, math_dep],
    c_args: c_args,
    install: true)
