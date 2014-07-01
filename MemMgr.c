/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: MemMgr.c - CKOS Memory Manager
*****************************************************************************/

#include "serial.h"
#include "ports_d256.h"
#include "CKLib.h"
#include "MemMgr.h"

//Memory Lists
MemStruct* MM_FREE_LIST;
MemStruct* MM_ALLOC_LIST;

/*****************************************************************************
* Function Name: InitMemMgr
* Params:
*    void
* Returns:
*    void
* Discription:
*    Initializes Memory Manager Lists and Memory Pattern
*****************************************************************************/
void InitMemMgr()
{
    //Initialize Lists
    MM_ALLOC_LIST = 0;
    MM_FREE_LIST = (MemStruct *)MM_HEAP_START;
    
    //Create Struct at start of Free List
    MM_FREE_LIST->m_next = 0;
    MM_FREE_LIST->m_prev = 0;
    MM_FREE_LIST->m_size = ((MM_HEAP_END - MM_HEAP_START) / MM_BLOCK_SIZE) - 1;

    //Initialize memory
    Fill((char *)&MM_FREE_LIST[1], (char *)MM_HEAP_END, MM_PATTERN_INIT);
}

/*****************************************************************************
* Function Name: MemDump
* Params:
*    start  -   Address of Memory Dump Start
*    len    -   Number of blocks to dump
* Returns:
*    void
* Discription:
*    Prints out a memory dump of [len] blocks starting at [start]
*****************************************************************************/
void MemDump(char * start, int len)
{
    unsigned char * mem = start;
    char ascii[MM_BLOCK_SIZE + 1] = { "" };
    char addStr[sizeof(MemStruct *) + 1] = { "" };
    int remBlocks = len;
    int cLine;

    //If start is null, start at heaps starting address
    if(!start)
        mem = MM_HEAP_START;

    //If len is null, go entire heap length
    if(!remBlocks)
        remBlocks = (MM_HEAP_END - MM_HEAP_START) / MM_BLOCK_SIZE;
    
    //Print out goodies
    puts("[Memory Dump: 0x");
    PtoX(addStr, mem);
    puts(addStr);
    puts(" - 0x");
    PtoX(addStr, mem + (MM_BLOCK_SIZE * remBlocks));
    puts(addStr);
    puts("]\n");

    //Print out every block on new line
    while((mem != MM_HEAP_END) && remBlocks)
    {
        //Print address
        puts("0x");
        PtoX(addStr, mem);
        puts(addStr);
        puts(" ");

        //Reset ascii string
        Strcpy((unsigned char *)ascii, (unsigned char *)"\0\0\0\0\0\0\0\0");

        //Print hex
        for(cLine = 0; (cLine < MM_BLOCK_SIZE) && (mem != MM_HEAP_END); cLine++)
        {
            char buff[3] = { "00" };
            CtoX(buff, *mem);
            puts(buff);
            puts(" ");
            
            if(((*mem > 0x00) && (*mem <= 0x1F)) || (*mem == 0x7F)) //Throws Warning: GCC Bug PR 25886
                ascii[cLine] = 0x80;
            else if(*mem == 0x00)
                ascii[cLine] = '.';
            else
                ascii[cLine] = *mem;
            _INC_PTR(mem);
        }
        
        //Print ASCII
        puts("\"");
        puts(ascii);
        puts("\"\n");
        
        //Decrement blocks remaining to print
        remBlocks--;
    }
    
    puts("[End Memory Dump]\n");
}

/*****************************************************************************
* Function Name: Malloc
* Params:
*    size   -   Size in bytes
* Returns:
*    Pointer to allocated memory block
* Discription:
*    Allocates [size] bytes of memory and returns address to start of memory
*****************************************************************************/
char * Malloc(int size)
{
    MemStruct * current = MM_FREE_LIST; //Pointer to current node
    MemStruct * match = 0;              //Best fitting memory found
    unsigned char best_fit, min_best;   //Holds blocks required for best fit and minimum best fit conditions

    //Calculate best fit and min best fit in blocks
    best_fit = (size / MM_BLOCK_SIZE);
    if(size % MM_BLOCK_SIZE)
        best_fit += 1;
    min_best = best_fit + 2;

    //Empty list, no available memory
    if(!MM_FREE_LIST)
    {
        SetError("No free memory available!");
        return 0;
    }

    //Look for free memory block
    while(current)
    {
        //Is found block a perfect size match
        if(current->m_size == best_fit)
        {
            match = current;
            break;
        }
        //Is found block at least a best fit
        else if(current->m_size > best_fit)
        {
            //Is found block a better fit than a previous best fit block
            if(!match || (current->m_size < match->m_size))
            {
                match = current;
            }
        }

        //Advance in list
        current = current->m_next;
    }

    //No sufficent memory available
    if(!match || (match->m_size < best_fit))
    {
        SetError("No memory of requested size available!");
        return 0;
    }
    //Found memory was a minimum best fit and can be split
    else if(match->m_size >= min_best)
    {
        SplitMem(match, best_fit);
    }

    //Remove from free list
    Remove(&MM_FREE_LIST, match);

    //Fill allocated memory
    Fill((char *)&match[1], (char *)&match[match->m_size + 1], MM_PATTERN_ALLOC);

    //Add to allocated list
    Insert(&MM_ALLOC_LIST, match);

    //Return pointer to alocated memory
    return (char *)&match[1];
}

/*****************************************************************************
* Function Name: Free
* Params:
*    ptr    -   Memory pointer
* Returns:
*    void
* Discription:
*    Frees the memory block at location indicated by [ptr]
*****************************************************************************/
void Free(char * ptr)
{
    ptr -= MM_BLOCK_SIZE;
    MemStruct * mem = (MemStruct *)ptr;
    MemStruct * current = MM_ALLOC_LIST;
    BOOL bMemExists = FALSE;

    //If address provided is invalid
    if((mem < (MemStruct *)MM_HEAP_START) || (mem > (MemStruct *)MM_HEAP_END))
    {
        SetError("Invalid address to free. Illegal Memory access!");
        return;
    }

    //Make sure memory location exists
    while(current)
    {
        if(current == mem)
        {
            bMemExists = TRUE;
            break;
        }
        current = current->m_next;
    }

    if(bMemExists == TRUE)
    {
        //Remove memory from allocated list
        Remove(&MM_ALLOC_LIST, mem);

        //Fill freed memory
        Fill((char *)&mem[1], (char *)&mem[mem->m_size + 1], MM_PATTERN_FREE);

        //Add to free list
        Insert(&MM_FREE_LIST, mem);

        //Check for contiguous memory
        ContigMem(mem);
    }
    else
    {
        SetError("Invalid free address! Cannot Free!");
    }
    return;
}

/*****************************************************************************
* Function Name: Insert
* Params:
*    list   -   List to use
*    node   -   Node pointer
* Returns:
*    void
* Discription:
*    Inserts [node] at its correct place in [list]
*****************************************************************************/
void Insert(MemStruct** list, MemStruct* node)
{    
    MemStruct * current = (*list);
    //List is empty
    if(!(*list))
    {
        //Add first node
        (*list) = node;
        node->m_next = 0;
        return;
    }
    //Node blongs at beginning of list
    else if(node < (*list))
    {
        (*list)->m_prev = node;
        node->m_next = (*list);
        (*list) = node;
        return;
    }
    
    //Look for place to insert node
    while(current)
    {
        //Insert node before current
        if(node < current)
        {
            node->m_next = current;
            node->m_prev = current->m_prev;
            node->m_prev->m_next = node;
            node->m_next->m_prev = node;

            return;
        }
        //Current node is last in the list
        else if(!current->m_next)
        {
            current->m_next = node;
            node->m_prev = current;
            node->m_next = 0;
            return;
        }
        //Advance to next node
        current = current->m_next;
    }
    
    //Successful insertion returns before this is reached
    SetError("Unknown Insert error");
}

/*****************************************************************************
* Function Name: Remove
* Params:
*    list   -   List to use
*    node   -   Node pointer
* Returns:
*    void
* Discription:
*    Removes [node] from its place in [list]
*****************************************************************************/
void Remove(MemStruct** list, MemStruct* node)
{
    //If list is empty or node is null
    if(!(*list) || !node)
    {
        //Set error and return
        SetError("Remove Performed on empty list.");
        return;
    }
    //If node to be removed is first node
    if((*list) == node)
    {
        (*list) = node->m_next;
        node->m_next->m_prev = 0;
    }
    //Otherwise remove node when its found
    else
    {
        if(node->m_prev)
            node->m_prev->m_next = node->m_next;

        if(node->m_next)
            node->m_next->m_prev = node->m_prev;
    }

    //Clear nodes next and prev members
    node->m_next = 0;
    node->m_prev = 0;
}

/*****************************************************************************
* Function Name: SplitMem
* Params:
*    node   -   Node pointer
*    size   -   New node size
* Returns:
*    Pointer to newly created node
* Discription:
*    Splits [node] into two different nodes based on [size], keeping both
*    in current list.
*****************************************************************************/
MemStruct* SplitMem(MemStruct* node, unsigned char size)
{
    MemStruct* newmem = &node[size + 1];
    newmem->m_size = node->m_size - size - 1;
    newmem->m_next = node->m_next;
    node->m_size = size;
    node->m_next = newmem;
    newmem->m_prev = node;
    return newmem;
}

/*****************************************************************************
* Function Name: ContigMem
* Params:
*    node   -   Node pointer
* Returns:
*    Pointer to merged node
* Discription:
*    Merges [node] with its next and previous node if they are contiguous
*****************************************************************************/
MemStruct* ContigMem(MemStruct* node)
{
    MemStruct* curr = node;
    MemStruct* next = &curr[curr->m_size + 1];
    MemStruct* ret  = node;
    if(curr && (curr->m_next == next))
    {
        MemStruct* free_start = &curr[1];
        MemStruct* free_end = &free_start[curr->m_size + 1];
        if(curr->m_next->m_next)
            curr->m_next->m_next->m_prev = curr;
        curr->m_size += 1 + curr->m_next->m_size;
        curr->m_next = curr->m_next->m_next;
        Fill((char *)free_start, (char *)free_end, MM_PATTERN_FREE);        
    }
    if(node->m_prev)
    {
        curr = node->m_prev;
        next = &curr[curr->m_size + 1];
        if(curr->m_next == next)
        {
            MemStruct* free_start = &curr[curr->m_size + 1];
            MemStruct* free_end = &free_start[1];
            if(curr->m_next->m_next)
                curr->m_next->m_next->m_prev = curr;
            curr->m_size += 1 + curr->m_next->m_size;
            curr->m_next = curr->m_next->m_next;
            Fill((char *)free_start, (char *)free_end, MM_PATTERN_FREE);
            ret = curr;
        }
    }
    return ret;
}

/*****************************************************************************
* Function Name: Fill
* Params:
*    char * start   -   Starting address
*    char * end     -   Ending address
*    char * pattern -   String pointer to fill pattern
* Returns:
*    void
* Discription:
*    Fills in the memory from [start] to [end] with the string [pattern]. If it
*    reaches the end of the [pattern] before it gets to [end], it resets
*    [pattern] and keeps writting.
*****************************************************************************/
void Fill (char * start, char * end, char * pattern)
{
    char * t_address = 0;
    int i = 0;

    for (t_address = start; t_address < end; t_address++)
    {
        if (pattern[i] == 0)
            i = 0;

        *t_address = pattern[i++];
    }
}