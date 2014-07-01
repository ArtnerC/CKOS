/* CML12SDP256 I/O Port definitions */

#ifndef _M68HC12_PORTS_DEF_H
#define _M68HC12_PORTS_DEF_H

#define REGBS      0x0000    //  DP256 register bank base address

#define _P(off)         *(unsigned char volatile *)(REGBS + off)
#define _LP(off)        *(unsigned short volatile *)(REGBS + off)

#define PORTA   _P(0x00) // port A = Address lines A8 - A15

#define PORTB      _P(0x01) // port B = Address lines A0 - A7
#define DDRA       _P(0x02) // port A direction register
#define DDRB       _P(0x03) // port A direction register

#define PORTE      _P(0x08) // port E = mode,IRQandcontrolsignals
#define DDRE       _P(0x09) // port E direction register
#define PEAR       _P(0x0A) // port E assignments
#define MODE       _P(0x0B) // Mode register
#define PUCR       _P(0x0C) // port pull-up control register
#define RDRIV      _P(0x0D) // port reduced drive control register
#define EBICTL     _P(0x0E) // E stretch control

#define INITRM     _P(0x10) // Ram location register
#define INITRG     _P(0x11) // Register location register
#define INITEE     _P(0x12) // EEprom location register
#define MISC       _P(0x13) // Miscellaneous Mapping control
#define MTST0      _P(0x14) //  RESERVED
#define ITCR       _P(0x15) // Interrupt test control register
#define ITEST      _P(0x16) // Interrupt test register
#define MTST1      _P(0x17) //  Reserved

#define PARTIDH    _P(0x1A) // Part ID high
#define PARTIDL    _P(0x1B) // Part ID low
#define MEMSIZ0    _P(0x1C) // memory size
#define MEMSIZ1    _P(0x1D) // memory size
#define INTCR      _P(0x1E) // interrupt control register
#define HPRIO      _P(0x1F) // high priority reg

#define BKPCT0     _P(0x28) // Break control register
#define BKPCT1     _P(0x29) // Break control register
#define BKP0X      _P(0x2A) // Break 0 index register
#define BKP0H      _P(0x2B) // Break 0 pointer high
#define BRP0L      _P(0x2C) // Break 0 pointer low
#define BKP1X      _P(0x2D) // Break 1 index register
#define BKP1H      _P(0x2E) // Break 1 pointer high
#define BRP1L      _P(0x2F) // Break 1 pointer low
#define PPAGE      _P(0x30) // Program Page register

#define PORTK      _P(0x32) // Port K data
#define DDRK       _P(0x33) // Port K direction
#define SYNR       _P(0x34) // Synthesizer / multiplier register
#define REFDV      _P(0x35) // Reference divider register
#define CTFLG      _P(0x36) // RESERVED
#define CRGFLG     _P(0x37) // PLL flags register
#define CRGINT     _P(0x38) // PLL interrupt register
#define CLKSEL     _P(0x39) // Clock select register
#define PLLCTL     _P(0x3A) // PLL control register
#define RTICTL     _P(0x3B) // Real time interrupt control
#define COPCTL     _P(0x3C) // Watchdog control
#define FORBYP     _P(0x3D //
#define CTCTL      _P(0x3E //
#define ARMCOP     _P(0x3F) // COP reset register

#define TIOS       _P(0x40) // timer input/output select
#define CFORC      _P(0x41) // timer compare force
#define OC7M       _P(0x42) // timer output compare 7 mask
#define OC7D       _P(0x43) // timer output compare 7 data
#define TCNT      _LP(0x44) // timer counter register (2 bytes)
#define TSCR       _P(0x46) // timer system control register
#define TTOV       _P(0x47) // reserved
#define TCTL1      _P(0x48) // timer control register 1
#define TCTL2      _P(0x49) // timer control register 2
#define TCTL3      _P(0x4A) // timer control register 3
#define TCTL4      _P(0x4B) // timer control register 4
#define TMSK1      _P(0x4C) // timer interrupt mask 1 (TIE)
#define TMSK2      _P(0x4D) // timer interrupt mask 2 (TSCR2)
#define TFLG1      _P(0x4E) // timer flags 1
#define TFLG2      _P(0x4F) // timer flags 2
#define TC0       _LP(0x50) // timer capture/compare register 0
#define TC1       _LP(0x52) // timer capture/compare register 1
#define TC2       _LP(0x54) // timer capture/compare register 2
#define TC3       _LP(0x56) // timer capture/compare register 3
#define TC4       _LP(0x58) // timer capture/compare register 4
#define TC5       _LP(0x5A) // timer capture/compare register 5
#define TC6       _LP(0x5C) // timer capture/compare register 6
#define TC7       _LP(0x5E) // timer capture/compare register 7
#define PACTL      _P(0x60) // pulse accumulator controls
#define PAFLG      _P(0x61) // pulse accumulator flags
#define PACN3      _P(0x62) // pulse accumulator counter 3
#define PACN2      _P(0x63) // pulse accumulator counter 2
#define PACN1      _P(0x64) // pulse accumulator counter 1
#define PACN0      _P(0x65) // pulse accumulator counter 0
#define MCCTL      _P(0x66) // Modulus down conunter control
#define MCFLG      _P(0x67) // down counter flags
#define ICPAR      _P(0x68) // Input pulse accumulator control
#define DLYCT      _P(0x69) // Delay count to down counter
#define ICOVW      _P(0x6A) // Input control overwrite register
#define ICSYS      _P(0x6B) // Input control system control

#define TIMTST     _P(0x6D) // timer test register

#define PBCTL      _P(0x70) //  Pulse accumulator B control
#define PBFLG      _P(0x71) //  Pulse accumulator B flags
#define PA3H       _P(0x72) //  Pulse Accumulator holding register 3
#define PA2H       _P(0x73) //  Pulse Accumulator holding register 2
#define PA1H       _P(0x74) //  Pulse Accumulator holding register 1
#define PA0H       _P(0x75) //  Pulse Accumulator holding register 0
#define MCCNT     _LP(0x76) //  Modulus down counter register
#define TCOH       _P(0x78) //  Capture 0 holding register
#define TC1H       _P(0x7A) //  Capture 1 holding register
#define TC2H       _P(0x7C) //  Capture 2 holding register
#define TC3H       _P(0x7E) //  Capture 3 holding register

#define ATD0CTL0   _P(0x80) // ADC control 0 (reserved)
#define ATD0CTL1   _P(0x81) // ADC control 1 (reserved)
#define ATD0CTL2   _P(0x82) // ADC control 2
#define ATD0CTL3   _P(0x83) // ADC control 3
#define ATD0CTL4   _P(0x84) // ADC control 4
#define ATD0CTL5   _P(0x85) // ADC control 5
#define ATD0STAT  _LP(0x86) // ADC status register hi
#define ATD0TEST  _LP(0x88) // ADC test (reserved)

#define ATD0DIEN   _P(0x8D //

#define PORTAD     _P(0x8F) // port ADC = input only
#define ADR00H     _P(0x90) // ADC result 0 register
#define ADR01H     _P(0x92) // ADC result 1 register
#define ADR02H     _P(0x94) // ADC result 2 register
#define ADR03H     _P(0x96) // ADC result 3 register
#define ADR04H     _P(0x98) // ADC result 4 register
#define ADR05H     _P(0x9A) // ADC result 5 register
#define ADR06H     _P(0x9C) // ADC result 6 register
#define ADR07H     _P(0x9E) // ADC result 7 register

#define PWME       _P(0xA0) // PWM enable
#define PWMPOL     _P(0xA1) // PWM polarity
#define PWMCLK     _P(0xA2) // PWM clock select register
#define PWMPRCLK   _P(0xA3) // PWM Prescale clock select register
#define PWMCAE     _P(0xA4) // PWM center align select register
#define PWMCTL     _P(0xA5) // PWM control register
#define PWMTST     _P(0xA6) // reserved
#define PWMPRSC    _P(0xA7) // reserved
#define PWMSCLA    _P(0xA8) // PWM Scale A
#define PWMSCLB    _P(0xA9) // PWM scale B
#define PWMSCNTA   _P(0xAA) // reserved
#define PWMSCNTB   _P(0xAB) // reserved
#define PWMCNT0    _P(0xAC) // PWM channel 0 counter
#define PWMCNT1    _P(0xAD) // PWM channel 1 counter
#define PWMCNT2    _P(0xAE) // PWM channel 2 counter
#define PWMCNT3    _P(0xAF) // PWM channel 3 counter
#define PWMCNT4    _P(0xB0) // PWM channel 4 counter
#define PWMCNT5    _P(0xB1) // PWM channel 5 counter
#define PWMCNT6    _P(0xB2) // PWM channel 6 counter
#define PWMCNT7    _P(0xB3) // PWM channel 7 counter
#define PWMPER0    _P(0xB4) // PWM channel 0 period
#define PWMPER1    _P(0xB5) // PWM channel 1 period
#define PWMPER2    _P(0xB6) // PWM channel 2 period
#define PWMPER3    _P(0xB7) // PWM channel 3 period
#define PWMPER4    _P(0xB8) // PWM channel 4 period
#define PWMPER5    _P(0xB9) // PWM channel 5 period
#define PWMPER6    _P(0xBA) // PWM channel 6 period
#define PWMPER7    _P(0xBB) // PWM channel 7 period
#define PWMDTY0    _P(0xBC) // PWM channel 0 duty cycle
#define PWMDTY1    _P(0xBD) // PWM channel 1 duty cycle
#define PWMDTY2    _P(0xBE) // PWM channel 2 duty cycle
#define PWMDTY3    _P(0xBF) // PWM channel 3 duty cycle
#define PWMDTY4    _P(0xC0) // PWM channel 0 duty cycle
#define PWMDTY5    _P(0xC1) // PWM channel 1 duty cycle
#define PWMDTY6    _P(0xC2) // PWM channel 2 duty cycle
#define PWMDTY7    _P(0xC3) // PWM channel 3 duty cycle
#define PWMSDN     _P(0xC4) // PWM shutdown register

#define SC0BDH     _P(0xC8) // sci 0 baud reg hi byte
#define SC0BDL     _P(0xC9) // sci 0 baud reg lo byte
#define SC0CR1     _P(0xCA) // sci 0 control1 reg
#define SC0CR2     _P(0xCB) // sci 0 control2 reg
#define SC0SR1     _P(0xCC) // sci 0 status reg 1
#define SC0SR2     _P(0xCD) // sci 0 status reg 2
#define SC0DRH     _P(0xCE) // sci 0 data reg hi
#define SC0DRL     _P(0xCF) // sci 0 data reg lo
#define SC1BDH     _P(0xDO) // sci 1 baud reg hi byte
#define SC1BDL     _P(0xD1) // sci 1 baud reg lo byte
#define SC1CR1     _P(0xD2) // sci 1 control1 reg
#define SC1CR2     _P(0xD3) // sci 1 control2 reg
#define SC1SR1     _P(0xD4) // sci 1 status reg 1
#define SC1SR2     _P(0xD5) // sci 1 status reg 2
#define SC1DRH     _P(0xD6) // sci 1 data reg hi
#define SC1DRL     _P(0xD7) // sci 1 data reg lo
#define SPI0CR1    _P(0xD8) // spi 0 control1 reg
#define SPI0CR2    _P(0xD9) // spi 0 control2 reg
#define SPI0BR     _P(0xDA) // spi 0 baud reg
#define SPI0SR     _P(0xDB) // spi 0 status reg hi

#define SP0DR      _P(0xDD) // spi 0 data reg

#define IBAD       _P(0xE0) // I2C Bus address register
#define IBFD       _P(0xE1) // I2C Bus frequency divider
#define IBCR       _P(0xE2) // I2C Bus control register
#define IBSR       _P(0xE3) // I2C Bus status register
#define IBDR       _P(0xE4) // I2C Bus message data register

#define DLCBCR1    _P(0xE8) // BDLC Control regsiter 1
#define DLCBSVR    _P(0xE9) // BDLC State vector register
#define DLCBCR2    _P(0xEA) // BDLC Control register 2
#define DLCBDR     _P(0xEB) // BDLC Data register
#define DLCBARD    _P(0xEC) // BDLC Analog delay register
#define DLCBRSR    _P(0xED) // BDLC Rate select register
#define DLCSCR     _P(0xEE) // BDLC Control register
#define DLCBSTAT   _P(0xEF) // BDLC Status register
#define SPI1CR1    _P(0xF0) // spi 1 control1 reg
#define SPI1CR2    _P(0xF1) // spi 1 control2 reg
#define SPI1BR     _P(0xF2) // spi 1 baud reg
#define SPI1SR     _P(0xF3) // spi 1 status reg hi

#define SP1DR      _P(0xF5) // spi 1 data reg

#define SPI2CR1    _P(0xF8) // spi 2 control1 reg
#define SPI2CR2    _P(0xF9) // spi 2 control2 reg
#define SPI2BR     _P(0xFA) // spi 2 baud reg
#define SPI2SR     _P(0xFB) // spi 2 status reg hi

#define SP2DR      _P(0xFD) // spi 2 data reg

#define FCLKDIV    _P(0x100) // FLASH clock divider
#define FSEC       _P(0x101) // FLASH security register

#define FCNFG      _P(0x103) // FLASH configuration register
#define FPROT      _P(0x104) // FLASH protection register
#define FSTAT      _P(0x105) // FLASH status register
#define FCMD       _P(0x106) // FLASH command register

#define ECLKDIV    _P(0x110) // EEPROM clock divider

#define ECNFG      _P(0x113) // EEPROM configuration register
#define EPROT      _P(0x114) // EEPROM protection register
#define ESTAT      _P(0x115) // EEPROM status register
#define ECMD       _P(0x116) // EEPROM command register

#define ATD1CTL0   _P(0x120) // ADC1 control 0 (reserved)
#define ATD1CTL1   _P(0x121) // ADC1 control 1 (reserved)
#define ATD1CTL2   _P(0x122) // ADC1 control 2
#define ATD1CTL3   _P(0x123) // ADC1 control 3
#define ATD1CTL4   _P(0x124) // ADC1 control 4
#define ATD1CTL5   _P(0x125) // ADC1 control 5
#define ATD1STAT  _LP(0x126) // ADC1 status register hi
#define ATD1TEST  _LP(0x128) // ADC1 test (reserved)

#define ATDDIEN    _P(0x12D) // ADC1 INPUT ENABLE REGISTER

#define PORTAD1    _P(0x12F) // port ADC1 = input only
#define ADR10H     _P(0x130) // ADC1 result 0 register
#define ADR11H     _P(0x132) // ADC1 result 1 register
#define ADR12H     _P(0x134) // ADC1 result 2 register
#define ADR13H     _P(0x136) // ADC1 result 3 register
#define ADR14H     _P(0x138) // ADC1 result 4 register
#define ADR15H     _P(0x13A) // ADC1 result 5 register
#define ADR16H     _P(0x13C) // ADC1 result 6 register
#define ADR17H     _P(0x13E) // ADC1 result 7 register
#define CAN0CTL0   _P(0x140) // CAN0 control register 0
#define CAN0CTL1   _P(0x141) // CAN0 control register 1
#define CAN0BTR0   _P(0x142) // CAN0 bus timing register 0
#define CAN0BTR1   _P(0x143) // CAN0 bus timing register 1
#define CAN0RFLG   _P(0x144) // CAN0 receiver flags
#define CAN0RIER   _P(0x145) // CAN0 receiver interrupt enables
#define CAN0TFLG   _P(0x146) // CAN0 transmit flags
#define CAN0TIER   _P(0x147) // CAN0 transmit interrupt enables
#define CAN0TARQ   _P(0x148) // CAN0 transmit message abort control
#define CAN0TAAK   _P(0x149) // CAN0 transmit message abort status
#define CAN0TBEL   _P(0x14A) // CAN0 transmit buffer select
#define CAN0IDAC   _P(0x14B) // CAN0 identfier acceptance control

#define CAN0RERR   _P(0x14E) // CAN0 Receive error counter
#define CAN0TERR   _P(0x14F) // CAN0 Transmit error counter
#define CAN0IDA0   _P(0x150) // CAN0 Identifier acceptance register 0
#define CAN0IDA1   _P(0x151) // CAN0 Identifier acceptance register 1
#define CAN0IDA2   _P(0x152) // CAN0 Identifier acceptance register 2
#define CAN0IDA3   _P(0x153) // CAN0 Identifier acceptance register 3
#define CAN0IDM0   _P(0x154) // CAN0 Identifier mask register 0
#define CAN0IDM1   _P(0x155) // CAN0 Identifier mask register 1
#define CAN0IDM2   _P(0x156) // CAN0 Identifier mask register 2
#define CAN0IDM3   _P(0x157) // CAN0 Identifier mask register 3
#define CAN0IDA4   _P(0x158) // CAN0 Identifier acceptance register 4
#define CAN0IDA5   _P(0x159) // CAN0 Identifier acceptance register 5
#define CAN0IDA6   _P(0x15A) // CAN0 Identifier acceptance register 6
#define CAN0IDA7   _P(0x15B) // CAN0 Identifier acceptance register 7
#define CAN0IDM4   _P(0x15C) // CAN0 Identifier mask register 4
#define CAN0IDM5   _P(0x15D) // CAN0 Identifier mask register 5
#define CAN0IDM6   _P(0x15E) // CAN0 Identifier mask register 6
#define CAN0IDM7   _P(0x15F) // CAN0 Identifier mask register 7
#define CAN0RXFG   _P(0x160) // CAN0 RX foreground buffer thru +0x16F
#define CAN0TXFG   _P(0x170) // CAN0 TX foreground buffer thru +0x17F

#define CAN1CTL0   _P(0x180) // CAN1 control register 0
#define CAN1CTL1   _P(0x181) // CAN1 control register 1
#define CAN1BTR0   _P(0x182) // CAN1 bus timing register 0
#define CAN1BTR1   _P(0x183) // CAN1 bus timing register 1
#define CAN1RFLG   _P(0x184) // CAN1 receiver flags
#define CAN1RIER   _P(0x185) // CAN1 receiver interrupt enables
#define CAN1TFLG   _P(0x186) // CAN1 transmit flags
#define CAN1TIER   _P(0x187) // CAN1 transmit interrupt enables
#define CAN1TARQ   _P(0x188) // CAN1 transmit message abort control
#define CAN1TAAK   _P(0x189) // CAN1 transmit message abort status
#define CAN1TBEL   _P(0x18A) // CAN1 transmit buffer select
#define CAN1IDAC   _P(0x18B) // CAN1 identfier acceptance control

#define CAN1RERR   _P(0x18E) // CAN1 Receive error counter
#define CAN1TERR   _P(0x18F) // CAN1 Transmit error counter
#define CAN1IDA0   _P(0x190) // CAN1 Identifier acceptance register 0
#define CAN1IDA1   _P(0x191) // CAN1 Identifier acceptance register 1
#define CAN1IDA2   _P(0x192) // CAN1 Identifier acceptance register 2
#define CAN1IDA3   _P(0x193) // CAN1 Identifier acceptance register 3
#define CAN1IDM0   _P(0x194) // CAN1 Identifier mask register 0
#define CAN1IDM1   _P(0x195) // CAN1 Identifier mask register 1
#define CAN1IDM2   _P(0x196) // CAN1 Identifier mask register 2
#define CAN1IDM3   _P(0x197) // CAN1 Identifier mask register 3
#define CAN1IDA4   _P(0x198) // CAN1 Identifier acceptance register 4
#define CAN1IDA5   _P(0x199) // CAN1 Identifier acceptance register 5
#define CAN1IDA6   _P(0x19A) // CAN1 Identifier acceptance register 6
#define CAN1IDA7   _P(0x19B) // CAN1 Identifier acceptance register 7
#define CAN1IDM4   _P(0x19C) // CAN1 Identifier mask register 4
#define CAN1IDM5   _P(0x19D) // CAN1 Identifier mask register 5
#define CAN1IDM6   _P(0x19E) // CAN1 Identifier mask register 6
#define CAN1IDM7   _P(0x19F) // CAN1 Identifier mask register 7
#define CAN1RXFG   _P(0x1A0) // CAN1 RX foreground buffer thru +0x1AF
#define CAN1TXFG   _P(0x1B0) // CAN1 TX foreground buffer thru +0x1BF

#define CAN2CTL0   _P(0x1C0) // CAN2 control register 0
#define CAN2CTL1   _P(0x1C1) // CAN2 control register 1
#define CAN2BTR0   _P(0x1C2) // CAN2 bus timing register 0
#define CAN2BTR1   _P(0x1C3) // CAN2 bus timing register 1
#define CAN2RFLG   _P(0x1C4) // CAN2 receiver flags
#define CAN2RIER   _P(0x1C5) // CAN2 receiver interrupt enables
#define CAN2TFLG   _P(0x1C6) // CAN2 transmit flags
#define CAN2TIER   _P(0x1C7) // CAN2 transmit interrupt enables
#define CAN2TARQ   _P(0x1C8) // CAN2 transmit message abort control
#define CAN2TAAK   _P(0x1C9) // CAN2 transmit message abort status
#define CAN2TBEL   _P(0x1CA) // CAN2 transmit buffer select
#define CAN2IDAC   _P(0x1CB) // CAN2 identfier acceptance control

#define CAN2RERR   _P(0x1CE) // CAN2 Receive error counter
#define CAN2TERR   _P(0x1CF) // CAN2 Transmit error counter
#define CAN2IDA0   _P(0x1D0) // CAN2 Identifier acceptance register 0
#define CAN2IDA1   _P(0x1D1) // CAN2 Identifier acceptance register 1
#define CAN2IDA2   _P(0x1D2) // CAN2 Identifier acceptance register 2
#define CAN2IDA3   _P(0x1D3) // CAN2 Identifier acceptance register 3
#define CAN2IDM0   _P(0x1D4) // CAN2 Identifier mask register 0
#define CAN2IDM1   _P(0x1D5) // CAN2 Identifier mask register 1
#define CAN2IDM2   _P(0x1D6) // CAN2 Identifier mask register 2
#define CAN2IDM3   _P(0x1D7) // CAN2 Identifier mask register 3
#define CAN2IDA4   _P(0x1D8) // CAN2 Identifier acceptance register 4
#define CAN2IDA5   _P(0x1D9) // CAN2 Identifier acceptance register 5
#define CAN2IDA6   _P(0x1DA) // CAN2 Identifier acceptance register 6
#define CAN2IDA7   _P(0x1DB) // CAN2 Identifier acceptance register 7
#define CAN2IDM4   _P(0x1DC) // CAN2 Identifier mask register 4
#define CAN2IDM5   _P(0x1DD) // CAN2 Identifier mask register 5
#define CAN2IDM6   _P(0x1DE) // CAN2 Identifier mask register 6
#define CAN2IDM7   _P(0x1DF) // CAN2 Identifier mask register 7
#define CAN2RXFG   _P(0x1E0) // CAN2 RX foreground buffer thru +0x1EF
#define CAN2TXFG   _P(0x1F0) // CAN2 TX foreground buffer thru +0x1FF

#define CAN3CTL0   _P(0x200) // CAN3 control register 0
#define CAN3CTL1   _P(0x201) // CAN3 control register 1
#define CAN3BTR0   _P(0x202) // CAN3 bus timing register 0
#define CAN3BTR1   _P(0x203) // CAN3 bus timing register 1
#define CAN3RFLG   _P(0x204) // CAN3 receiver flags
#define CAN3RIER   _P(0x205) // CAN3 receiver interrupt enables
#define CAN3TFLG   _P(0x206) // CAN3 transmit flags
#define CAN3TIER   _P(0x207) // CAN3 transmit interrupt enables
#define CAN3TARQ   _P(0x208) // CAN3 transmit message abort control
#define CAN3TAAK   _P(0x209) // CAN3 transmit message abort status
#define CAN3TBEL   _P(0x20A) // CAN3 transmit buffer select
#define CAN3IDAC   _P(0x20B) // CAN3 identfier acceptance control

#define CAN3RERR   _P(0x20E) // CAN3 Receive error counter
#define CAN3TERR   _P(0x20F) // CAN3 Transmit error counter
#define CAN3IDA0   _P(0x210) // CAN3 Identifier acceptance register 0
#define CAN3IDA1   _P(0x211) // CAN3 Identifier acceptance register 1
#define CAN3IDA2   _P(0x212) // CAN3 Identifier acceptance register 2
#define CAN3IDA3   _P(0x213) // CAN3 Identifier acceptance register 3
#define CAN3IDM0   _P(0x214) // CAN3 Identifier mask register 0
#define CAN3IDM1   _P(0x215) // CAN3 Identifier mask register 1
#define CAN3IDM2   _P(0x216) // CAN3 Identifier mask register 2
#define CAN3IDM3   _P(0x217) // CAN3 Identifier mask register 3
#define CAN3IDA4   _P(0x218) // CAN3 Identifier acceptance register 4
#define CAN3IDA5   _P(0x219) // CAN3 Identifier acceptance register 5
#define CAN3IDA6   _P(0x21A) // CAN3 Identifier acceptance register 6
#define CAN3IDA7   _P(0x21B) // CAN3 Identifier acceptance register 7
#define CAN3IDM4   _P(0x21C) // CAN3 Identifier mask register 4
#define CAN3IDM5   _P(0x21D) // CAN3 Identifier mask register 5
#define CAN3IDM6   _P(0x21E) // CAN3 Identifier mask register 6
#define CAN3IDM7   _P(0x21F) // CAN3 Identifier mask register 7
#define CAN3RXFG   _P(0x220) // CAN3 RX foreground buffer thru +0x22F
#define CAN3TXFG   _P(0x230) // CAN3 TX foreground buffer thru +0x23F

#define PTT        _P(0x240) // portT data register
#define PTIT       _P(0x241) // portT input register
#define DDRT       _P(0x242) // portT direction register
#define RDRT       _P(0x243) // portT reduced drive register
#define PERT       _P(0x244) // portT pull device enable
#define PPST       _P(0x245) // portT pull polarity select

#define PTS        _P(0x248) // portS data register
#define PTIS       _P(0x249) // portS input register
#define DDRS       _P(0x24A) // portS direction register
#define RDRS       _P(0x24B) // portS reduced drive register
#define PERS       _P(0x24C) // portS pull device enable
#define PPSS       _P(0x24D) // portS pull polarity select
#define WOMS       _P(0x24E) // portS Wired Or mode register

#define PTM        _P(0x250) // portM data register
#define PTIM       _P(0x251) // portM input register
#define DDRM       _P(0x252) // portM direction register
#define RDRM       _P(0x253) // portM reduced drive register
#define PERM       _P(0x254) // portM pull device enable
#define PPSM       _P(0x255) // portM pull polarity select
#define WOMM       _P(0x256) // portM Wired Or mode register
#define MODRR      _P(0x257) // portM Module routing register
#define PTP        _P(0x258) // portP data register
#define PTIP       _P(0x259) // portP input register
#define DDRP       _P(0x25A) // portP direction register
#define RDRP       _P(0x25B) // portP reduced drive register
#define PERP       _P(0x25C) // portP pull device enable
#define PPSP       _P(0x25D) // portP pull polarity select
#define PIEP       _P(0x25E) // portP interrupt enable register
#define PIFP       _P(0x25F) // portP interrupt flag register
#define PTH        _P(0x260) // portH data register
#define PTIH       _P(0x261) // portH input register
#define DDRH       _P(0x262) // portH direction register
#define RDRH       _P(0x263) // portH reduced drive register
#define PERH       _P(0x264) // portH pull device enable
#define PPSH       _P(0x265) // portH pull polarity select
#define PIEH       _P(0x266) // portH interrupt enable register
#define PIFH       _P(0x267) // portH interrupt flag register
#define PTJ        _P(0x268) // portP data register
#define PTIJ       _P(0x269) // portP input register
#define DDRJ       _P(0x26A) // portP direction register
#define RDRJ       _P(0x26B) // portP reduced drive register
#define PERJ       _P(0x26C) // portP pull device enable
#define PPSJ       _P(0x26D) // portP pull polarity select
#define PIEJ       _P(0x26E) // portP interrupt enable register
#define PIFJ       _P(0x26F) // portP interrupt flag register

#define CAN4CTL0   _P(0x280) // CAN4 control register 0
#define CAN4CTL1   _P(0x281) // CAN4 control register 1
#define CAN4BTR0   _P(0x282) // CAN4 bus timing register 0
#define CAN4BTR1   _P(0x283) // CAN4 bus timing register 1
#define CAN4RFLG   _P(0x284) // CAN4 receiver flags
#define CAN4RIER   _P(0x285) // CAN4 receiver interrupt enables
#define CAN4TFLG   _P(0x286) // CAN4 transmit flags
#define CAN4TIER   _P(0x287) // CAN4 transmit interrupt enables
#define CAN4TARQ   _P(0x288) // CAN4 transmit message abort control
#define CAN4TAAK   _P(0x289) // CAN4 transmit message abort status
#define CAN4TBEL   _P(0x28A) // CAN4 transmit buffer select
#define CAN4IDAC   _P(0x28B) // CAN4 identfier acceptance control

#define CAN4RERR   _P(0x28E) // CAN4 Receive error counter
#define CAN4TERR   _P(0x28F) // CAN4 Transmit error counter
#define CAN4IDA0   _P(0x290) // CAN4 Identifier acceptance register 0
#define CAN4IDA1   _P(0x291) // CAN4 Identifier acceptance register 1
#define CAN4IDA2   _P(0x292) // CAN4 Identifier acceptance register 2
#define CAN4IDA3   _P(0x293) // CAN4 Identifier acceptance register 3
#define CAN4IDM0   _P(0x294) // CAN4 Identifier mask register 0
#define CAN4IDM1   _P(0x295) // CAN4 Identifier mask register 1
#define CAN4IDM2   _P(0x296) // CAN4 Identifier mask register 2
#define CAN4IDM3   _P(0x297) // CAN4 Identifier mask register 3
#define CAN4IDA4   _P(0x298) // CAN4 Identifier acceptance register 4
#define CAN4IDA5   _P(0x299) // CAN4 Identifier acceptance register 5
#define CAN4IDA6   _P(0x29A) // CAN4 Identifier acceptance register 6
#define CAN4IDA7   _P(0x29B) // CAN4 Identifier acceptance register 7
#define CAN4IDM4   _P(0x29C) // CAN4 Identifier mask register 4
#define CAN4IDM5   _P(0x29D) // CAN4 Identifier mask register 5
#define CAN4IDM6   _P(0x29E) // CAN4 Identifier mask register 6
#define CAN4IDM7   _P(0x29F) // CAN4 Identifier mask register 7
#define CAN4RXFG   _P(0x2A0) // CAN4 RX foreground buffer thru +0x2AF
#define CAN4TXFG   _P(0x2B0) // CAN4 TX foreground buffer thru +0x2BF

#endif /* _M68HC12_PORTS_DEF_H */

