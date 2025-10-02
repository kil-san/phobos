#!/bin/sh
set -e
. ./config.sh
. ./build.sh

ISODIR="$INTERMEDIATE_DIR/isodir"

mkdir -p "$ISODIR"
mkdir -p "$ISODIR/boot"
mkdir -p "$ISODIR/boot/grub"

cp "$SYSROOT_DIR/boot/phobos.kernel" "$ISODIR/boot/phobos.kernel"
cat > "$ISODIR/boot/grub/grub.cfg" << EOF
menuentry "phobos" {
	multiboot /boot/phobos.kernel
}
EOF
i686-elf-grub-mkrescue -o "$ISO_PATH" "$ISODIR"
