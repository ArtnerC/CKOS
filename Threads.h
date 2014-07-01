/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: Threads.h - CKOS Cooperative and Preemptive Threading
*****************************************************************************/

#ifndef CKOS_THREADS
#define CKOS_THREADS

#include "Scheduler.h"

//Register Map
//extern unsigned short __tmp    __asm__("_.tmp");
//extern unsigned short __z      __asm__("_.z");
//extern unsigned short __xy     __asm__("_.xy");
//extern unsigned short __frame  __asm__("_.frame");

//Critical Section Defines
#define T_CRITICAL_BEGIN    asm volatile("sei");
#define T_CRITICAL_END      asm volatile("cli");

//Global Vars
extern unsigned short int _address;
extern unsigned short int _current_sp;
extern unsigned short int _next_sp;

typedef struct SemiphoreN
{
    int m_count;
    SchBlockedNode * m_blocked;
} Semiphore;

//Threads Functions
static void inline Push();
static void inline Pop();
void InitThreading();
void inline Preempt();
void SWI_ISR(void) __attribute__((interrupt));
void RTI_ISR(void) __attribute__((interrupt));
void CreateThread(unsigned short int address);
void inline Yield();

//Semiphore Functions
Semiphore * CreateSemiphore(int count);
Semiphore * CreateMutex();
void DestroySemiphore(Semiphore * sem);
void Wait(Semiphore * sem);
void Signal(Semiphore * sem);

#endif /* CKOS_THREADS */
