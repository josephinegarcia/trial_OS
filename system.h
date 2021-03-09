#ifndef INCLUDE_SYSTEM_H
#define INCLUDE_SYSTEM_H

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
unsigned char *memset(unsigned char *dest, unsigned char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
int strlen(const char *str);
void write(const char *data, char outType);

#endif
