
#include <stdint.h>

#define CMCC_BASE_ADDR      (0x41006000U)

#define CMCC_TYPE_OFFSET    (0x00U)
#define CMCC_CFG_OFFSET     (0x04U)
#define CMCC_CTRL_OFFSET    (0x08U)
#define CMCC_SR_OFFSET      (0x0CU)

#define CMCC_CFG_CSIZESW_Pos  4U
#define CMCC_CFG_CSIZESW_Msk  (0x7U << CMCC_CFG_CSIZESW_Pos)
#define CMCC_CFG_DCDIS_Msk    (1U << 0)

#define CMCC_CTRL_CEN_Msk     (1U << 0)
#define CMCC_SR_CSTS_Msk      (1U << 0)

#define SCB_VTOR_ADDR          (*(volatile uint32_t *)0xE000ED08)  // VTOR address
#define SCB_VTOR_TBLOFF_Pos    7U
#define SCB_VTOR_TBLOFF_Msk    (0x1FFFFFFUL << SCB_VTOR_TBLOFF_Pos)

// Linker symbol pointing to the start of vector table
extern uint32_t __svectors;

void FPU_enalble(void)
{
    
    __asm volatile (
        // Save PRIMASK into R2
        "MRS     R2, PRIMASK       \n"  // Save interrupt state

        // Disable interrupts
        "CPSID   i                 \n"

        // Load address of SCB->CPACR (0xE000ED88)
        "LDR.W   R0, =0xE000ED88   \n"

        // Read current CPACR value
        "LDR     R1, [R0]          \n"

        // Set bits 20–23 (CP10 and CP11 full access)
        "ORR     R1, R1, #(0xF << 20) \n"

        // Write back modified CPACR
        "STR     R1, [R0]          \n"

        // Data and Instruction barriers
        "DSB                       \n"
        "ISB                       \n"

        // Re-enable interrupts if previously enabled
        "CMP     R2, #0            \n"
        "BEQ     1f                \n"  // If PRIMASK == 0, enable IRQs
        "B       2f                \n"  // Else skip

        "1:                        \n"
        "CPSIE   i                 \n"

        "2:                        \n"
        :::"r0", "r1", "r2", "memory"
    );

}

void CMCC_enable(void)
{   
    volatile uint32_t* CMCC_CTRL = (uint32_t*)(CMCC_BASE_ADDR + CMCC_CTRL_OFFSET);
    volatile uint32_t* CMCC_SR   = (uint32_t*)(CMCC_BASE_ADDR + CMCC_SR_OFFSET);
    volatile uint32_t* CMCC_CFG  = (uint32_t*)(CMCC_BASE_ADDR + CMCC_CFG_OFFSET);

    // Disable cache
    *CMCC_CTRL &= ~CMCC_CTRL_CEN_Msk;

    // Wait until cache controller is idle
    while ((*CMCC_SR & CMCC_SR_CSTS_Msk) == CMCC_SR_CSTS_Msk)
    {
        // Wait
    }

    // Configure cache: Set CSIZESW = 2 (e.g., 4KB), and disable data cache if needed
    *CMCC_CFG = (2U << CMCC_CFG_CSIZESW_Pos) | CMCC_CFG_DCDIS_Msk;

    // Re-enable cache
    *CMCC_CTRL = CMCC_CTRL_CEN_Msk;

}

void vector_table_offset_set(void)
{   
    //to setup vector table base address
    SCB_VTOR_ADDR = ((uint32_t)&__svectors & SCB_VTOR_TBLOFF_Msk);
    // vector tabel is now set to 0x00000000
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

    //CMCC enable
    CMCC_enable();

    //Vector table offset
    vector_table_offset_set();


}
