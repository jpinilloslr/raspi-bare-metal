#include "printf.h"
#include "uart.h"

static void _print_memu();
static void _check_el();

void main()
{
    uart_init();
    init_printf(0, uart_putc);

    printf("Initialized UART from processor 0\r\n");
    print_memu();

    while (1)
    {
        char o = uart_read();
        if (o == '1')
            check_el();
    }
}

static void _print_memu()
{
    printf("1:    Check current exception level\r\n");
    printf("\r\n");
}

static void _check_el()
{
    printf("Current exception level: %d\r\n", get_el());
    printf("\r\n");
}
