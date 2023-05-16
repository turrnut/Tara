source_files = src/toy.c src/compiler/compiler.c  src/data/data.c src/ir/ir.c src/memory/memory.c src/test/test.c

install-packages:
	sudo apt-get install gcc

build:
	gcc $(source_files) -o out/toy.o

