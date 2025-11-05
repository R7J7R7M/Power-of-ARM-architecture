# Power-of-ARM-Architecture 🚀

## 🧠 Project Summary

This project is a **bare-metal implementation** of the ARM Cortex-M startup process for the **ATSAME54P20A microcontroller**, built from scratch without using any vendor-provided frameworks like ASF or Harmony.

It demonstrates:

* ✅ Writing your own **startup code** including the `Reset_Handler` and vector table
* ✅ Manually **initializing `.data` and `.bss`** sections using linker-defined symbols
* ✅ Custom **linker script** to place sections like `.text`, `.data`, `.bss`, and the vector table
* ✅ Manual **SystemInit** with optional **FPU activation**
* ✅ Building using **arm-none-eabi-gcc** with a **custom Makefile**
* ✅ Flashing to the actual SAME54P20A hardware using **OpenOCD + CMSIS-DAP**

---

## ⚙️ Requirements

Before running this project, ensure the following tools and environment are set up:

* 🧩 **ARM GCC (arm-none-eabi) compiler** — Required to build and link the project.
* 💻 **VS Code (Visual Studio Code)** — Recommended code editor for development.
* ⚡ **PowerShell script** — Used to automate build and flash commands.
* 🔌 **OpenOCD + CMSIS-DAP debugger** — Required to upload and debug the program on hardware.

---

## 🧰 System Setup & Commands

Follow these steps to build, link, and flash the firmware to your SAME54P20A board:

### 🏗️ Build the Source Files

Use the following commands to compile each source file:

```bash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -c startup.c -o startup.o
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -c system.c -o system.o
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -c main.c -o main.o
```

### 🔗 Link the Object Files

Once compiled, link all object files with the linker script:

```bash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -T linker.ld -nostartfiles \
  ./startup.o ./system.o ./main.o -o firmware.elf
```

### ⚡ Flash the Firmware

To program the device using OpenOCD and CMSIS-DAP interface:

```bash
openocd -f interface/cmsis-dap.cfg -f target/atsame5x.cfg -c "program firmware.elf verify reset exit"
```

---

## 📚 Notes

This project is ideal for understanding the **ARM startup sequence**, memory initialization, and low-level boot process without relying on any vendor frameworks. It provides a hands-on understanding of how a Cortex-M device starts up — from vector table mapping to stack setup and transition to `main()`.

By experimenting with this code, you’ll gain a clear picture of what happens **before main()** executes, how the system initializes essential memory regions, and how bare-metal firmware directly interacts with ARM architecture features like **stack pointers**, **exception vectors**, and **floating-point configuration**.
