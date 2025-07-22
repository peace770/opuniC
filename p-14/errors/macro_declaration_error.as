.entry MAIN

macro DEC_AND_PRINT extra_token
    sub r2, #1
    prn r2
endmacro

macro DOUBLE_AND_JUMP target extra
    add r2, r2
    jmp target
endmacro

MAIN: DEC_AND_PRINT
      DOUBLE_AND_JUMP MAIN
      stop
