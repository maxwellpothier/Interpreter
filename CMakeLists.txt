cmake_minimum_required(VERSION 3.17)
project(lab3-interpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(sandbox main.cpp Parser.cpp Parser.h DatalogProgram.cpp DatalogProgram.h Parameter.h Predicate.h Rule.h Scanner.cpp Scanner.h Token.cpp Token.h Scheme.h Interpreter.cpp Interpreter.h Database.h Relation.cpp Relation.h Tuple.h Header.h)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})