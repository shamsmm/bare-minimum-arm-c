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

    _end_of_ram = ORIGIN(RAM) + LENGTH(RAM);
    _estack = _end_of_ram;
}
