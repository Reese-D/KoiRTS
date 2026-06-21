# KoiRTS

## Build

This project builds from the committed C output in `out/main.c`. Make sure `meson`, `cmake`, and `ninja` are on `PATH`.

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

To build from Carp through Meson instead of the committed C output, configure with:

```sh
meson setup build -Dbuild_from_carp=true
meson compile -C build
```

To regenerate `out/main.c` from Carp during development, run:

```sh
carp --generate-only --eval-preload '(Project.config "output-directory" ".")' -b src/main.carp
```

Then rebuild with Meson.

## Run

```sh
./build/KoiRTS
```
