#!/bin/sh
set -e
. ./config.sh

for PROJECT in $PROJECTS; do
  (
    cd "$PROJECT" || exit 1
    $MAKE clean
  )
done

rm -rf sysroot
rm -rf isodir
rm -rf LambdaOS.iso
