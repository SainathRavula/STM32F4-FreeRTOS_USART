

                .syntax unified
                .cpu cortex-m4
                .thumb

                .global g_pfnVectors
                .global Reset_Handler


                .section .isr_vector,"a",%progbits
                .type g_pfnVectors, %object
                .size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler


                .section .text.Reset_Handler,"ax",%progbits
                .weak   Reset_Handler
                .type   Reset_Handler, %function
Reset_Handler:
  b       _start

                .section .text.NMI_Handler,"ax",%progbits
                .weak   NMI_Handler
                .type   NMI_Handler, %function
NMI_Handler:
  b       .

                .section .text.HardFault_Handler,"ax",%progbits
                .weak   HardFault_Handler
                .type   HardFault_Handler, %function
HardFault_Handler:
  b       .

                .section .text.MemManage_Handler,"ax",%progbits
                .weak   MemManage_Handler
                .type   MemManage_Handler, %function
MemManage_Handler:
  b       .

                .section .text.BusFault_Handler,"ax",%progbits
                .weak   BusFault_Handler
                .type   BusFault_Handler, %function
BusFault_Handler:
  b       .

                .section .text.UsageFault_Handler,"ax",%progbits
                .weak   UsageFault_Handler
                .type   UsageFault_Handler, %function
UsageFault_Handler:
  b       .

                .section .text.SVC_Handler,"ax",%progbits
                .weak   SVC_Handler
                .type   SVC_Handler, %function
SVC_Handler:
  b       .

                .section .text.DebugMon_Handler,"ax",%progbits
                .weak   DebugMon_Handler
                .type   DebugMon_Handler, %function
DebugMon_Handler:
  b       .

                .section .text.PendSV_Handler,"ax",%progbits
                .weak   PendSV_Handler
                .type   PendSV_Handler, %function
PendSV_Handler:
  b       .

                .section .text.SysTick_Handler,"ax",%progbits
                .weak   SysTick_Handler
                .type   SysTick_Handler, %function
SysTick_Handler:
  b       .

                .section .ARM.attributes
                .align  2
                .word   0x00000000

