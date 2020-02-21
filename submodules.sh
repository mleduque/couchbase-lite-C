#!/bin/sh
git submodule deinit --all --force
rm -rf .git/modules
git submodule init
git submodule update --recursive --init