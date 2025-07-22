.entry MAIN
.extern EXT_LABEL

1DATA:  .data   5 -3, 100
STR1:   .string "Hello

MAIN:   mvo     r3, 1DATA
        add     r2, r3, r4
        cmp     r2 #10
        bne     LOOP
        prn     r2
        jsr     EXT_LABEL
        stop

LOOP:   DEC_AND_PRINT
        DOUBLE_AND_JUMP MAIN
