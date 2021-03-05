#include "serial.h"
#include "fb.h"
#include "gdt.h"


void write(char *data, char outType){
  if(outType == 'F'){
    fb_write(data, sizeof(data)+2);
  }else if(outType == 'S'){
    serial_config();
    serial_write(data);
  }
}

void kernel_main(void){
  gdt_install();
  char *word = "HELLO";
  write(word, 'F');
  write(word, 'S');

}
