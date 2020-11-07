#include "Interpreter.h"

int main(int argc, char* argv[]) {
    Interpreter i;
    i.interpret(argv[1]);

    return 0;
}