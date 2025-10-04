#!/bin/sh
set -e
. ./config.sh
. ./build.sh

ISODIR="$INTERMEDIATE_DIR/isodir"

mkdir -p "$ISODIR"
mkdir -p "$ISODIR/boot"
mkdir -p "$ISODIR/boot/grub"

cp "$SYSROOT_DIR/boot/phoibos.kernel" "$ISODIR/boot/phoibos.kernel"
cat > "$ISODIR/boot/grub/grub.cfg" << EOF
menuentry "phoibos" {
	multiboot /boot/phoibos.kernel
}
EOF
i686-elf-grub-mkrescue -o "$ISO_PATH" "$ISODIR"
