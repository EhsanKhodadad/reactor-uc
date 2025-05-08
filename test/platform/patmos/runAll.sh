#!/bin/bash

# Make test
make all
pasim ./build/*.elf
