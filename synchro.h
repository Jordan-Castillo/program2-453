#ifndef SYNC_H
#define SYNC_H

//includes necessary...

//Structures....
typedef struct {
   int count;
}semaphore;

typedef struct mutex_t{
   int lock;
   int waitList[8];
   int waiting;
}mutex_t;


//function constructors...
void mutex_init(struct mutex_t* m);
void mutex_lock(struct mutex_t* m);
void mutex_unlock(struct mutex_t* m);
void display_stats(void);
void blink_V2(void);
void consumer(void);
void producer(void);
void display_bounded_buffer(void);
//structures, enums, globals...
enum state {THREAD_RUNNING, THREAD_READY, THREAD_SLEEPING, THREAD_WAITING};
//THREAD_RUNNING - instructions currently being processed by processor
//THREAD_READY - When the thread is ready to run, and waiting on a processor
//THREAD_SLEEPING - when the thread is asleep after a thread_asleep call
//THREAD_WAITING - after a call to mutex or semaphore fails

#endif
