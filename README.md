# KoiRTS

## Build

This project uses Meson, Carp, and the raylib CMake subproject. Make sure `carp`, `meson`, `cmake`, and `ninja` are on `PATH`.

```sh
git submodule update --init --recursive
meson setup build
meson compile -C build
```

If you need to rebuild from scratch:

```sh
rm -rf build
meson setup build
meson compile -C build
```

## Run

```sh
./build/KoiRTS
```
