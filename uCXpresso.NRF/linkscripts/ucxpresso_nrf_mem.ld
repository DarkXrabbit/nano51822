/*
 * GENERATED FILE - DO NOT EDIT
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v7.2.0 [Build 153] [2014-05-19]  on Sun Jul 20 16:58:20 CST 2014)
*/

MEMORY
{
  /* Define each memory region */
  FLASH (rx) : ORIGIN = 0x00016000, LENGTH = 148k /* 152 bytes */
  RAM (rwx) : ORIGIN = 0x20002000, LENGTH = 8k /* 8K bytes */
}
  /* Define a symbol for the top of each memory region */
  __top_FLASH = 0x00016000 + 148k;
  __top_RAM = 0x20002000 + 8k;



