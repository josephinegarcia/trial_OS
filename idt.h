#include "system.h"
#ifndef INCLUDE_IDT_H
#define INCLUDE_IDT_H


//Define the IDT entry
struct idt_entry {
  unsigned short base_lo;
  unsigned short selector;      //Our kernel segment goes here
  unsigned char zero;           //This is always 0
  unsigned char flags;
  unsigned short base_hi;
}__attribute__((packed));

struct idt_ptr {
  unsigned short limit;
  unsigned int base;
}__attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

//Exists in idt.s. Used to load the IDT
extern void idt_load();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
  idt[num].base_lo = (base & 0xFFFF);
  idt[num].selector = sel;
  idt[num].zero = 0;
  idt[num].flags = flags;
  idt[num].base_hi = ((base >> 16) & 0xFFFF);
}

void idt_install(){
  //Sets the special IDT pointer up, just like in gdt.h
  idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
  idtp.base = (unsigned int)&idt;

  //Clears out the entire IDT, initializing it to zero
  memset((unsigned char*)&idt, 0, sizeof(struct idt_entry) * 256);

  //Add new ISRs to IDT using idt_set_gate

  //Points the processor's internal register to the new IDT
  idt_load();
}

#endif
