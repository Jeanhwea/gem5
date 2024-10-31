#!/usr/bin/env bash

python3 `which scons` build/X86/gem5.opt -j$(nproc)
