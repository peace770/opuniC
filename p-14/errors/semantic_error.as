.entry NOT_DEFINED
.extern MAIN

DATA1:  .data   10, 20
STR1:   .string "Test"

MAIN:   mov     r3, DATA1
        add     r2, r3
        jsr     UNDEF_LABEL
        stop

MAIN:   prn     r2
