#!/usr/bin/env sh

set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
dest_dir="$repo_root/vendor/carp-core"
default_src_dir="$repo_root/subprojects/Carp/core"

usage() {
    printf '%s\n' "Usage: $0 [PATH_TO_CARP_CORE_OR_CARP_CHECKOUT]" >&2
    printf '%s\n' "Copies Carp runtime headers from subprojects/Carp/core into vendor/carp-core." >&2
    exit 1
}

src_arg="${1:-}"
if [ "$#" -gt 1 ]; then
    usage
fi

if [ -n "$src_arg" ]; then
    src_dir=$src_arg
else
    src_dir=$default_src_dir
fi

if [ -d "$src_dir/core" ]; then
    src_dir="$src_dir/core"
fi

if [ ! -d "$src_dir" ]; then
    printf '%s\n' "Source directory not found: $src_dir" >&2
    exit 1
fi

mkdir -p "$dest_dir"
rm -f "$dest_dir"/*.h
cp "$src_dir"/*.h "$dest_dir"/

printf '%s\n' "Updated $dest_dir from $src_dir"
