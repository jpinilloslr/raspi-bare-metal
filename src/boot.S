#include "boot.h"

.section ".text.boot"

.globl _start
_start:
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF   // Check processor
    cmp     x0, #0x0
    beq     boot            // Continue with processor 0
    b       proc_hang       // Hang other processors

proc_hang:
    b       proc_hang

boot:
    adr     x0, bss_begin
    adr     x1, bss_end
    sub     x1, x1, x0
    bl      memzero         // Init bss section
    mov     sp, #STACK0     // Initialize stack for proc 0
    bl      main            // Pass execution to C
    b       proc_hang

memzero:
    str     xzr, [x0], #8
    subs    x1, x1, #8
    b.gt    memzero
    ret
