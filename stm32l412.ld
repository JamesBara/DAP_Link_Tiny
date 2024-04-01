__stack_size__ = 0x00008000;

MEMORY
{
  SRAM    (rwx)    : ORIGIN = 0x20000000,   LENGTH = 40K
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 64K
}

ENTRY(Reset_Handler)

SECTIONS
{
	.text :
	{
		. = ALIGN(4);
		_svtor = .;
		KEEP(*(.isr_vector))
		. = ALIGN(4);
		_evtor = .;
		_stext = _evtor;
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		KEEP(*(.eh_frame*))
		. = ALIGN(4);
		_etext = .;
	} > FLASH

	.stack (COPY):
	{
		. = ALIGN(8);
		_sstack = .;
       _sstack = .;
	   . = . + __stack_size__;
	   _estack = .;
	   . = ALIGN(8);
	} > SRAM

	_sidata = LOADADDR(.data); /* I don't understand why this is needed here. Using etext is not aligning properly.*/

	.data :
	{
		. = ALIGN(4);
		_sdata = .;
		*(.data)
		*(.data.*)
		*(.RamFunc)
        *(.RamFunc*)
		. = ALIGN(4);
		_edata = .;
	} > SRAM AT > FLASH

	.bss :
	{
		. = ALIGN(4);
		_sbss = .;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	} > SRAM
}