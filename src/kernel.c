#include "printf.h"
#include "uart.h"
#include "el.h"

static void _print_menu();
static void _check_el();
static void _check_lsr_reg();

void main()
{
    uart_init();
    init_printf(0, uart_putc);

    printf("Initialized UART from processor 0\r\n");
    _print_menu();

    while (1)
    {
        char o = uart_read();
        if (o == '1')
            _check_el();
        if (o == '2')
            _check_lsr_reg();
    }
}

static void _print_menu()
{
    printf("1:    Check current exception level\r\n");
    printf("2:    Check AUX_MU_LSR_REG\r\n");
    printf("\r\n");
}

static void _check_el()
{
    printf("Current exception level: %d\r\n", get_el());
    printf("\r\n");
}

static void _check_lsr_reg()
{
    unsigned int last_value = 1234;
    while (1)
    {
        unsigned int reg = reg_get32(AUX_MU_LSR_REG);
        if (last_value != reg)
        {
            printf("AUX_MU_LSR_REG changed: %d\r\n", reg);
            last_value = reg;
        }

        if (reg == AUX_MU_LSR_DATA_READY)
        {
            char c = uart_read();
            printf("Data ready, reading: %d\r\n", c);

            if (c == 'q')
            {
                printf("Exiting loop\r\n");
                break;
            }
        }
    }
}