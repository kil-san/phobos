#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/phobos.kernel isodir/boot/phobos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "phobos" {
	multiboot /boot/phobos.kernel
}
EOF
i686-elf-grub-mkrescue -o phobos.iso isodir
