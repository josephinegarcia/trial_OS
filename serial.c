#include "io.h"
#include "serial.h"

/** serial_configure_baud_rate:
*  Sets the speed of the data being sent. The default speed of a serial
*  port is 115200 bits/s. The argument is a divisor of that number, hence
*  the resulting speed becomes (115200 / divisor) bits/s.
*
*  @param com      The COM port to configure
*  @param divisor  The divisor
*/
void serial_configure_baud_rate(unsigned short com, unsigned short divisor){
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com){
  /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
  * Content: | d | b | prty  | s | dl  |
  * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
  */
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffer(unsigned short com){
  /* Bit:     | 7 6 | 5  | 4 |  3  |  2  | 1   | 0 |
  * Content: | lvl | bs | r | dma | clt | clr | e |
  * Value:  | 1 1 |  0 | 0 |  0  |  1  |  1  | 1 | = 0xC7
  */
  outb(SERIAL_LINE_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com){
  /* Bit:     | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
  * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
  * Value:   | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | = 0x03
  */
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/** serial_is_transmit_fifo_empty:
*  Checks whether the transmit FIFO queue is empty or not for the given COM
*  port.
*
*  @param  com The COM port
*  @return 0 if the transmit FIFO queue is not empty
*          1 if the transmit FIFO queue is empty
*/
int serial_is_transmit_fifo_empty(unsigned int com){
  /* 0x20 = 0010 0000 */
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_config(){
  serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
  serial_configure_line(SERIAL_COM1_BASE);
  serial_configure_buffer(SERIAL_COM1_BASE);
  serial_configure_modem(SERIAL_COM1_BASE);
}

int serial_write_one(char data){
  while(serial_is_transmit_fifo_empty(SERIAL_COM1_BASE) == 0);
  outb(SERIAL_COM1_BASE, data);
  return 0;
}

int serial_write(char *data){
  for(unsigned int i = 0; data[i] != '\0'; i++){
    serial_write_one(data[i]);
  }
  return 0;
}
