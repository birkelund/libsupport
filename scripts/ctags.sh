#!/bin/bash

rm -f "${MESON_SOURCE_ROOT}/tags"

for dir in "include" "src"; do
  ctags -R -f "${MESON_SOURCE_ROOT}/tags" --append "${MESON_SOURCE_ROOT}/$dir"
done
