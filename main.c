#include "os.h"
#include "globals.h"
#include <avr/interrupt.h>

volatile int global;

int main(void) {
   global = 0;
   int prevGlobal = global;

   os_init();

   while(1){
      if(prevGlobal < (global - 100)) { //only update screen if 1s past
         prevGlobal = global;
         set_cursor(0, 0);
         clear_screen();
         set_color(YELLOW);
         print_string("Timer: ");
         print_int32((global/100));

         set_color(WHITE); //
         set_cursor(4, 4); // testing my hex,color,cursor functions
         print_hex(25555);   //
      }
   }
   return 0;
}
