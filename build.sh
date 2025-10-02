#!/bin/sh
set -e
. ./config.sh

# Create the output directories.
mkdir -p "$INTERMEDIATE_DIR"
mkdir -p "$SYSROOT_DIR"

. ./headers.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT_DIR" $MAKE)
done
