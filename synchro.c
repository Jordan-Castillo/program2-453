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
   Just the function for the consumer animation.
   call it once to iterate the animation once
*/
void consumer_anim(void){
   uint8_t row = 2, col = 20;
   uint8_t setColor = CYAN, base = WHITE;
   int frame = 0;
   while(1){
      set_color(base);
      row = 2;
      col = 0;
      //if(global < 10)
      //   clear_screen();
      if(frame >= 0 && frame <= 10){
         set_cursor(row++, col);
         print_string("               ");
         set_cursor(row++, col);
         print_string("   #   ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string(" #####  ");
         set_cursor(row++, col);
         print_string("#######");
         set_cursor(row++, col);
         print_string(" #####  ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string("   #   ");
         frame++;
      }
      else if(frame > 10 && frame <= 20){
         set_cursor(row++, col);
         print_string("CONSUMING");
         set_cursor(row++, col);
         print_string("   #   ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string(" #####  ");
         set_cursor(row++, col);
         print_string("###");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("###");
         set_cursor(row++, col);
         print_string(" #####  ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string("   #   ");
         frame++;
      }
      else if(frame > 20 && frame <= 30){
         set_cursor(row++, col);
         print_string("               ");
         set_cursor(row++, col);
         print_string("   #   ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string(" ##");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("##  ");
         set_cursor(row++, col);
         print_string("##");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("#");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("##");
         set_cursor(row++, col);
         print_string(" ##");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("##  ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string("   #   ");
         frame++;
      }
      else if(frame > 30 && frame <= 40){
         set_cursor(row++, col);
         print_string("CONSUMING");
         set_cursor(row++, col);
         print_string("   #   ");
         set_cursor(row++, col);
         print_string("  #");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("#  ");
         set_cursor(row++, col);
         print_string(" #");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("#");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("#  ");
         set_cursor(row++, col);
         print_string("#");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("###");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("#");
         set_cursor(row++, col);
         print_string(" #");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("#");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("#  ");
         set_cursor(row++, col);
         print_string("  #");
         set_color(setColor);
         print_string("0");
         set_color(base);
         print_string("#  ");
         set_cursor(row++, col);
         print_string("   #   ");
         frame++;
      }
      else if(frame > 40 && frame <= 50){
         set_cursor(row++, col);
         print_string("                ");
         set_cursor(row++, col);
         set_color(setColor);
         print_string("   0   ");
         set_cursor(row++, col);
         set_color(setColor);
         print_string("  0");
         set_color(base);
         print_string("#");
         set_color(setColor);
         print_string("0  ");
         set_cursor(row++, col);
         print_string(" 0");
         set_color(base);
         print_string("###");
         set_color(setColor);
         print_string("0  ");
         set_cursor(row++, col);
         print_string("0");
         set_color(base);
         print_string("#####");
         set_color(setColor);
         print_string("0");
         set_cursor(row++, col);
         print_string(" 0");
         set_color(base);
         print_string("###");
         set_color(setColor);
         print_string("0  ");
         set_cursor(row++, col);
         print_string("  0");
         set_color(base);
         print_string("#");
         set_color(setColor);
         print_string("0  ");
         set_cursor(row++, col);
         print_string("   0   ");
         frame++;
      }
      else if(frame == 51){
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         frame++;
      }
      else
         return;
   }
}
/*

*/
void consumer(void){
   int i = 5;
   for (i = 0; i < 5; i++)
      consumer_anim();
   return;
}


/*

*/
void producer_anim(void){
   uint8_t row = 2, col = 0;
   int frame = 0;
   while(1){
      row = 2;
      col = 0;
   //this might not be necessary in the final product, but just incase saved here
   //   if(global < 10)
   //      clear_screen();
      if(frame >= 0 && frame <= 10){
         set_cursor(row++, col);
         print_string("   #   ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string(" #####  ");
         set_cursor(row++, col);
         print_string("#######");
         set_cursor(row++, col);
         print_string(" #####  ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string("   #   ");
         frame++;
      }
      else if(frame > 10 && frame <= 20){
         set_cursor(row++, col);
         print_string("   #   ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string(" #####  ");
         set_cursor(row++, col);
         print_string("###0###");
         set_cursor(row++, col);
         print_string(" #####  ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string("   #   ");
         frame++;
      }
      else if(frame > 20 && frame <= 30){
         set_cursor(row++, col);
         print_string("   #   ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string(" ##0##  ");
         set_cursor(row++, col);
         print_string("##0#0##");
         set_cursor(row++, col);
         print_string(" ##0##  ");
         set_cursor(row++, col);
         print_string("  ###  ");
         set_cursor(row++, col);
         print_string("   #   ");
         frame++;
      }
      else if(frame > 30 && frame <= 40){
         set_cursor(row++, col);
         print_string("   #   ");
         set_cursor(row++, col);
         print_string("  #0#  ");
         set_cursor(row++, col);
         print_string(" #0#0#  ");
         set_cursor(row++, col);
         print_string("#0###0#");
         set_cursor(row++, col);
         print_string(" #0#0#  ");
         set_cursor(row++, col);
         print_string("  #0#  ");
         set_cursor(row++, col);
         print_string("   #   ");
         frame++;
      }
      else if(frame > 40 && frame <= 50){
         set_cursor(row++, col);
         print_string("   0   ");
         set_cursor(row++, col);
         print_string("  0#0  ");
         set_cursor(row++, col);
         print_string(" 0###0  ");
         set_cursor(row++, col);
         print_string("0#####0");
         set_cursor(row++, col);
         print_string(" 0###0  ");
         set_cursor(row++, col);
         print_string("  0#0  ");
         set_cursor(row++, col);
         print_string("   0   ");
         frame++;
      }
      else if(frame == 51){
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         set_cursor(row++, col);
         print_string("        ");
         frame++;
      }
      else
         return;
   }
   return;
}

/*

*/
void producer(void){
   int i = 5;
   for (i = 0; i < 5; i++)
      producer_anim();
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
   uint8_t row = 4, col = 0, i = 0;

   while(1){
      if(global < 2){  //garbage prints immediately, this cleans that up
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
      print_int(memBegin -> numThreads);
      for(int i = 0; i < memBegin -> numThreads; i++){ //print stats of each thread
         if(i < 3){
            col = (i % 3) * 30;
            row = 4;
         }
         else if (i > 2){
            col = (i % 3) * 30;
            row = 15;
         }

         set_color(GREEN);
         set_cursor(row++, col);
         print_string("Thread Id: ");
         print_int(memBegin->threads[i].id);
         set_cursor(row++, col);
         print_string("Thread name: ");
         print_string(memBegin->threads[i].tName);
         set_cursor(row++, col);
         print_string("Thread PC: ");
         print_hex(memBegin->threads[i].PC);
         set_cursor(row++, col);
         print_string("Stack Usage: ");
         print_int((uint16_t)memBegin->threads[i].stackEnd -
            (uint16_t)memBegin->threads[i].stackPointer);
         print_string(" bytes   ");
         set_cursor(row++, col);
         print_string("Stack Size: ");
         print_int(memBegin->threads[i].stackSize);
         print_string(" bytes   ");
         set_cursor(row++, col);
         print_string("Current top of stack: ");
         print_hex((uint16_t)memBegin->threads[i].stackPointer);
         set_cursor(row++, col);
         print_string("Stack base: ");
         print_hex((uint16_t)memBegin->threads[i].stackBase);
         set_cursor(row++, col);
         print_string("Stack end: ");
         print_hex((uint16_t)memBegin->threads[i].stackEnd);
         row++;
      }
   }
}
