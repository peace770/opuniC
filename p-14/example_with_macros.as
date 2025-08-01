.entry MAIN
.extern EXT_LABEL

mcro DEC_AND_PRINT
    sub     r2, #1
    prn     r2
mcroend

mcro DOUBLE_AND_JUMP
    add     r2, r2
    jmp     MAIN
mcroend

DATA1:  .data   5, -3, 100
STR1:   .string "Hello, Macro!"

MAIN:   mov     r3, DATA1
        add     r2, r3
        cmp     r2, #10
        bne     LOOP
        prn     r2
        jsr     EXT_LABEL
        stop

LOOP:   cmp     r2, #10
        DEC_AND_PRINT
        DOUBLE_AND_JUMP
