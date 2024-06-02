export IMG_ROOT=/opt/src/gem5/cpu_tests/aarch-system-20220707

./build/ARM/gem5.opt configs/example/arm/fs_power.py \
                     --caches \
                     --bootloader="$IMG_ROOT/binaries/boot.arm64" \
                     --kernel="$IMG_ROOT/binaries/vmlinux.arm64" \
                     --disk="$IMG_ROOT/ubuntu-18.04-arm64-docker.img" \
                     --bootscript=./configs/tutorial/part1/bootscript.rcS
