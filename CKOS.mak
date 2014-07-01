OC = Z:/usr/bin/m6811-elf-objcopy
CC = Z:/usr/bin/m6811-elf-gcc
RM = Z:/egnu110/rm.exe

CFLAGS  = -m68hc12 -Os -fno-ident -fno-common -mshort -fsigned-char
LDFLAGS = -Wl,-u,-mm68hc12elfb
OCFLAGS = -O srec

CSRCS=serial.c Main.c Console.c MemMgr.c CKLib.c Threads.c Scheduler.c

OBJS=$(CSRCS:.c=.o)

all:	CKOS.elf CKOS.s19

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $<

CKOS.elf:	$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o CKOS.elf $(OBJS) -lgcc -lc

CKOS.s19:	CKOS.elf
	$(OC) $(OCFLAGS) CKOS.elf CKOS.s19

clean:
	$(RM) -f CKOS.elf
	$(RM) -f CKOS.s19
	$(RM) -f CKOS.dmp
	$(RM) -f $(OBJS)
