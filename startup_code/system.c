
#include <stdint.h>


void FPU_enalble(void)
{
    // uint32_t primask = __get_PRIMASK();
    // __disable_irq();
    // SCB->CPACR |= (((uint32_t)0xFU) << 20);
    // __DSB();
    // __ISB();

    // if (primask == 0U)
    // {
    //     __enable_irq();
    // }
}
void SystemInit(void)
{
    // Example: Enable FPU or set clock registers if needed
    // For now, do nothing. You can expand based on the MCU

    //Accorinding to the startupfile in the SAMe54p20A datasheet
    //FPU Enabled
    //CMCC enabled
    //clock configuration is not done here
    //vector table offset 

    //FPU enable 
    FPU_enalble();


}
