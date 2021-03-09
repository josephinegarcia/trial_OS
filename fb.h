#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

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

int fb_write(const char *buff, unsigned int len);
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_move_cursor(unsigned short pos);
int fb_write(const char *buff, unsigned int len);
void write(const char *data, char outType);

#endif
