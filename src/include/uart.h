#ifndef UART_H
#define UART_H

#include "timer.h"
#include "register.h"
#include "peripherals.h"

#define BAUD_RATE 115200
#define SYSTEM_CLOCK 250 * 1000000
#define BAUD_REG SYSTEM_CLOCK / (8 * BAUD_RATE) - 1

#define AUX_MU_LSR_DATA_READY (1 << 0)
#define AUX_MU_LSR_TX_EMPTY (1 << 5)

void uart_init();
char uart_read();
void uart_write(char c);
void uart_putc(void *p, char c);

#endif
