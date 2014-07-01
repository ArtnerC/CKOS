/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: Scheduler.h - CKOS Task Scheduler
*****************************************************************************/

#ifndef CKOS_SCHEDULER
#define CKOS_SCHEDULER

//Define Scheduler Task Node
typedef struct SchThreadNode
{
    //char m_threadID;
    //int m_priority;
    unsigned short int m_stack;
    struct SchThreadNode * m_next;
    struct SchThreadNode * m_prev;
} SchThread;

//Scheduler Blocked List Node
typedef struct SchBlockedNodeN
{
    SchThread * m_thread;
    struct SchBlockedNodeN * m_next;
} SchBlockedNode;

//Scheduler List Pointers
extern SchThread * SCHEDULER_CURRENT;   //Current Running Task
extern SchThread * SCHEDULER_NEXT;
//extern SchThread * SCHEDULER_PREVIOUS;      //Previous task ran
extern SchThread * SCHEDULER_START;     //Startup Task
extern SchThread * SCHEDULER_END;       //Last node in queue

//Scheduler Functions
void InitScheduler();
void SchPush(unsigned short int node);
void SchSaveCurr(unsigned short int stack);
unsigned short int SchCurr();
unsigned short int SchNext();
void SchRem(unsigned short int node);
void SchBlock(SchBlockedNode ** q);
void SchResume(SchBlockedNode ** q);

#endif /* CKOS_SCHEDULER */
