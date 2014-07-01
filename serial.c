/* ===========================================================================

    serial.c  - serial com port I/O routines for Axiom CML12SDP256 board

    Version:        1.0
    Author:         Dusty Nidey, Axiom Manufacturing (www.axman.com)
    Compiler:       GNU for 68HC11 & 68HC12 (www.gnu-m68hc11.org)

    This is freeware - use as you like

==============================================================================
------------------------------------------------------------------------------
*/

#include "ports_d256.h"
#include "serial.h"


// RAM Variables
// -------------
unsigned char   ioport;         // 0 = use SC0 for standard i/o.  1 = use SC1


//---------------------------------------------------------------------------
// Initialize serial port
void InitSerial(unsigned char baudrate){
    SC0BDL = baudrate;  // set baud rate register
    SC0BDH = 0x00;
    SC0CR1 = 0;     // configure SCI0 control registers
    SC0CR2 = 0x0C;  // enable transmit and receive
}

/*----------------------------------------------------------------------------
ReadyToSend
-----------
 Wait for the serial port Status register to indicate the transmiter is
 ready to receive another byte.

 INPUT:     ioport      0= SCI0, 1= SCI1
 OUTPUT:    returns 0 when ready.  NO TIMEOUT is currently implemented
----------------------------------------------------------------------------*/
char ReadyToSend(char portnum){
    unsigned char Status;
    do{
        if(portnum == 0)    Status = SC0SR1;
        else                Status = SC1SR1;
    }while((Status & 0x80) == 0);
    return 0;
}

/*----------------------------------------------------------------------------
putchar
-------
 Wait for the serial port transmiter to return ready then write a single byte
 to the transmit register.

 INPUT:     SByte       Value to write
            ioport      0= SCI0, 1= SCI1
 OUTPUT:    returns 0 when finished.  NO TIMEOUT is currently implemented
----------------------------------------------------------------------------*/
char putchar(unsigned char scbyte){
    if(ReadyToSend(ioport)) return 1;   // wait for ready to send
    if(ioport == 0) SC0DRL = scbyte;
    else            SC1DRL = scbyte;
    return 0;
}

/*----------------------------------------------------------------------------
putch
-----
 Send a single byte out the serial port.
 If this is the '\n' character then 2 bytes are sent which are the carriage
 return followed by line feed characters.

 INPUT:        ch            Value to write
            ioport      0= SCI0, 1= SCI1
----------------------------------------------------------------------------*/
void putch(unsigned char ch){
    if (ch == '\n'){
        putchar(CR);
        putchar(LF);
    }
    else{
        putchar(ch);
    }
}

/*----------------------------------------------------------------------------
puts
----
 Send a string of characters to the serial port.  The string must end in a
 NULL character (0x00).

 INPUT:        sptr        pointer to the string
            ioport      0= SCI0, 1= SCI1
----------------------------------------------------------------------------*/
void puts(char *sptr){
    while(*sptr){
        putch(*sptr);
        ++sptr;
    }
}


