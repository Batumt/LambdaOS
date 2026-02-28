#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/LambdaOS.kernel isodir/boot/LambdaOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "LambdaOS" {
	multiboot /boot/LambdaOS.kernel
}
EOF
grub-mkrescue -o LambdaOS.iso isodir
