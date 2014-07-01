/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: Console.h - CKOS Shell Console
*****************************************************************************/

#ifndef CKOS_CONSOLE
#define CKOS_CONSOLE

//Maximum buffer size
#define C_BUFFER_MAX 128

//Console Functions
void InitConsole();
void RunConsole();
char RunCommand(unsigned char * buffer);
void SplitCommand(unsigned char * src, unsigned char * cmd, unsigned char * args);
void GetLine(unsigned char * buffer);
char GetChar();

#endif /* CKOS_CONSOLE */
