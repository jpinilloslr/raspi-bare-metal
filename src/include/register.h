#ifndef REGISTER_H
#define REGISTER_H

unsigned int reg_get32(unsigned long address);
void reg_put32(unsigned long address, unsigned int value);

#endif
