#include "io.h"
#include "serial.c"

/* The I/O ports*/
#define FB_COMMAND_PORT     0x3D4
#define FB_DATA_PORT        0x3D5

/* The I/O port commands*/
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

#define FB_GREEN     2
#define FB_DARK_GREY 8
#define FB_BLACK 0

char *fb = (char*) 0x000B8000;

/** fb_write_cell:
*  Writes a character with the given foreground and background to position i
*  in the framebuffer.
*
*  @param i  The location in the framebuffer
*  @param c  The character
*  @param fg The foreground color
*  @param bg The background color
*/
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg){
  fb[i] = c;
  fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);

  //i++;
  //*fb++ = c;
  //*fb++ = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move_cursor(unsigned short pos){
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

int write(char *buff, unsigned int len){
  for(unsigned int i = 0; i < len; i++){
    fb_move_cursor(i);
    fb_write_cell(i*2, buff[i], FB_BLACK, FB_DARK_GREY);
  }
  return 0;
}

void kernel_main(void){
  //fb_write_cell(0, 'A', FB_GREEN, FB_DARK_GREY);
  //fb_move_cursor(50);
  char word[5] = {'H','E','L','L','O'};
  //write(word, sizeof(word)/sizeof(word[0])+1);
  serial_config();
  serial_write(word);

}
