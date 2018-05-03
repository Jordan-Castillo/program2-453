#include "globals.h"
#include "os.h"
#include "synchro.h"

extern system_t *memBegin;
extern volatile int global;
extern int numThreads;
/*
   put the thread to sleep for the specified number of ticks...
   count global timer maybe?
*/
void thread_sleep(uint16_t ticks){

}
void blink_V2(void){

}
/*

*/
void consumer(void){

   return;
}
/*

*/
void producer(void){

   return;
}
/*

*/
void display_bounded_buffer(void){

   return;
}
/*

*/
void display_stats(void){
   //start at row 1, for reasons I dont want to explain
   uint8_t row = 4, i = 0;

   while(1){
      if(global < 10){  //garbage prints immediately, this cleans that up
         clear_screen();
      }
      row = 4;
      //clear_screen();
      set_cursor(0, 0);
      set_color(YELLOW);
      print_string("Timer: ");
      print_int32((global/100));
      print_string("                             ");
      set_cursor(2, 0);
      print_string("Number of Threads: ");
      print_int(numThreads);
      for(int i = 0; i < numThreads; i++){ //print stats of each thread
         set_color(GREEN);
         set_cursor(row++, 0);
         print_string("Thread Id: ");
         print_int(memBegin->threads[i].id);
         set_cursor(row++, 0);
         print_string("Thread name: ");
         print_string(memBegin->threads[i].tName);
         set_cursor(row++, 0);
         print_string("Thread PC: ");
         print_hex(memBegin->threads[i].PC);
         set_cursor(row++, 0);
         print_string("Stack Usage: ");
         print_int((uint16_t)memBegin->threads[i].stackEnd -
            (uint16_t)memBegin->threads[i].stackPointer);
         print_string(" bytes   ");
         set_cursor(row++, 0);
         print_string("Stack Size: ");
         print_int(memBegin->threads[i].stackSize);
         print_string(" bytes   ");
         set_cursor(row++, 0);
         print_string("Current top of stack: ");
         print_hex((uint16_t)memBegin->threads[i].stackPointer);
         set_cursor(row++, 0);
         print_string("Stack base: ");
         print_hex((uint16_t)memBegin->threads[i].stackBase);
         set_cursor(row++, 0);
         print_string("Stack end: ");
         print_hex((uint16_t)memBegin->threads[i].stackEnd);
         row++;
      }
   }
}
