/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: MemMgr.h - CKOS Memory Manager
*****************************************************************************/

#ifndef CKOS_MEMMGR
#define CKOS_MEMMGR

//Heap Settings
#define MM_HEAP_START    _PTR(0x9000)
#define MM_HEAP_END      _PTR(0xBFFF)
#define MM_BLOCK_SIZE    8

//Block Fill Patterns
#define MM_PATTERN_INIT    "I-N-I-T-" //0x 49 2D 4E 2D 49 2D 54 2D
#define MM_PATTERN_ALLOC   "A-L-O-C-" //0x 41 2D 4C 2D 4F 2D 43 2D
#define MM_PATTERN_FREE    "F-R-E-E-" //0x 46 2D 52 2D 45 2D 45 2D

//Define Memory Struct Node
typedef struct MemStructNode
{
    int m_size;
    char * m_void;
    struct MemStructNode * m_next;
    struct MemStructNode * m_prev;
} MemStruct;

//Memory Lists
extern MemStruct* MM_FREE_LIST;     //Free Mem List
extern MemStruct* MM_ALLOC_LIST;    //Allocated Mem List

//Memory Manager Functions
void InitMemMgr();
void MemDump(char * start, int len);
void Insert(MemStruct** list, MemStruct* node);
void Remove(MemStruct** list, MemStruct* node);
MemStruct* SplitMem(MemStruct* node, unsigned char size);
MemStruct* ContigMem(MemStruct* node);
char * Malloc(int size);
void Free (char * ptr);
void Fill (char * start, char * stop, char * pattern);

#endif /* CKOS_MEMMGR */
