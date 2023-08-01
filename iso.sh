#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/FoundexOS.kernel isodir/boot/FoundexOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "FoundexOS" {
	multiboot /boot/FoundexOS.kernel
}
EOF
grub-mkrescue -o FoundexOS.iso isodir
