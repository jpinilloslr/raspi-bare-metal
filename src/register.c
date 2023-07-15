#include "register.h"

unsigned int reg_get32(unsigned long address)
{
    return *(unsigned int *)address;
}

void reg_put32(unsigned long address, unsigned int reg)
{
    *(unsigned int *)address = reg;
}