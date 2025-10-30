#include <stdint.h>

extern int main(void);
extern void SystemInit(void);

/* Linker-defined symbols */
extern uint32_t _estack;
extern uint32_t _sdata, _edata, _sidata;
extern uint32_t _sbss, _ebss;

/* Default weak handlers */
void Default_Handler(void) { while (1); }
void Reset_Handler(void);

/* Vector table */
__attribute__((section(".isr_vector")))
const void *vector_table[] = {
    &_estack,           // Initial Stack Pointer
    Reset_Handler,      // Reset Handler
    Default_Handler,    // NMI
    Default_Handler,    // HardFault
    // Add more if needed
};

void Reset_Handler(void)
{
    // Call system init (clock, FPU, etc.)
    SystemInit();

    // Copy .data section from flash to RAM
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    // Zero initialize .bss section
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    // Call main
    main();

    // If main returns, loop forever
    while (1);
}
