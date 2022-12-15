    .global mcp_syscall

    .text

mcp_syscall:
    linkw %fp,#0
    moveml %d1-%d7, -(%sp)
    movel %fp@(8), %d0
    movel %fp@(12), %d1
    movel %fp@(16), %d2
    movel %fp@(20), %d3
    movel %fp@(24), %d4
    trap #15
    moveml (%sp)+, %d1-%d7
    unlk %fp
    rts
