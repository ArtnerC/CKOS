/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: Main.c - OS Entry Point
*****************************************************************************/
#include "serial.h"
#include "ports_d256.h"
#include "CKLib.h"
#include "Threads.h"
#include "Scheduler.h"
#include "MemMgr.h"
#include "Console.h"

extern void RunConsole();
void Thread();
void Thread2();
void Thread3();
void Thread4();

Semiphore * items = 0;
Semiphore * holes = 0;
Semiphore * mutex = 0;
char buff[64] = { "" };
int currInsert = 0;
int currRemove = 0;

main()
{
    InitConsole();      //Initialize Console
    InitMemMgr();       //Initialize Memory Manager
    InitThreading();    //Initialize Threading

    //CreateThread((unsigned short)RunConsole);
    CreateThread((unsigned short)Thread3);
    CreateThread((unsigned short)Thread3);

    CreateThread((unsigned short)Thread);
    CreateThread((unsigned short)Thread2);
    
    //Create Mutex Semiphore
    holes = CreateSemiphore(64);
    items = CreateSemiphore(0);
    mutex = CreateMutex();

    //[!!!]Must be LAST in main()[!!!]
    Preempt();
    
    //With Preempt() called this should never be executed
    SetError("ERROR! MAIN EXITING! THIS IS IMPOSSIBLE!");
}

addItem(char c)
{
    Wait(holes);
    Wait(mutex);

    buff[currInsert] = c;
    currInsert++;
    currInsert %= 64;

    Signal(mutex);
    Signal(items);
}

char removeItem()
{
    char c;
    Wait(items);
    Wait(mutex);

    c = buff[currRemove];
    currRemove++;
    currRemove %= 64;

    Signal(mutex);
    Signal(holes);
    
    return c;
}

//Worker Thread 1
void Thread()
{
    puts("Enter T1\n");
    while(1)
    {
        //putch('1');

        addItem('g');
        
        //Yield();
    }
}

//Worker Thread 2
void Thread2()
{
    puts("Enter T2\n");
    while(1)
    {
        //putch('1');

        addItem('l');

        //Yield();
    }
}

//Worker Thread 3
void Thread3()
{
    puts("Enter T3\n");
    while(1)
    {
        //putch('3');
        
        putch(removeItem());
        
        //Yield();
    }
}

/*****************************************************************************
* Function Name: [Function Name]
* Params:
*    [Type ID]    -    [Short Description]
* Returns:
*    [Returns]
* Discription:
*    [Description]
*****************************************************************************/

/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: [File].[ext] - [Short Desc]
*****************************************************************************/
