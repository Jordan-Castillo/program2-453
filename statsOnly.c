#include "globals.h"
#include "os.h"
#include <avr/interrupt.h>

volatile int global;

int main(void) {
   serial_init();
   global = 0;
   stayHere();

   return 0;
}
