# Understanding the Basics of ARM CPU 🧠

This section provides a fundamental understanding of how an **ARM Cortex-M CPU** operates at a low level. It serves as a foundation before diving into the project.

---

## ⚙️ What is an ARM CPU?

The **ARM CPU (Advanced RISC Machine)** is based on the **Reduced Instruction Set Computing (RISC)** architecture. It is designed for high efficiency, low power consumption, and compact instruction execution — making it ideal for **microcontrollers, IoT, and embedded systems**.

ARM cores such as the **Cortex-M series** are tailored for deterministic real-time control applications. The **Cortex-M4** used in this project supports both **integer** and **floating-point** operations.

---

## 🧩 Key Features of ARM Cortex-M

* **Harvard architecture** — Separate instruction and data buses for faster throughput.
* **Pipeline architecture** — Enables simultaneous instruction fetch, decode, and execution.
* **Thumb instruction set** — Compact 16/32-bit instruction format to reduce code size.
* **Nested Vectored Interrupt Controller (NVIC)** — Hardware support for prioritized interrupt handling.
* **Memory-mapped registers** — Direct access to peripherals using specific address ranges.
* **Low power modes** — Support for sleep and deep sleep for energy-efficient operation.

---



---

This document complements the main project by helping you understand **how ARM CPUs boot, manage memory, and execute code at the bare-metal level**.
