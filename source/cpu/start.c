/*
 * File:	start.c
 * Purpose:	Kinetis start up routines. 
 *
 * Notes:		
 */
#include "common.h"
#include "start.h"

#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"
#pragma section = "CodeRelocate"
#pragma section = "CodeRelocateRam" 

/******************************************************************************/
/*!
 * \brief   Kinetis Start
 * \return  None
 *
 * This function calls all of the needed starup routines and then 
 * branches to the main process.
 */
void start(void)
{
	/* Disable the watchdog timer */
	wdog_disable();

	/* Copy any vector or data sections that need to be in RAM */
	common_startup();

	/* Perform processor initialization */
	clkinit();

	/* Jump to main process */
	main();

	/* No actions to perform after this so wait forever */
	while(1);

} // start

/******************************************************************************/
/*!
 * \brief   Kinetis Startup
 * \return  None
 *
 * This function calls startup Generic Kinetis.
 */

void common_startup(void)
{
    /* Declare a counter we'll use in all of the copy loops */
    int32 n;

    /* Addresses for VECTOR_TABLE and VECTOR_RAM come from the linker file */
    extern uint32 __VECTOR_TABLE[];
    extern uint32 __VECTOR_RAM[];

    /* Copy the vector table to RAM */
    if (__VECTOR_RAM != __VECTOR_TABLE)
    {
        for (n = 0; n < 0x410; n++)
            __VECTOR_RAM[n] = __VECTOR_TABLE[n];
    }
    /* Point the VTOR to the new copy of the vector table */
    write_vtor((uint32)__VECTOR_RAM);

    /* Get the addresses for the .data section (initialized data section) */
    uint8* data_ram = __section_begin(".data");
    uint8* data_rom = __section_begin(".data_init");
    uint8* data_rom_end = __section_end(".data_init");
    
    /* Copy initialized data from ROM to RAM */
    n = data_rom_end - data_rom;
    while (n-- > 0)
        *data_ram++ = *data_rom++;
 
 
    /* Get the addresses for the .bss section (zero-initialized data) */
    uint8* bss_start = __section_begin(".bss");
    uint8* bss_end = __section_end(".bss");
    
    /* Clear the zero-initialized data section */
    n = bss_end - bss_start;
    while(n-- > 0)
        *bss_start++ = 0;    
    
   /* Get addresses for any code sections that need to be copied from ROM to RAM.
    * The IAR tools have a predefined keyword that can be used to mark individual
    * functions for execution from RAM. Add "__ramfunc" before the return type in
    * the function prototype for any routines you need to execute from RAM instead 
    * of ROM. ex: __ramfunc void foo(void);
    */
    uint8* code_relocate_ram = __section_begin("CodeRelocateRam");
    uint8* code_relocate = __section_begin("CodeRelocate");
    uint8* code_relocate_end = __section_end("CodeRelocate");
    
    /* Copy functions from ROM to RAM */
    n = code_relocate_end - code_relocate;
    while (n-- > 0)
        *code_relocate_ram++ = *code_relocate++;

} // common_startup
/******************************************************************************/

