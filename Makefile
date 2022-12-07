# Author: turrnut
# Copyrighted © turrnut under the Apache 2.0 license
#
# We hoped that you will use this piece of open source
# software fairly. read the LICENSE in the project for
# more details about how you can use it, you have freedom
# to distribute and use this file in your project. However,
# you will have to state changes you made and include the
# orginal author of this file.
#
# Makefile
# Build an executable on a Linux Machine
# Require to have Clang installed

.PHONY: build
build:
	clang++ -g -O3 toy.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o toy.out
	./toy.out $1
