/* CML12SDP256 Serial I/O definitions */

#ifndef _M68HC12_SERIO_DEF_H
#define _M68HC12_SERIO_DEF_H

// Constant Definitions
// --------------------
#define LF 10            /* line feed */
#define CR 13            /* carriage return */

//#define Eclock  24000000              // 24Mhz crystal clock frequency (NOICE)
#define Eclock  8000000               // 8Mhz crystal clock frequency (MON12)

// this board has a 4Mhz osc clock
#define CLKX    ((Eclock/1000000)/4) - 1  // pll enable for Eclock

// values for baud registers, based on clock frequency.
#define Baud115200 (Eclock/16)/115200
#define Baud57600  (Eclock/16)/57600
#define Baud38400  (Eclock/16)/38400
#define Baud19200  (Eclock/16)/19200
#define Baud9600   (Eclock/16)/9600

#define LF 10            /* line feed */
#define CR 13            /* carriage return */

// RAM Variables
// -------------
extern unsigned char   ioport;         // 0 = use SC0 for standard i/o.  1 = use SC1


// Function Prototypes
// -------------------
char ReadyToSend(char portnum);
char putchar(unsigned char scbyte);
void putch(unsigned char ch);
void puts(char *sptr);
void InitSerial(unsigned char baudrate);



#endif /* _M68HC12_SERIO_DEF_H */
