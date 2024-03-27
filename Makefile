# 
# Author: turrnut
# Copyrighted (c) turrnut under the MIT license
# ir.h
#

source_files = src/toy.c src/code/ir.c src/code/runtime.c src/debugging/debugging.c src/security/alloc.c src/types/types.c
output_binary = bin/tara

install-packages:
	sudo apt-get update
	sudo apt-get upgrade
	sudo apt-get install gcc

build:
	mkdir bin || echo
	gcc $(source_files) -o $(output_binary)
	./bin/tara

