ENTRY(Reset_Handler)

MEMORY
{
    /* The bluepill memory map and sizes */
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text : {
        . = 0;

        KEEP(*(.isr_vectors))

        /* The whole interrupt table is 304 bytes long. */
        . = 304;

        *(.text.Reset_Handler)
        *(.text*)
        *(.rodata*)
    } > FLASH = 0xFF

    . = ALIGN(4);

    _etext = .;
    _sidata = _etext;

    .data  : AT ( _sidata ) {
        . = ALIGN(4);

        _sdata = . ;
        *(.data*)

        . = ALIGN(4);
        _edata = . ;
    } > RAM

    .bss : {
        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;
	    __bss_start__ = _sbss;
        *(.bss)
        *(.bss.*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = . ;
	    __bss_end__ = _ebss;
    } >RAM

    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );
    PROVIDE ( _exit = _ebss );

    /* TODO: This is for compiling the standard library, this should be real functions */
    PROVIDE ( _close = _ebss );
    PROVIDE ( _lseek = _ebss );
    PROVIDE ( _read = _ebss );
    PROVIDE ( _sbrk = _ebss );
    PROVIDE ( _write = _ebss );

    PROVIDE (_stackend = ORIGIN(RAM) + LENGTH(RAM) - _Minimum_Stack_Size);

    _end_of_ram = ORIGIN(RAM) + LENGTH(RAM);
    _estack = _end_of_ram;
}
