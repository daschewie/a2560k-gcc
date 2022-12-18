#include "asm.h"

    .global SYM (mcp_syscall)

    .text

SYM (mcp_syscall):
    linkw fp, IMM(0)
    moveml d1-d7, -(sp)
    movel fp@(8), d0
    movel fp@(12), d1
    movel fp@(16), d2
    movel fp@(20), d3
    movel fp@(24), d4
    trap IMM(15)
    moveml (sp)+, d1-d7
    unlk fp
    rts
