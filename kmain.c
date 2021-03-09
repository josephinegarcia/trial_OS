#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "system.h"

void kernel_main(void){
  gdt_install();
  idt_install();
  isrs_install();
  const char *word = "HELLO";
  write(word, 'F');
  write(word, 'S');


}
