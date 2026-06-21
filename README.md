# KoiRTS

## Build

This project generates `main.c` in the build directory from Carp during the
build. If `carp` is already installed, Meson will use it directly. Otherwise
it falls back to the vendored Carp submodule via `stack`. Make sure `meson`,
`cmake`, and `ninja` are on `PATH`, and set `CARP_DIR` to the Carp submodule
root:

```sh
git submodule update --init --recursive
export CARP_DIR="$PWD/subprojects/Carp"
meson setup build
meson compile -C build
```

If you do not have a system `carp`, also install `stack` so Meson can build
the vendored compiler.

If you need to rebuild from scratch:

```sh
rm -rf build
meson setup build
meson compile -C build
```

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

After regenerating the headers, rebuild with Meson.

## Run

```sh
./build/KoiRTS
```
