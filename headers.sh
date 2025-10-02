#!/bin/sh
set -e
. ./config.sh

mkdir -p "$SYSROOT_DIR"

for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT_DIR" $MAKE install-headers)
done
