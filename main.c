#include "os.h"
#include "globals.h"
#include <avr/interrupt.h>

volatile int global;

int main(void) {
   global = 0;
   os_init();
   
   return 0;
}
