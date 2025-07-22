.entry MAIN

macro 123INVALID
    add r2, r3
endmacro

macro mov
    sub r1, r1
endmacro

DATA1: .data  1, 2, 3

MAIN:  123INVALID
       mov
       stop
