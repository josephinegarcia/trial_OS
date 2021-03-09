#include "system.h"
#include "serial.h"
#include "fb.h"

/*Copies 'count' bytes of data from 'src' to 'dest'*/
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count){
  for(int i = 0; i < count; i++){
    dest[i] = src[i];
  }
  return dest;
}

/*Sets 'count' bytes in 'dest' to 'val'*/
unsigned char *memset(unsigned char *dest, unsigned char val, int count){
  for(int i = 0; i < count; i++){
    dest[i] = val;
  }
  return dest;
}

/*Same as above but 'val' and 'dest' is 16-bit*/
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count){
  for(int i = 0; i < count; i++){
    dest[i] = val;
  }
  return dest;
}

/*Returns length of string*/
int strlen(const char *str){
  int len = 0;
  while (str[len] != '\0'){
    len++;
  }
  return len;
}

void write(const char *data, char outType){
  if(outType == 'F'){
    //fb_write(data, sizeof(data)+2);
    fb_write(data, strlen(data)+1);
  }else if(outType == 'S'){
    serial_config();
    serial_write(data);
  }
}
