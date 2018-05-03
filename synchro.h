#ifndef SYNC_H
#define SYNC_H

//includes necessary...

//function constructors...
void display_stats(void);
void blink_V2(void);
void consumer(void);
void producer(void);
void display_bounded_buffer(void);
//structures, enums, globals...
enum state {THREAD_RUNNING, THREAD_READY, THREAD_SLEEPING, THREAD_WAITING};
//THREAD_RUNNING - can be paused during this statement
//THREAD_READY - Only happens during initialization of the thread
//THREAD_SLEEPING - when the thread is asleep after a thread_asleep call
//THREAD_WAITING - after a call to mutex or semaphore fails

#endif
