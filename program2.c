#include "os.h"
#include "globals.h"
#include "synchro.h"
#include <avr/interrupt.h>

volatile int global;

int main(void) {
   global = 0;
   int blinkId = 20;
   int stayId = 1;
   os_init();
   create_thread("printtt", (uint16_t) printtt, &blinkId, 200);
   create_thread("nothing", (uint16_t) nothing, &stayId, 200);
   os_start();
   sei();
   while(1){

   }

   return 0;
}
