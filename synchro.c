#include "globals.h"
#include "os.h"
#include "synchro.h"
#include <avr/interrupt.h>

extern system_t *memBegin;
extern struct mutex_t *printLock;
extern volatile int global;
extern int numThreads;
/*
   put the thread to sleep for the specified number of ticks...
   count global timer maybe?
*/

void printState(enum state curState){
   switch(curState){
      case THREAD_READY:
         print_string("THREAD_READY");
         break;
      case THREAD_WAITING:
         print_string("THREAD_WAITING");
         break;
      case THREAD_RUNNING:
         print_string("THREAD_RUNNING");
         break;
      case THREAD_SLEEPING:
         print_string("THREAD_SLEEPING");
         break;
   }
}

void mutex_init(struct mutex_t* m)
{
   m = (struct mutex_t*)malloc(sizeof(mutex_t));
   m -> lock = 1;
   m -> waiting = 0;
}
void mutex_lock(struct mutex_t* m){
   cli();
   if(m -> lock != 1){ //lock unavailable
      memBegin -> threads[memBegin -> runningThread].curState = THREAD_WAITING;
      m -> waitList[m -> waiting++] = memBegin -> runningThread; //add to waitlist
         //with this implementation, we need to reorder the array in mutex_unlock
      yield();
   }
   else
      m -> lock = 0;

   sei();
}
/*
   Simple function to resort the array after taking
      the first member of the waitlist
*/
void siftArray(struct mutex_t* p, int count){
   int i;
   for(i = 0; i < count - 1; i++){
      p -> waitList[i] = p -> waitList[i + 1];
   }
}
void mutex_unlock(struct mutex_t* m){
   cli();
   m -> lock = 1;
   //change the state of the first thread on waitlist
   //so that get_next_thread will actually call it
   if(m -> waiting > 0){
      memBegin -> threads[m -> waitList[0]].curState = THREAD_READY;
      siftArray(m, 8);
   }
   sei();
}


void thread_sleep(uint16_t ticks){

}

void seminit(struct semaphore_t* s, int8_t value){
   s = (struct semaphore_t*)malloc(sizeof(semaphore_t));
   s->value = value;
}

void sem_wait(struct semaphore_t* s){
   cli();
   s->value--;
   if (s->value < 0) {
      // block();
   }
   sei();
}

void sem_signal(struct semaphore_t* s){
   cli();
   s->value++;
   if (s->value <= 0) {
      // wakeup(P);
   }
   sei();
}

void sem_signal_swap(struct semaphore_t* s){

}

void blink_V2(void){

}
/*
   Just the function for the consumer animation.
   call it once to iterate the animation once
*/
void consumer_anim(void){
   uint8_t row = 26, col = 20;
   uint8_t setColor = CYAN, base = WHITE;
   int frame = 0;
   while(1){
      set_color(base);
      row = 26;
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
   while(1){
      mutex_lock(printLock);
      consumer_anim();
      mutex_unlock(printLock);
   }
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
      mutex_lock(printLock); ///////FUUUUUUUUUUUU DOES THIS WORK?!?!
      if(global < 2){  //garbage prints immediately, this cleans that up
         clear_screen();
      }
      row = 4;
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
            col = (i % 3) * 33;
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
         set_cursor(row++, col);
         print_string("Sched. Count: ");
         print_int(memBegin -> threads[memBegin -> runningThread].sched_count);
         set_cursor(row++, col);
         print_string("Thread Status: ");
         printState(memBegin -> threads[i].curState);
         row++;
      }
   mutex_unlock(printLock);
   }
}
