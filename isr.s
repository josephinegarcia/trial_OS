;Interrupt Service Routines (ISRs)
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; 0: Divide by Zero Exception
isr0:
    cli
    push  byte 0                     ;A normal ISR stub that pop a dummy error code
    push  byte 0                     ;to keep a uniform stack
    jmp   common_isr_handler

; 1: Debug Exception
isr1:
    cli
    push  byte 0
    push  byte 1
    jmp   common_isr_handler

; 2: Non Maskable Interrupt Exception
isr2:
    cli
    push  byte 0
    push  byte 2
    jmp   common_isr_handler

; 3: Breakpoint Exception
isr3:
    cli
    push  byte 0
    push  byte 3
    jmp   common_isr_handler

; 4: Into Detected Overflow Exception
isr4:
    cli
    push  byte 0
    push  byte 4
    jmp   common_isr_handler

; 5: Out of Bounds Exception
isr5:
    cli
    push  byte 0
    push  byte 5
    jmp   common_isr_handler

; 6: Invalid Opcode Exception
isr6:
    cli
    push  byte 0
    push  byte 6
    jmp   common_isr_handler

; 7: No Coprocessor Segment Overrun
isr7:
    cli
    push  byte 0
    push  byte 7
    jmp   common_isr_handler

; 8: Double Fault Exception
isr8:
    cli
    push  byte 8                        ;Don't need to push a value on stack since it already pushes one
    jmp   common_isr_handler

; 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push  byte 0
    push  byte 9
    jmp   common_isr_handler

; 10: Bad TSS Exception
isr10:
    cli
    push  byte 10
    jmp   common_isr_handler

; 11: Segment Fault Exception
isr11:
    cli
    push  byte 11
    jmp   common_isr_handler

; 12: Stack Fault Exception
isr12:
    cli
    push  byte 12
    jmp   common_isr_handler

; 13: General Protection Fault Exception
isr13:
    cli
    push  byte 13
    jmp   common_isr_handler

; 14: Page Fault Exception
isr14:
    cli
    push  byte 14
    jmp   common_isr_handler

; 15: Unknown Interrupt Exception
isr15:
    cli
    push  byte 0
    push  byte 15
    jmp   common_isr_handler

; 16: Coprocessor Fault Exception
isr16:
    cli
    push  byte 0
    push  byte 16
    jmp   common_isr_handler

; 17: Alignment Check Exception (486+)
isr17:
    cli
    push  byte 0
    push  byte 17
    jmp   common_isr_handler

; 18: Machine Check Exception (Pentinum/586+)
isr18:
    cli
    push  byte 0
    push  byte 18
    jmp   common_isr_handler

; 19: Reserved Exception
isr19:
    cli
    push  byte 0
    push  byte 19
    jmp   common_isr_handler

; 20: Reserved Exception
isr20:
    cli
    push  byte 0
    push  byte 20
    jmp   common_isr_handler

; 21: Reserved Exception
isr21:
    cli
    push  byte 0
    push  byte 21
    jmp   common_isr_handler

; 22: Reserved Exception
isr22:
    cli
    push  byte 0
    push  byte 22
    jmp   common_isr_handler

; 23: Reserved Exception
isr23:
    cli
    push  byte 0
    push  byte 23
    jmp   common_isr_handler

; 24: Reserved Exception
isr24:
    cli
    push  byte 0
    push  byte 24
    jmp   common_isr_handler

; 25: Reserved Exception
isr25:
    cli
    push  byte 0
    push  byte 25
    jmp   common_isr_handler

; 26: Reserved Exception
isr26:
    cli
    push  byte 0
    push  byte 26
    jmp   common_isr_handler

; 27: Reserved Exception
isr27:
    cli
    push  byte 0
    push  byte 27
    jmp   common_isr_handler

; 28: Reserved Exception
isr28:
    cli
    push  byte 0
    push  byte 28
    jmp   common_isr_handler

; 29: Reserved Exception
isr29:
    cli
    push  byte 0
    push  byte 29
    jmp   common_isr_handler

; 30: Reserved Exception
isr30:
    cli
    push  byte 0
    push  byte 30
    jmp   common_isr_handler

;31: Reserved Exception
isr31:
    cli
    push  byte 0
    push  byte 31
    jmp   common_isr_handler

extern fault_handler

common_isr_handler:
    pusha
    push  ds
    push  es
    push  fs
    push  gs
    mov   ax, 0x10      ; Load Kernel Data Segment descriptor
    mov   ds, ax
    mov   es, ax
    mov   fs, ax
    mov   gs, ax
    mov   eax, esp      ; Push onto the Stack
    push  eax
    mov   eax, fault_handler
    call  eax           ; A special call, preserves the eip register
    pop   eax
    pop   gs
    pop   fs
    pop   es
    pop   ds
    popa
    add   esp, 8        ; Cleans up the pushed error code and pushed ISR number
    iret                ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
