#include <linux/of_fdt.h>
#include <asm/prom.h>

// from non-trivial-mips
#if IS_ENABLED(CONFIG_PHOENIX_ARTIX7)
#define EARLY_PRINTK_UART_BASE 0xbfd00000
#define PHOENIX_UART_OUTB(addr, byte) writeb((byte), (uint32_t *)(EARLY_PRINTK_UART_BASE + addr))
#endif

void prom_putchar(char c)
{
#if IS_ENABLED(CONFIG_PHOENIX_ARTIX7)
    while( (readl((uint32_t *)(EARLY_PRINTK_UART_BASE + 0x14)) & 0x40) == 0 );
    PHOENIX_UART_OUTB(0x00, c & 0xFF);
#endif
}

void __init prom_init(void)
{
#if IS_ENABLED(CONFIG_PHOENIX_ARTIX7)
    /** turn on the uart fifo register, reset all values,
     * set the interrupt threshold to 8 byte */
    //PHOENIX_UART_OUTB(0x08, 0x81);
    /** set uar lcr register DLABbit to 1
     * this will use 0x0, 0x1 as divisor latch */
    //PHOENIX_UART_OUTB(0x0c, 0x80);
    /** set the baud rate to 57600 */
    //PHOENIX_UART_OUTB(0x04, 0x00);
    //PHOENIX_UART_OUTB(0x00, 0x36);

    // 8 data bits, 1 stop bit, parity off; turn off DLAB latch
    //PHOENIX_UART_OUTB(0x0C, 0x03);

    // turn on rts and dts model control
    //PHOENIX_UART_OUTB(0x10, 0x0);
    // Enable rcv interrupts
    //PHOENIX_UART_OUTB(0x04, 0x01);
#endif
}

void __init prom_free_prom_memory(void)
{
}
