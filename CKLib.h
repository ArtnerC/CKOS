/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: CKLib.h - CKOS Library
*****************************************************************************/

#ifndef CKLIB_H
#define CKLIB_H

#define CKOS_VERSION    "5.0"
#define CKOS_STAGE      "5 - Preemptive Multitasking"

//Typedefs and Macros
typedef enum { FALSE, TRUE } BOOL; //Boolean enum
#define _PTR(off)    (unsigned char *)(off) //Convert hex to PTR
#define _INC_PTR(ptr) (ptr += 0x0001) //Increment PTR
typedef unsigned char *    PTR; //Pointer typedef
//typedef unsigned short int    PTR; //Pointer typedef
typedef unsigned char    UCHAR; //Single byte typedef

//Error Vars
extern char CKLIB_ERROR[255];
extern BOOL CKLIB_EFLAG;

//CKLib Functions
void Memcpy (unsigned char * m_From, unsigned char * m_To, int Length);
void Strcpy (unsigned char * m_From, unsigned char * m_To);
int Strcmp(unsigned char * string1, unsigned char * string2);
int SStrcmp(unsigned char * string1, char * string2);
void AtoH (unsigned char * string, unsigned char * hex);
void PtoX(char * str, const unsigned char * ptr);
void CtoX(char * str, const UCHAR c);
char * UCtoC(unsigned char * uc);
unsigned char * CtoUC(char * c);
void SetError(char * err);
char * GetLastError();

#endif    /* CKLIB_H */
