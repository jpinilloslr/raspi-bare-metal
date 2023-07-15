#include "uart.h"

void uart_init(void)
{
    unsigned int selector;

    selector = reg_get32(GPFSEL1);
    selector &= ~(7 << 12); // Clean GPIO 14 alt func
    selector |= 2 << 12;    // Set GPIO 14 alt func for TXD1
    selector &= ~(7 << 15); // Clean GPIO 15 alt func
    selector |= 2 << 15;    // Set GPIO 15 alt func for RXD1
    reg_put32(GPFSEL1, selector);

    reg_put32(GPPUD, 0); // Remove pull-up/down
    delay(150);
    reg_put32(GPPUDCLK0,
              (1 << 14) | (1 << 15)); // Set control signal for GPIO 14, 15
    delay(150);
    reg_put32(GPPUDCLK0, 0); // Reset constrol signal

    reg_put32(AUX_ENABLES, 1);            // Enable UART
    reg_put32(AUX_MU_CNTL_REG, 0);        // Disable Rx Tx
    reg_put32(AUX_MU_IER_REG, 0);         // Disable interrupts
    reg_put32(AUX_MU_LCR_REG, 3);         // Set 8 bit mode
    reg_put32(AUX_MU_MCR_REG, 0);         // Won't use RTS line
    reg_put32(AUX_MU_BAUD_REG, BAUD_REG); // Set baud rate
    reg_put32(AUX_MU_CNTL_REG, 3);        // Enable Rx Tx
}

char uart_read(void)
{
    while (!(reg_get32(AUX_MU_LSR_REG) & AUX_MU_LSR_DATA_READY))
        continue;

    return (reg_get32(AUX_MU_IO_REG) & 0xFF);
}

void uart_write(char c)
{
    while (!(reg_get32(AUX_MU_LSR_REG) & AUX_MU_LSR_TX_EMPTY))
        continue;

    reg_put32(AUX_MU_IO_REG, c);
}

void uart_putc(void *p, char c)
{
    uart_write(c);
}
