/*****************************************************************************
* Project Name: CKOS
* Authors: Casey Artner & Kenny Deardorff
* Class: CST 352 - Operating Systems
* File: CKLib.c - CKOS Library
*****************************************************************************/

#include "CKLib.h"

//Error Vars
char CKLIB_ERROR[255] = { "" };
BOOL CKLIB_EFLAG = FALSE;

/*****************************************************************************
* Function Name: Memcpy
* Params:
*    void * m_From  - Address to copy from
*    void * m_To    - Address to copy to
*    int Length     - Length in bytes to copy
* Returns:
*    void
* Discription:
*    Copies a piece of memory from [m_From] to [m_To].
*****************************************************************************/
void Memcpy (unsigned char * m_From, unsigned char * m_To, int Length)
{
    int i = 0;
    for (i = 0; i < Length; i++)
    {
        m_To[i] = m_From[i];
    }
}

/*****************************************************************************
* Function Name: Strcpy
* Params:
*    void * m_From  - Address to copy from
*    void * m_To    - Address to copy to
* Returns:
*    void
* Discription:
*    Copies a null terminated string from [m_From] to [m_To].
*****************************************************************************/
void Strcpy (unsigned char * m_From, unsigned char * m_To)
{
    int i = 0;

    while ( m_From[i] != 0 )
    {
        m_To[i] = m_From[i];
        ++i;
    }
}

/*****************************************************************************
* Function Name: Strcmp
* Params:
*    char * string1    - String 1
*    char * string2    - String 2
* Returns:
*    int             - 1 means string 1 comes before string 2
*                    - -1 means string 2 comes before string 1
*                    - 0 means string 1 is the same as string 2
* Discription:
*    Compairs two strings to see if they are the same. Returns the
*    coresponding integer.
*****************************************************************************/
int Strcmp(unsigned char * string1, unsigned char * string2)
{
    while(1)
    {
        if ((*string1 == 0) && (*string2 == 0))
            return 0;

        if (*string1 == 0)
            return 2;

        if (*string2 == 0)
            return -2;

        if (*string1 > *string2)
            return -1;

        if (*string1 < *string2)
            return 1;

        ++string1;
        ++string2;
    }
}

/*****************************************************************************
* Function Name: SStrcmp
* Discription:
*    Overload for Strcmp
*****************************************************************************/
int SStrcmp(unsigned char * string1, char * string2)
{
    return Strcmp(string1, (unsigned char *)string2);
}

//Version by Casey
//int Strcmp(PTR dest, PTR src)
//{
//    int i = 0;
//    while(dest[i] || src[i])
//    {
//        if(dest[i] > src[i])
//            return -1;
//        if(dest[i] < src[i])
//            return 1;
//        i++;
//    }
//    return 0;
//}

/*****************************************************************************
* Function Name: AtoH
* Params:
*    unsigned char * string     - ASCII string
*    unsigned char * hex        - Hex string
* Returns:
*    void
* Discription:
*    Converts an ASCII null-terminated string into a hex string. [hex] should
*    be 1/2 as long or greater than the ASCII string. 
*****************************************************************************/
void AtoH (unsigned char * string, unsigned char * hex)
{
    int i = 0;        //index
    char b = 0;        //buffer

    while (string[i] != 0)
    {
        if ((string[i] >= '0') &&
            (string[i] <= '9'))
        {
            b = string[i] - '0';        //convert ASCII to hex
        }

        else if ((string[i] >= 'A') &&
                 (string[i] <= 'F'))
        {
            b = string[i] - 'A' + 10;    //convert ASCII to hex
        }
        
        b <<= 4;    //shift hex value over
        ++i;

        if ((string[i] >= '0') &&
            (string[i] <= '9'))
        {
            b = b | (string[i] - '0');        //convert ASCII to hex and OR the two values together
        }

        else if ((string[i] >= 'A') &&
                 (string[i] <= 'F'))
        {
            b = b | (string[i] - 'A' + 10);    //convert ASCII to hex and OR the two values together
        }

        hex[(i - 1) / 2] = b;    //add buffer to string
        ++i;
    }
    
    hex[(i + 1) / 2] = 0;        //null terminate string
}

/*****************************************************************************
* Function Name: PtoX
* Params:
*    str    - Char array for string storage
*    ptr    - Pointer to be converted
* Returns:
*    void
* Discription:
*    Converts [ptr] to a hex string [str] (0xXXXX)
*****************************************************************************/
void PtoX(char * str, const unsigned char * ptr)
{
    unsigned int buffer = (unsigned int)ptr;
    int pos = 3;
    char lookup[] = "0123456789ABCDEF";
    
    Strcpy(CtoUC(str), (unsigned char *)"0000");
    
    while (pos != -1)
    {
        str[pos--] = lookup[buffer & 0x0000000F];
        buffer >>= 4;
    }
    
    str[4] = 0;
}

/*****************************************************************************
* Function Name: CtoX
* Params:
*    str    - Char array for string storage
*    c      - Character to be converted
* Returns:
*    void
* Discription:
*    Converts an unsigned char [c] to a hex string [str] (0xXX)
*****************************************************************************/
void CtoX(char * str, const unsigned char c)
{
    char lookup[] = { "0123456789ABCDEF" };
    unsigned char ch = 0;

    ch = (c & 0xF0);
    ch = (ch >> 4);
    str[0] = lookup[ch];

    ch = (c & 0x0F);
    str[1] = lookup[ch];

    str[2] = 0;
}

/*****************************************************************************
* Function Name: UCtoC
* Params:
*    uc     - unsigned character pointer
* Returns:
*    character pointer
* Discription:
*    Easy/Lazy typecasting from unsigned char * to char *
*****************************************************************************/
char * UCtoC(unsigned char * uc)
{
    return (char *)uc;
}

/*****************************************************************************
* Function Name: CtoUC
* Params:
*    c      - character pointer
* Returns:
*    unsigned character pointer
* Discription:
*    Easy/Lazy typecasting from char * to unsigned char *
*****************************************************************************/
unsigned char * CtoUC(char * c)
{
    return (unsigned char *)c;
}

/*****************************************************************************
* Function Name: SetError
* Params:
*    err    - String containing error message
* Returns:
*    void
* Discription:
*    Sets the current system error and prints it
*****************************************************************************/
void SetError(char * err)
{
    CKLIB_EFLAG = TRUE;
    Strcpy((unsigned char *)err, (unsigned char *)CKLIB_ERROR);
    puts("[System Error] - ");
    puts(CKLIB_ERROR);
    puts("\n");
}

/*****************************************************************************
* Function Name: GetLastError
* Params:
*    void
* Returns:
*    char * containing last system error message
* Discription:
*    Returns the last system error message set
*****************************************************************************/
char * GetLastError()
{
    if(CKLIB_EFLAG == TRUE)
    {
        CKLIB_EFLAG = FALSE;
        return CKLIB_ERROR;
    }
    
    return 0;
}
