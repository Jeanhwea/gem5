export IMG_ROOT=/opt/src/gem5/cpu_tests/aarch-system-20220707

./build/ARM/gem5.opt configs/example/arm/fs_bigLITTLE.py \
                     --caches \
                     --bootloader="$IMG_ROOT/binaries/boot.arm" \
                     --kernel="$IMG_ROOT/binaries/vmlinux.arm" \
                     --disk="$IMG_ROOT/disks/m5_exit.squashfs.arm" \
                     --bootscript=./util/dist/test/simple_bootscript.rcS
