@echo off
mkdir bin || echo building...
gcc -o bin\tara.exe src\toy.c src\code\codegen.c src\code\lexer.c src\error\error.c src\ir\ir.c src\memory\memory.c src\runtime\runtime.c src\test\test.c src\types\types.c src\utils\files.c
bin\tara -h