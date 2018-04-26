#include "globals.h"
#include "os.h"
#include <avr/interrupt.h>

volatile int global;

int main(void) {
   serial_init();
   global = 0;
   set_color(RED);
   set_cursor(2, 0);
   uint16_t rate = 500;

   print_string("Jordan Castillo");
   blink(&rate);



   return 0;
}
