OUTPUT_FORMAT("elf32-m68hc12", "elf32-m68hc12",
            "elf32-m68hc12")
OUTPUT_ARCH(m68hc12)
ENTRY(_start)
SEARCH_DIR("z:\usr\lib\gcc-lib\m6811-elf\3.0.4\m68hc12\mshort")

MEMORY
{
  ioports (!x)  : org = 0x0000, l = 0x400
  eeprom  (!i)  : org = 0x400, l = 0xbec
  data    (rwx) : org = 0x1000, l = 0x2e00
  text    (rx)  : org = 0x4000, l = 0x4000
  vectors (rx)  : org = 0x3f8c, l = 0x72
}

PROVIDE (_stack = 0x3E00);

vectors_addr = 0x3f8c;
