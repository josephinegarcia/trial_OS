#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H

struct gdt_entry {
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity;
  unsigned char base_high;
}__attribute__((packed));

struct gdt_ptr {
  unsigned short limit;
  unsigned int base;
}__attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern void gdt_flush();

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran){
  //Setup descriptor base address
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  //Setup descripto limits
  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F);

  //Setup granularity and access flags
  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

void gdt_install(){
  //Setup the GDT pointer and the limits
  gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
  gp.base = (unsigned int)&gdt;

  //NULL descriptor
  gdt_set_gate(0, 0, 0, 0, 0);

  //Code segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  //Data segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  //Flush out old GDT and install new changes
  gdt_flush(gp);

}

#endif
