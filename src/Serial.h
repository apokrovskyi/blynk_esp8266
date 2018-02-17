/*
 * Serial.h
 *
 *  Created on: 13.07.2017
 *      Author: andrew
 */

#ifndef SERIAL_H_
#define SERIAL_H_

enum PrintMode {
  DEC, HEX
};

class SerialPort {

public:
  void begin(long baud) {
      uart_init(BIT_RATE_115200, BIT_RATE_115200);
      println();
  }

  void print(int arg, PrintMode p = DEC) {
      os_printf("%d", arg);
  }

  void print(uint32_t arg) {
      os_printf("%lu", arg);
  }

  void print(long arg) {
      os_printf("%l", arg);
  }

  void print(unsigned char arg) {
      os_printf("%d", arg);
  }

  void print(char arg) {
      os_printf("%c", arg);
  }

  void printf(const char* format, ...) {
    char buffer[128];
    va_list arglist;
    va_start(arglist, format);
    ets_vsnprintf(buffer, sizeof(buffer), format, arglist);
    va_end(arglist);

    print(buffer);
  }

  void print(const char* arg) {
      os_printf("%s", arg);
  }

  template <typename T>
  void println(T arg) {
      print(arg);
      println();
  }

  void println() {
      os_printf("\r\n");
  }
};

SerialPort Serial;

#endif /* SERIAL_H_ */
