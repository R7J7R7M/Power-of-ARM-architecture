# Power-of-ARM-Architecture 

## Project Summary

This project is a **bare-metal implementation** of the ARM Cortex-M startup process for the **ATSAME54P20A microcontroller**, built from scratch without using any vendor-provided frameworks like ASF or Harmony.

It demonstrates:

- ✅ Writing your own **startup code** including the `Reset_Handler` and vector table  
- ✅ Manually **initializing `.data` and `.bss`** sections using linker-defined symbols  
- ✅ Custom **linker script** to place sections like `.text`, `.data`, `.bss`, and the vector table  
- ✅ Manual **SystemInit** with optional **FPU activation**  
- ✅ Building using **arm-none-eabi-gcc** with a **custom Makefile**  
- ✅ Flashing to the actual SAME54P20A hardware using **OpenOCD + CMSIS-DAP**
