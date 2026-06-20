project('cimgui', ['c', 'cpp'],
    default_options: ['cpp_std=c++17'])

# Expects lib/cimgui submodule to be checked out.
# cimgui wraps Dear ImGui (C++) with a C API.
# Dear ImGui source lives in lib/cimgui/imgui/

cimgui_src = files(
    '../../lib/cimgui/cimgui.cpp',
    '../../lib/cimgui/imgui/imgui.cpp',
    '../../lib/cimgui/imgui/imgui_draw.cpp',
    '../../lib/cimgui/imgui/imgui_tables.cpp',
    '../../lib/cimgui/imgui/imgui_widgets.cpp',
)

cimgui_inc = include_directories(
    '../../lib/cimgui',
    '../../lib/cimgui/imgui',
)

cimgui_lib = static_library('cimgui',
    cimgui_src,
    include_directories: cimgui_inc)

cimgui_dep = declare_dependency(
    link_with: cimgui_lib,
    include_directories: cimgui_inc)
