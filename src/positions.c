/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 * 
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE for details for
 * more details about how you can use it, you have freedom
 * to distribute and use this file in your project. However,
 * you will have to state changes you made and include the
 * orginal author of this file.
 * 
 * positions.h
 * This file keeps track of the position of where the program
 * is. The positional information provided will be used by
 * other files.
*/
#pragma once
struct Position {
    long int index, line, col;
};
static Position position;

Position clone() {
    Position clone;
    clone.index = position.index;
    clone.line = position.line;
    clone.col = position.col;
    return clone;
}

Position clone(Position existingPosition) {
    Position clone;
    clone.index = existingPosition.index;
    clone.line = existingPosition.line;
    clone.col = existingPosition.col;
    return clone;
}

void init_pos() {
    position.line = 1;
    position.index = -1;
    position.col = 0;
}

void forward(char current) {
    position.index += 1;
    position.col += 1;
    if (current == '\n') {
        position.line += 1;
        position.col = 0;
    }
}

void backward(char current) {
    position.index -= 1;
    position.col -= 1;
    if (current == '\n') {
        position.line -= 1;
    }
}
