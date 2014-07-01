/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: Console.c - CKOS Shell Console
*****************************************************************************/

#include "serial.h"
#include "ports_d256.h"
#include "CKLib.h"
#include "Console.h"
#include "Threads.h"
#include "MemMgr.h"

//MemMgr Test Variables
char * point = 0;
char * point2 = 0;
char * point3 = 0;

/*****************************************************************************
* Function Name: InitConsole
* Params:
*    void
* Returns:
*    void
* Discription:
*    Initializes CKOS console and displays version info
*****************************************************************************/
void InitConsole()
{
    puts("\n\nCKOS Version ");
    puts(CKOS_VERSION);
    puts("\n");
    puts("Stage: ");
    puts(CKOS_STAGE);
    puts("\n");
}

/*****************************************************************************
* Function Name: RunConsole
* Params:
*    void
* Returns:
*    void
* Discription:
*    Prompts user for input and runs commands
*****************************************************************************/
void RunConsole()
{
    BOOL run = TRUE;
    unsigned char buffer[C_BUFFER_MAX];
    
    while(1)
    {
        //Display Prompt
        puts("\n[CKOS]: ");
        
        //Get input string
        GetLine(buffer);
        
        puts("\n");

        //Run command
        if(RunCommand(buffer))
            run = FALSE;

        //Yield();
    }
}

/*****************************************************************************
* Function Name: Run
* Params:
*    char * buffer    - Command string entered by user
* Returns:
*    char    - TRUE if the user signaled to close the console, FALSE otherwise
* Discription:
*    Runs the command string entered by the user
*****************************************************************************/
char RunCommand(unsigned char * buffer)
{
    unsigned char cmd[C_BUFFER_MAX] = "";
    unsigned char args[C_BUFFER_MAX] = "";
    
    //Split the entered string into command and argument strings
    SplitCommand(buffer, cmd, args);
    
    //Checks for known commands
    if(!SStrcmp(cmd, "help"))
    {
        puts("[Console Commands]\n");
        puts("hello         - HELLO WORLD!\n");
        puts("echo [string] - Prints [string] back.\n");
        puts("memdump       - Shows all memory.\n");
        puts("malloc [1-3]  - Allocate memory and show dump\n");
        puts("memset [1-3]  - Sets allocated memory\n");
        puts("free [1-3]    - Free memory and show dump\n");
        puts("end           - Terminates the console.\n");
    }
    else if(!SStrcmp(cmd, "hello"))
    {
        puts("HELLO WORLD!\n");
    }
    else if(!SStrcmp(cmd, "echo"))
    {
        puts(UCtoC(args));
        putch('\n');
    }
    else if(!SStrcmp(cmd, "memdump"))
    {
        MemDump(0, 16);
    }
    else if(!SStrcmp(cmd, "malloc"))
    {
        if(!SStrcmp(args, "1"))
            point = Malloc(8);
        else if(!SStrcmp(args, "2"))
            point2 = Malloc(11);
        else if(!SStrcmp(args, "3"))
            point3 = Malloc(16);

        MemDump(0, 16);
    }
    else if(!SStrcmp(cmd, "free"))
    {
        if(!SStrcmp(args, "1"))
            Free(point);
        else if(!SStrcmp(args, "2"))
            Free(point2);
        else if(!SStrcmp(args, "3"))
            Free(point3);
            
        MemDump(0, 16);
    }
    else if(!SStrcmp(cmd, "memset"))
    {
        if(!SStrcmp(args, "1"))
            Strcpy("8 Bytes", point);
        else if(!SStrcmp(args, "2"))
            Strcpy("11Bytes", point2);
        else if(!SStrcmp(args, "3"))
            Strcpy("16Bytes", point3);

        MemDump(0, 16);
    }
    else if(!SStrcmp(cmd, "end"))
    {
        return TRUE;
    }
    else
    {
        puts("Unknown Command - Type 'help' for a list of commands\n");
    }
    
    return FALSE;
}

/*****************************************************************************
* Function Name: SplitCommand
* Params:
*    char * src    -    Source command string
*    char * cmd    -    String to store the command string
*    char * args    -    String to store the argument string
* Returns:
*    void
* Discription:
*    Puts everything before the first space in [cmd] and everything after in [args]
*****************************************************************************/
void SplitCommand(unsigned char * src, unsigned char * cmd, unsigned char * args)
{
    int i;
    for(i = 0; src[i]; i++)
    {
        if(src[i] == ' ')
        {
            int j;
            i++;
            for(j = 0; src[i]; i++, j++)
            {
                args[j] = src[i];
                args[j + 1] = '\0';
            }
        }
        else
        {
            cmd[i] = src[i];
            cmd[i + 1] = '\0';
        }
    }
}

/*****************************************************************************
* Function Name: GetLine
* Params:
*    char * buffer    -    Buffer to store user input
* Returns:
*    void
* Discription:
*    Waits for user input which it displays to console and adds to buffer
*****************************************************************************/
void GetLine(unsigned char * buffer)
{
    int i = 0;
    while(i < (C_BUFFER_MAX - 1))
    {
        //Wait for input character
        char tmp = GetChar();
        
        //Check input character
        switch(tmp)
        {
        case '\n':
        case '\r':
            buffer[i] = '\0';
            putch('\n');
            return;
            
        case '\b':
            if(i > 0)
            {
                i--;
                putch(tmp);
            }
            buffer[i] = '\0';
            break;

        default:
            buffer[i] = tmp;
            buffer[i + 1] = '\0';
            putch(tmp);
            i++;
            break;
        }        
    }
    buffer[C_BUFFER_MAX - 1] = '\0';
    putch('\n');
}

/*****************************************************************************
* Function Name: GetChar
* Params:
*    void
* Returns:
*    char    - A single user entered char
* Discription:
*    Waits for user input to be ready and returns entered character
*****************************************************************************/
char GetChar()
{
    while(!(SC0SR1 & 0x20));
    return SC0DRL;
}
