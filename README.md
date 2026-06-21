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

To refresh the vendored Carp runtime headers after updating the Carp submodule:

```sh
git submodule update --init --recursive
./scripts/update-carp-core.sh
```

The helper copies from `subprojects/Carp/core` by default. You can also pass an
explicit Carp checkout or core directory if you want to refresh from another
source:

```sh
./scripts/update-carp-core.sh /path/to/carp
```

After regenerating the headers, rebuild from the committed C output with Meson,
or regenerate `out/main.c` from Carp first if your change needs it.

## Run

```sh
./build/KoiRTS
```
