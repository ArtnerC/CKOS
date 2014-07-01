/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: Threads.c - CKOS Cooperative and Preemptive Threading
*****************************************************************************/

#include "ports_D256.h"
#include "serial.h"
#include "Scheduler.h"
#include "Threads.h"

//Register Map
//register volatile unsigned char * REG_A asm("a");
//register volatile unsigned char * REG_B asm("b");
//register volatile unsigned char * REG_D asm("d");
//register volatile unsigned char * REG_X asm("x");
//register volatile unsigned char * REG_Y asm("y");
register volatile unsigned char * REG_SP asm("sp");
//register volatile unsigned char * REG_PC asm("pc");
//register volatile unsigned char * _REG_CCR asm("ccr");

//Global Vars
unsigned short int _address     = 0x0000;
unsigned short int _current_sp  = 0x0000;
unsigned short int _next_sp     = 0x0000;

/*****************************************************************************
* Function Name: Push
* Params:
*    void
* Returns:
*    void
* Discription:
*    Pushes important registers to current stack.
*****************************************************************************/
static void inline Push()
{
    //Push Registers
    asm volatile("PSHY");
    asm volatile("PSHX");
    asm volatile("PSHD");
    asm volatile("PSHC");
    asm volatile("LDY _.frame");
    asm volatile("PSHY");
    asm volatile("LDY _.tmp");
    asm volatile("PSHY");
    asm volatile("LDY _.z");
    asm volatile("PSHY");
    asm volatile("LDY _.xy");
    asm volatile("PSHY");
}

/*****************************************************************************
* Function Name: Pop
* Params:
*    void
* Returns:
*    void
* Discription:
*    Pops important registers from current stack.
*****************************************************************************/
static void inline Pop()
{
    //Pop Registers
    asm volatile("PULY");
    asm volatile("STY _.xy");
    asm volatile("PULY");
    asm volatile("STY _.z");
    asm volatile("PULY");
    asm volatile("STY _.tmp");
    asm volatile("PULY");
    asm volatile("STY _.frame");
    asm volatile("PULC");
    asm volatile("PULD");
    asm volatile("PULX");
    asm volatile("PULY");
}

/*****************************************************************************
* Function Name: InitThreading
* Params:
*    void
* Returns:
*    void
* Discription:
*    Initializes everything needed for Cooperative and Preemptive Threading
*****************************************************************************/
void InitThreading()
{
    //Initialize Scheduler
    InitScheduler();

    //Setup Interrupt Vectors
    asm volatile("sei");
    *(void(**)())0x3ff6 = SWI_ISR; //Software Interrupt (Cooperative)
    *(void(**)())0x3ff0 = RTI_ISR; //Real-Time Clock Interrupt (Preemptive)
    asm volatile("cli");
}

/*****************************************************************************
* Function Name: Preempt
* Params:
*    void
* Returns:
*    void
* Discription:
*    Begins Preemptive Threading and waits for first Interrupt
*****************************************************************************/
void inline Preempt()
{
    asm volatile("sei");    //Set Interrupt Mask
    RTICTL = 0x70;          //Set Rate
    CRGINT = 0x80;          //Enable RTI
    CRGFLG = 0x80;          //Clear RTI Flag
    asm volatile("cli");    //Clear Interrupt Mask
    
    while(1)
    {
        asm volatile("wai");//Wait for Interrupt
    }
}

/*****************************************************************************
* Function Name: SWI_ISR
* Params:
*    void
* Returns:
*    void
* Discription:
*    Interrupt Handler for Software Interrupts
*****************************************************************************/
void __attribute__((interrupt)) SWI_ISR()
{
    //Save Current SP
    if(SCHEDULER_CURRENT)
        SCHEDULER_CURRENT->m_stack = REG_SP;

    //Schedule Next Task
    REG_SP = SCHEDULER_NEXT->m_stack;

    //SCHEDULER_PREVIOUS = SCHEDULER_PREVIOUS->m_next;
    SCHEDULER_CURRENT = SCHEDULER_NEXT;
    SCHEDULER_NEXT = SCHEDULER_NEXT->m_next;
}

/*****************************************************************************
* Function Name: RTI_ISR
* Params:
*    void
* Returns:
*    void
* Discription:
*    Interrupt Handler for Real-Time Clock Interrupts
*****************************************************************************/
void __attribute__((interrupt)) RTI_ISR()
{
    //Set interrupt mask (already done)
    //asm volatile("sei");

    //Save Current SP
    if(SCHEDULER_CURRENT)
        SCHEDULER_CURRENT->m_stack = REG_SP;

    //Schedule Next Task
    REG_SP = SCHEDULER_NEXT->m_stack;

    //SCHEDULER_PREVIOUS = SCHEDULER_PREVIOUS->m_next;
    SCHEDULER_CURRENT = SCHEDULER_NEXT;
    SCHEDULER_NEXT = SCHEDULER_NEXT->m_next;

    //Clear RTI Flag
    CRGFLG |= 0x80;

    //Clear Interrupt mask
    //asm volatile("cli");
}

/*****************************************************************************
* Function Name: CreateThread
* Params:
*    address    -   Starting address of thread
* Returns:
*    void
* Discription:
*    Creates new thread and pushes it on the Scheduler
*****************************************************************************/
void CreateThread(unsigned short int address)
{
    //Set Interrupt Mask
    asm volatile("sei");

    //Save Address
    _address = address;

    //Push Registers
    Push();

    //Save Current Stack Pointer
    _current_sp = (unsigned short)REG_SP;

    //Load New Stack Pointer
    REG_SP = (unsigned char *)((unsigned short int)Malloc(256) + 255);

    //New Thread
    asm volatile("LDX _address");   //pc
    asm volatile("PSHX");
    asm volatile("LDY #0x0000");    //iy
    asm volatile("PSHY");
    asm volatile("LDX #0x0000");    //ix
    asm volatile("PSHX");
    asm volatile("LDD #0x0000");    //d
    asm volatile("PSHD");
    asm volatile("LDAA #0xC0");     //ccr
    asm volatile("PSHA");

    //Push New Thread Registers
    asm volatile("LDX _.frame");    //frame
    asm volatile("PSHX");
    asm volatile("LDX _.tmp");      //temp
    asm volatile("PSHX");
    asm volatile("LDX _.z");        //z
    asm volatile("PSHX");
    asm volatile("LDX _.xy");       //xy
    asm volatile("PSHX");

    //Add to Scheduler
    SchPush((unsigned short)REG_SP);

    //Restore Current Stack Pointer
    REG_SP = (unsigned char *)_current_sp;
    
    //Pop Registers
    Pop();
    
    //Clear interrupt mask
    asm volatile("cli");
}

/*****************************************************************************
* Function Name: Yield
* Params:
*    void
* Returns:
*    void
* Discription:
*    Software Interrupt Wrapper
*****************************************************************************/
void inline Yield()
{
    //Trigger Software Interrupt
    asm volatile("swi");
}

Semiphore * CreateSemiphore(int count)
{
    Semiphore * ret = (Semiphore *)Malloc(sizeof(Semiphore));
    ret->m_count = count;
    ret->m_blocked = 0;
}

Semiphore * CreateMutex()
{
    Semiphore * ret = (Semiphore *)Malloc(sizeof(Semiphore));
    ret->m_count = 1;
    ret->m_blocked = 0;
}

void DestroySemiphore(Semiphore * sem)
{
    sem->m_count = 0;
    if(sem->m_blocked)
    {
        SetError("Destroy Semiphore - BAD SEMIPHORE USE");
        while(sem->m_blocked)
            SchResume(&sem->m_blocked);
    }

    Free((char *)sem);
}

void Wait(Semiphore * sem)
{
    T_CRITICAL_BEGIN
    
    if(sem->m_count <= 0)
    {
        SchBlock(&(sem->m_blocked));
        asm volatile("swi");
    }
    
    sem->m_count--;
    
    T_CRITICAL_END
}

void Signal(Semiphore * sem)
{
    T_CRITICAL_BEGIN
    
    sem->m_count++;
    SchResume(&(sem->m_blocked));
    
    T_CRITICAL_END
}
