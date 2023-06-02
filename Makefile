# 
# Author: turrnut
# Copyrighted © turrnut under the Apache 2.0 license#
#
# We hoped that you will use this piece of open source
# software fairly. read the LICENSE for more details about
# how you can use it, you have freedom to distribute and
# use this code in your project. However, you will have to
# state changes you made and include the orginal author of
# this code.
#
# Makefile
#

source_files = src/toy.c src/code/codegen.c src/code/lexer.c src/error/error.c src/ir/ir.c src/memory/memory.c src/runtime/runtime.c src/test/test.c src/type/type.c src/utils/files.c
output_binary = bin/tara

install-packages:
	sudo apt-get install gcc

build:
	mkdir bin || echo
	gcc $(source_files) -o $(output_binary)
	./bin/tara -h

