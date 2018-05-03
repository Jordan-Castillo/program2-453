#include "os.h"
#include "globals.h"
#include <avr/interrupt.h>

volatile int global;

int main(void) {
   global = 0;
   int blinkId = 20;
   int stayId = 1;
   os_init();
   create_thread("blink", (uint16_t) blink, &blinkId, 200);
   create_thread("stay", (uint16_t) stayHere, &stayId, 200);
   os_start();
   return 0;
}
