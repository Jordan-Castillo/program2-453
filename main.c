#include "os.h"
#include "globals.h"
#include "synchro.h"
#include <avr/interrupt.h>

volatile int global;

int main(void) {
   global = 0;
   int blinkId = 20;
   int topId = 1;
   int bottomId = 1;
   int stayId = 1;
   os_init();

   create_thread("blink", (uint16_t) blink, &blinkId, 200);
   //create_thread("stay", (uint16_t) stayHere, &stayId, 200);
   // create_thread("stats", (uint16_t) display_stats, &topId, 200);
   // create_thread("nada", (uint16_t) nada, &bottomId, 200);
   // create_thread("nada", (uint16_t) nada, &bottomId, 200);
   // create_thread("nada", (uint16_t) nada, &bottomId, 200);
   //create_thread("producer", (uint16_t) producer, &bottomId, 200);
   create_thread("consumer", (uint16_t) consumer, &bottomId, 200);
   os_start();
   sei();
   while(1){

   }
   return 0;
}
