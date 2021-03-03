#include "io.h"

/* The I/O ports*/
#define FB_COMMAND_PORT     0x3D4
#define FB_DATA_PORT        0x3D5

/* The I/O port commands*/
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

enum FB_COLORS {
  FB_BLACK = 0,
  FB_BLUE = 1,
  FB_GREEN = 2,
  FB_CYAN = 3,
  FB_RED = 4,
  FB_MAGENTA = 5,
  FB_BROWN = 6,
  FB_LIGHT_GREY = 7,
  FB_DARK_GREY = 8,
  FB_LIGHT_BLUE = 9,
  FB_LIGHT_GREEN = 10,
  FB_LIGHT_CYAN = 11,
  FB_LIGHT_RED = 12,
  FB_LIGHT_MAGENTA = 13,
  FB_LIGHT_BROWN = 14,
  FB_WHITE = 15,
};

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
}

void fb_move_cursor(unsigned short pos){
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

int fb_write(char *buff, unsigned int len){
  for(unsigned int i = 0; i < len; i++){
    fb_move_cursor(i);
    fb_write_cell(i*2, buff[i], FB_BLACK, FB_WHITE);
  }
  return 0;
}
