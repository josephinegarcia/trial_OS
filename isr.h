#ifndef INCLUDE_ISR_H
#define INCLUDE_ISR_H

//Function prototypes for all exceptions handlers
extern unsigned long isr0;
extern unsigned long isr1;
extern unsigned long isr2;
extern unsigned long isr3;
extern unsigned long isr4;
extern unsigned long isr5;
extern unsigned long isr6;
extern unsigned long isr7;
extern unsigned long isr8;
extern unsigned long isr9;
extern unsigned long isr10;
extern unsigned long isr11;
extern unsigned long isr12;
extern unsigned long isr13;
extern unsigned long isr14;
extern unsigned long isr15;
extern unsigned long isr16;
extern unsigned long isr17;
extern unsigned long isr18;
extern unsigned long isr19;
extern unsigned long isr20;
extern unsigned long isr21;
extern unsigned long isr22;
extern unsigned long isr23;
extern unsigned long isr24;
extern unsigned long isr25;
extern unsigned long isr26;
extern unsigned long isr27;
extern unsigned long isr28;
extern unsigned long isr29;
extern unsigned long isr30;
extern unsigned long isr31;

void isrs_install(){
  idt_set_gate(0, (unsigned long)isr0, 0x08, 0x8E);
  idt_set_gate(1, (unsigned long)isr1, 0x08, 0x8E);
  idt_set_gate(2, (unsigned long)isr2, 0x08, 0x8E);
  idt_set_gate(3, (unsigned long)isr3, 0x08, 0x8E);
  idt_set_gate(4, (unsigned long)isr4, 0x08, 0x8E);
  idt_set_gate(5, (unsigned long)isr5, 0x08, 0x8E);
  idt_set_gate(6, (unsigned long)isr6, 0x08, 0x8E);
  idt_set_gate(7, (unsigned long)isr7, 0x08, 0x8E);
  idt_set_gate(8, (unsigned long)isr8, 0x08, 0x8E);
  idt_set_gate(9, (unsigned long)isr9, 0x08, 0x8E);
  idt_set_gate(10, (unsigned long)isr10, 0x08, 0x8E);
  idt_set_gate(11, (unsigned long)isr11, 0x08, 0x8E);
  idt_set_gate(12, (unsigned long)isr12, 0x08, 0x8E);
  idt_set_gate(13, (unsigned long)isr13, 0x08, 0x8E);
  idt_set_gate(14, (unsigned long)isr14, 0x08, 0x8E);
  idt_set_gate(15, (unsigned long)isr15, 0x08, 0x8E);
  idt_set_gate(16, (unsigned long)isr16, 0x08, 0x8E);
  idt_set_gate(17, (unsigned long)isr17, 0x08, 0x8E);
  idt_set_gate(18, (unsigned long)isr18, 0x08, 0x8E);
  idt_set_gate(19, (unsigned long)isr19, 0x08, 0x8E);
  idt_set_gate(20, (unsigned long)isr20, 0x08, 0x8E);
  idt_set_gate(21, (unsigned long)isr21, 0x08, 0x8E);
  idt_set_gate(22, (unsigned long)isr22, 0x08, 0x8E);
  idt_set_gate(23, (unsigned long)isr23, 0x08, 0x8E);
  idt_set_gate(24, (unsigned long)isr24, 0x08, 0x8E);
  idt_set_gate(25, (unsigned long)isr25, 0x08, 0x8E);
  idt_set_gate(26, (unsigned long)isr26, 0x08, 0x8E);
  idt_set_gate(27, (unsigned long)isr27, 0x08, 0x8E);
  idt_set_gate(28, (unsigned long)isr28, 0x08, 0x8E);
  idt_set_gate(29, (unsigned long)isr29, 0x08, 0x8E);
  idt_set_gate(30, (unsigned long)isr30, 0x08, 0x8E);
  idt_set_gate(31, (unsigned long)isr31, 0x08, 0x8E);
}

const char *exception_message[] = {
  "Division by Zero",
  "Debug",
  "Non Masked Interrupt",
  "Breakpoint",
  "Into Detected Overflow",
  "Out of Bounds",
  "Invalid Opcode",
  "No Coprocessor",
  "Double Fault",
  "Coprocessor Segment Overrun",
  "Bad TSS Exception",
  "Segment Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault",
  "Unknown Interrupt",
  "Coprocessor Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions"
};

struct regs {
  unsigned int gs, fs, es, ds; //pushed the segs last
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; //pushed by 'pusha'
  unsigned int int_no, err_code; //'push byte #' and encodes do This
  unsigned int eip, cs, eflags, useresp, ss; //pushed by the processor automatically
};

void fault_handler(struct regs *r){
  if(r->int_no < 32){
    write(exception_message[r->int_no], 'F');
    write("Exception. System Halted!\n", 'F');
    for(;;);
  }
}

#endif
