/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: Scheduler.c - CKOS Task Scheduler
*****************************************************************************/

#include "serial.h"
#include "ports_d256.h"
#include "CKLib.h"
#include "MemMgr.h"
#include "Scheduler.h"

SchThread * SCHEDULER_CURRENT = 0;
SchThread * SCHEDULER_NEXT = 0;
//SchThread * SCHEDULER_PREVIOUS = 0;
SchThread * SCHEDULER_START = 0;
SchThread * SCHEDULER_END = 0;

/*****************************************************************************
* Function Name: InitScheduler
* Params:
*    void
* Returns:
*    void
* Discription:
*    Initializes Scheduler to a Healthy State
*****************************************************************************/
void InitScheduler()
{
    //Make sure Scheduler is not already initialized
    if(!SCHEDULER_START)
    {
        //Create Starting Node *removed*
        SCHEDULER_START = 0;
        SCHEDULER_END = SCHEDULER_START;
        //SCHEDULER_CURRENT = SCHEDULER_START;
        SCHEDULER_NEXT = SCHEDULER_START;
        //SCHEDULER_PREVIOUS = SCHEDULER_START;
    }
    else
    {
        //Set Error Message
        SetError("InitScheduler - Scheduler already initialized!");
    }
    return;
}

/*****************************************************************************
* Function Name: SchPush
* Params:
*    node   -   Stack pointer to a task
* Returns:
*    void
* Discription:
*    Adds a new task to the scheduler
*****************************************************************************/
void SchPush(unsigned short int node)
{
    //Check for empty node
    if(!node)
    {
        SetError("SchPush - Null node");
        return;
    }
    
    //Add first Task
    if(!SCHEDULER_START)
    {
        SCHEDULER_START = (SchThread *)Malloc(sizeof(SchThread));
        SCHEDULER_START->m_next = SCHEDULER_START;
        SCHEDULER_START->m_prev = SCHEDULER_START;
        SCHEDULER_START->m_stack = node;
        
        SCHEDULER_END = SCHEDULER_START;
        //SCHEDULER_CURRENT = SCHEDULER_START;
        SCHEDULER_NEXT = SCHEDULER_START;
        //SCHEDULER_PREVIOUS = SCHEDULER_START;
        return;
    }
    //Add additional task
    else
    {
        SchThread * temp = (SchThread *)Malloc(sizeof(SchThread));
        temp->m_next = SCHEDULER_END->m_next;
        temp->m_prev = SCHEDULER_END;
        temp->m_stack = node;
        
        SCHEDULER_END->m_next = temp;
        SCHEDULER_END = temp;
        SCHEDULER_START->m_prev = SCHEDULER_END;
    }
}

/*****************************************************************************
* Function Name: SchSaveCurr
* Params:
*    stack  -   Stack pointer for a Task
* Returns:
*    void
* Discription:
*    Saves the stack pointer to the current running Task
*****************************************************************************/
void SchSaveCurr(unsigned short int stack)
{
    SCHEDULER_CURRENT->m_stack = stack;
}

/*****************************************************************************
* Function Name: SchCurr
* Params:
*    void
* Returns:
*    Pointer to the stack of the currently running Task
* Discription:
*    Returns the currently running threads stack pointer
*****************************************************************************/
unsigned short int SchCurr()
{
    return SCHEDULER_CURRENT->m_stack;
}

/*****************************************************************************
* Function Name: SchNext
* Params:
*    void
* Returns:
*    Pointer to the stack of the next Task to be ran
* Discription:
*    Advances the Scheduler to the next task and returns a pointer to its stack
*****************************************************************************/
unsigned short int SchNext()
{
    //Advance to next task
    //SCHEDULER_PREVIOUS = SCHEDULER_CURRENT;
    SCHEDULER_CURRENT = SCHEDULER_NEXT;
    SCHEDULER_NEXT = SCHEDULER_NEXT->m_next;

    //Return stack pointer
    return SCHEDULER_CURRENT->m_stack;
}

/*****************************************************************************
* Function Name: SchRem
* {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{ UN-TESTED }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
* Params:
*    node   -   Stack pointer
* Returns:
*    void
* Discription:
*    Removes a Task from Scheduler based on its Stack pointer
*****************************************************************************/
void SchRem(unsigned short int node)
{
    if(!node)
    {
        SetError("SchRem - Null node");
        return;
    }
    if(!SCHEDULER_CURRENT)
    {
        SetError("SchRem - Remove on empty list");
        return;
    }
    if(SCHEDULER_CURRENT->m_stack == node)
    {
        Free((char *)SCHEDULER_CURRENT);
        SCHEDULER_CURRENT = 0;
        return;
    }
    else
    {
        SchThread * curr = SCHEDULER_CURRENT->m_next;
        SchThread * prev = SCHEDULER_CURRENT;
        while(curr != SCHEDULER_CURRENT)
        {
            if(curr->m_stack == node)
            {
                prev->m_next = curr->m_next;
                Free((char *)curr);
                return;
            }
            prev = curr;
            curr = curr->m_next;
        }
    }
}

void SchBlock(SchBlockedNode ** q)
{
    //Create new blocked node
    SchBlockedNode * last = (*q);
    SchBlockedNode * node = (SchBlockedNode *)Malloc(sizeof(SchBlockedNode));
    node->m_thread = SCHEDULER_CURRENT;
    node->m_next = 0;
    
    //Add node to queue
    if((*q) == 0)
    {
        (*q) = node;
    }
    else
    {
        while(last->m_next != 0)
        {
            last = last->m_next;
        }
        last->m_next = node;
    }

    //Remove thread from scheduler
    if(SCHEDULER_START == SCHEDULER_END)
    {
        SetError("ERROR! ORPHAN THREAD BLOCKING!");
    }

    SCHEDULER_CURRENT->m_next->m_prev = SCHEDULER_CURRENT->m_prev;
    SCHEDULER_CURRENT->m_prev->m_next = SCHEDULER_CURRENT->m_next;

    if(SCHEDULER_START == SCHEDULER_CURRENT)
        SCHEDULER_START = SCHEDULER_CURRENT->m_next;

    if(SCHEDULER_END == SCHEDULER_CURRENT)
        SCHEDULER_END = SCHEDULER_CURRENT->m_prev;
        
    //putch('B');
}

void SchResume(SchBlockedNode ** q)
{
    if((*q) != 0)
    {
        SchBlockedNode * temp = (*q);
        
        //Add back to scheduler
        (*q)->m_thread->m_next = SCHEDULER_CURRENT->m_next;
        (*q)->m_thread->m_prev = SCHEDULER_CURRENT;
        SCHEDULER_NEXT->m_prev = (*q)->m_thread;
        SCHEDULER_CURRENT->m_next = (*q)->m_thread;
        SCHEDULER_NEXT = (*q)->m_thread;
        
        if(SCHEDULER_CURRENT == SCHEDULER_END)
        {
            SCHEDULER_END = (*q)->m_thread;
        }
        
        //Remove queue node
        (*q) = (*q)->m_next;
        Free((char *)temp);

        //putch('R');
    }
}
