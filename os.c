#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
#include "os.h"
#include <stdint.h>
extern volatile int global;
//memBegin holds the address of system_t
system_t *memBegin;
thread_t *dummyThread;
uint8_t curThread;
int numThreads;

__attribute__((naked)) void context_switch(uint16_t* new_sp, uint16_t* old_sp);
__attribute__((naked)) void thread_start(void);

/******************************************************************************
 * Function:  create_thread
 * --------------------
 * Desc: Initializes stack space for new threads. Managing tasks such as setting
 *       setting the correct stack pointer, storing the address of the
 *       functions to be threaded, allocating memory for the stack and
 *       storing the address of thread_start so that it can be called
 *       implicitly.
 *
 * Parameter:
 *    name: name of the function
 *    address: address of the thread to start
 *    args: pointer to the thread argument
 *    stack_size: size of the stack specified by the user
 *****************************************************************************/
//from here, we need to malloc the size of the registers, + necessary stack space
//i think we save this pointer where the memory is saved, somewhere....
void create_thread(char* name, uint16_t address, void* args, uint16_t stack_size) {
   void *memAddr = malloc(stack_size);
   memBegin -> threads[numThreads].stackBase = memAddr;
   memBegin -> threads[numThreads].stackEnd = memAddr + stack_size;

   //int *id = (int*)args;
   regs_context_switch *ptr;
   memAddr = memAddr + (stack_size - sizeof(regs_context_switch));
   memBegin -> threads[numThreads].stackTop = memAddr;

   ptr = (regs_context_switch*) memAddr;
   ptr->padding = 0;
   //now the address of the function is in our registers
   ptr->r29 = ((uint16_t) address & 0xFF00) >> 8;   // 0;
   ptr->r28 = ((uint16_t) address & 0x00FF);   // 0;
   //now the address of the arguments is in our registers as well
   ptr->r17 = ((uint16_t) args & 0xFF00) >> 8;   // 0;
   ptr->r16 = ((uint16_t) args & 0x00FF);   // 0;
   ptr->r15 = 0;
   ptr->r14 = 0;
   ptr->r13 = 0;
   ptr->r12 = 0;
   ptr->r11 = 0;
   ptr->r10 = 0;
   ptr->r9 = 0;
   ptr->r8 = 0;
   ptr->r7 = 0;
   ptr->r6 = 0;
   ptr->r5 = 0;
   ptr->r4 = 0;
   ptr->r3 = 0;
   ptr->r2 = 0;
   ptr->eind = 0;
   ptr->pch = ((uint16_t) thread_start & 0xFF00) >> 8;
   ptr->pcl = ((uint16_t) thread_start & 0x00FF);

   memBegin -> systemTime = 0;
   memBegin -> runningThread = 0;
   memBegin -> threads[numThreads].id = numThreads;
   memBegin -> threads[numThreads].PC = address; 
   //memBegin -> threads[numThreads].tName = name;
   memcpy(memBegin->threads[numThreads].tName, name, strlen(name) + 1);
   memBegin -> threads[numThreads].stackSize = stack_size;
   memBegin -> threads[numThreads].stackPointer = ptr;
   numThreads++;
}

/******************************************************************************
 * Function:  os_init
 * ------------------
 * Desc: Initializes the multithreading program by calling functions that
 *       will produce new threads and start context switches causing the threads
 *       to continuously swaps between each other.
 *
 * Parameter:
 *    N/A
 *****************************************************************************/
void os_init() {
   serial_init();
   int curThread = 0;

   dummyThread = (thread_t*) malloc(sizeof(thread_t));
   memBegin = (system_t*) malloc(sizeof(system_t));
   numThreads = 0;
   return;
}
void os_start(void){
   start_system_timer();
   sei();
   context_switch((uint16_t*)&memBegin -> threads[0].stackPointer,
   (uint16_t*)&dummyThread);
}


/******************************************************************************
 * Function:  get_next_thread
 * --------------------------
 * Desc: Defines the next thread to be ran in the queue
 *
 * Parameter:
 *    N/A
 *****************************************************************************/

uint8_t get_next_thread(void) {
   if(curThread < (numThreads - 1))
      curThread++;
   else
      curThread = 0;
   return curThread;
}

/******************************************************************************
 * Function:  ISR
 * --------------
 * Desc: Interrupt routine is automatically run every 10 milliseconds. It is
 *       used for the system_timer, context_switch(when to switch to a new
 *       thread).
 *
 * Parameter:
 *    TIMER0_COMPA_vect:
 *****************************************************************************/
//This interrupt routine is automatically run every 10 milliseconds
ISR(TIMER0_COMPA_vect) {
   void *new_sp, *old_sp;
   uint8_t curNode = curThread;
   uint8_t nextThread = get_next_thread();
   global++;

   //At the beginning of this ISR, the registers r0, r1, and r18-31 have
   //already been pushed to the stack

   //The following statement tells GCC that it can use registers r18-r31
   //for this interrupt routine.  These registers (along with r0 and r1)
   //will automatically be pushed and popped by this interrupt routine.
   asm volatile ("" : : : "r18", "r19", "r20", "r21", "r22", "r23", "r24", \
                 "r25", "r26", "r27", "r30", "r31");

   //Insert your code here
   //Call get_next_thread to get the thread id of the next thread to run
   //Call context switch here to switch to that next thread

   context_switch((uint16_t*)&memBegin -> threads[nextThread].stackPointer,
    (uint16_t*)&memBegin -> threads[curNode].stackPointer);
   //At the end of this ISR, GCC generated code will pop r18-r31, r1,
   //and r0 before exiting the ISR
}

/******************************************************************************
 * Function:  start_system_timer
 * -----------------------------
 * Desc: Call this to start the system timer interrupt
 *
 * Parameter:
 *    N/A
 *****************************************************************************/
//Call this to start the system timer interrupt
void start_system_timer() {
   TIMSK0 |= _BV(OCIE0A);  //interrupt on compare match
   TCCR0A |= _BV(WGM01);   //clear timer on compare match

   //Generate timer interrupt every ~10 milliseconds
   TCCR0B |= _BV(CS02) | _BV(CS00) | _BV(CS02);    //prescalar /1024
   OCR0A = 156;             //generate interrupt every 9.98 milliseconds
}

//new_sp = arg1 = r25(high) r24(low)
   //this is an address, move to Z
   //value in Z put in reg
//old_sp = arg2 = r23(high), r22(low)
//stackPointer = 0x005E (high) and 0x005D (low)
/*
   now that this works for new_sp.. i need to implement:
   pop all registers of the current stack into the area
      pointed to by old_sp

   then --> i think just commence with the code I already have


*/

/******************************************************************************
 * Function:  context_switch
 * -------------------------
 * Desc: Saves the state of the old thread and loads the state of the new thread
 *       to be ran. Saves the stack pointer into the address that old_sp points
 *       to. Moves new_sp values into the Z register. It will also pop off the
 *       top three bytes implicitly calling, thread_start when 'RET' is called.
 *
 * Parameter:
 *    new_sp: the stack pointer to the new thread
 *    old_sp: the stack pointer to the current thread
 *****************************************************************************/
__attribute__((naked)) void context_switch(uint16_t* new_sp, uint16_t* old_sp) {
   //am i pushing correctly, PUSH R2 FIRST
   asm volatile("push r2");
   asm volatile("push r3");
   asm volatile("push r4");
   asm volatile("push r5");
   asm volatile("push r6");
   asm volatile("push r7");
   asm volatile("push r8");
   asm volatile("push r9");
   asm volatile("push r10");
   asm volatile("push r11");
   asm volatile("push r12");
   asm volatile("push r13");
   asm volatile("push r14");
   asm volatile("push r15");
   asm volatile("push r16");
   asm volatile("push r17");
   asm volatile("push r28");
   asm volatile("push r29");
//SAVE stackpointer into the address that old_sp points to
/*
   save the current stack pointer into local registers...
   set the Z register to point to old_sp
   store the stack pointer values that we saved, into old_sp
0x005E = 5E
*/
   asm volatile("ldi r31, 0x00");
   asm volatile("ldi r30, 0x5E");
   asm volatile("ld r18, Z");
   asm volatile("ldi r30, 0x5D");
   asm volatile("ld r19, Z");
   //current stackptr now in r18-r19
   //now set Z reg, old_sp is in reg r23(high), r22(low)
   asm volatile("mov r31, r23");
   asm volatile("mov r30, r22");
   //now store the stack pointer values into Z...
///~~~~~~~~~~~~~~~~~~~POSSIBLE POINT OF FAILURE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   asm volatile("st Z+, r19"); //move Z pointer up 1 address...
   asm volatile("st Z, r18");

//THIS PART BELOW IS FOR THE new_sp
   //move new_sp values into Z
   asm volatile("mov r31, r25");
   asm volatile("mov r30, r24");
   asm volatile("ld r21, Z+"); //asm volatile("ld r22, Z+"); post incr
   //increment z, store val in another reg
   //asm volatile("adiw Z, 1");
   asm volatile("ld r22, Z");
   //now r22 and r21 hold the values we will we writing into the stack stackPointer
   //we must move Z to point to the stack pointer
   asm volatile("ldi r31, 0x00");
   asm volatile("ldi r30, 0x5E");
   asm volatile("st Z, r22");

   asm volatile("ldi r30, 0x5D");
   asm volatile("st Z, r21");

   asm volatile("pop r29");
   asm volatile("pop r28");
   asm volatile("pop r17");
   asm volatile("pop r16");
   asm volatile("pop r15");
   asm volatile("pop r14");
   asm volatile("pop r13");
   asm volatile("pop r12");
   asm volatile("pop r11");
   asm volatile("pop r10");
   asm volatile("pop r9");
   asm volatile("pop r8");
   asm volatile("pop r7");
   asm volatile("pop r6");
   asm volatile("pop r5");
   asm volatile("pop r4");
   asm volatile("pop r3");
   asm volatile("pop r2");
   asm volatile("RET");
}

/******************************************************************************
 * Function:  thread_start
 * -----------------------
 * Desc: Starts the given thread by moving the stack pointer into the program
 *       counter as well as the function arguments into the correct registers.
 *
 * Parameter:
 *    N/A
 *****************************************************************************/
//load r17 (high), r16 (low) of the arguments, into r25(high), r24(low) for ARGS1
//load r29 (high), r28 (low) of the address into the Z register...
//ijmp to address specified by Z
__attribute__((naked)) void thread_start(void) {
   sei(); //enable interrupts - leave as the first statement in thread_start()
   asm volatile("mov r25, r17");
   asm volatile("mov r24, r16");
   asm volatile("mov r31, r29");
   asm volatile("mov r30, r28");
   asm volatile("ijmp");
}
