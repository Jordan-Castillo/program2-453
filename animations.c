#include "os.h"
#include "globals.h"
#include "synchro.h"
#include <avr/interrupt.h>

volatile int global;
extern mutex_t *printLock;
int main(void) {
   global = 0;
   int blinkId = 20;
   int topId = 1;
   int bottomId = 1;
   int stayId = 1;
   os_init();
   create_thread("anim", (uint16_t) just_animations, &blinkId, 200);
   os_start();
   sei();
   while(1){

   }
   return 0;
}
