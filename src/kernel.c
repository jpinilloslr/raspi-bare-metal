#include "printf.h"
#include "uart.h"

void print_memu()
{
    printf("1\tOption1\r\n");
    printf("2\tOption2\r\n");
    printf("3\tOption3\r\n");
    printf("\r\n");
}

void option1()
{
    printf("Executed option1\r\n");
    printf("\r\n");
}

void option2()
{
    printf("Executed option2\r\n");
    printf("\r\n");
}

void option3()
{
    printf("Executed option3\r\n");
    printf("\r\n");
}

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
            option1();
        if (o == '2')
            option2();
        if (o == '3')
            option3();
    }
}
