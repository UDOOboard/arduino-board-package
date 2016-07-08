ENTRY(__boot)
EXTERN(main __vector_table ram_vector)

MEMORY
{
	/*text        (RX): ORIGIN = 0x847C0000, LENGTH = 0x00020000*/  /* for build clean.fw DDR */

	text        (RX): ORIGIN = 0x84000000, LENGTH = 0x00080000		/* DDR */
  data        (RW): ORIGIN = 0x00901000, LENGTH = 0x0001E000    	/* OCRAM */
}

CODE_BASE_ADDR_START            = ORIGIN(text);
CODE_SIZE                       = LENGTH(text);
CODE_BASE_ADDR_END              = CODE_BASE_ADDR_START + CODE_SIZE;

DATA_BASE_ADDR_START            = ORIGIN(data);
DATA_SIZE                       = LENGTH(data);
DATA_BASE_ADDR_END              = DATA_BASE_ADDR_START + DATA_SIZE;

/* exported symbols */
__DEFAULT_INTERRUPT_STACK_SIZE  = 1024;

__ROM_END                       = CODE_BASE_ADDR_END;

/* 64kB of shared memory at DDR */
__SHARED_RAM_START              = 0xBFF00000;
__SHARED_RAM_END                = 0xBFF10000;

/* define 4KB clock management share memory in RAM*/
__SHARED_CM_IRAM_START          = 0x2091F000;
__SHARED_CM_IRAM_END            = 0x20920000;

/* 32kB TCML for system pool extension */
__SRAM_POOL_START               = 0x1FFF8010;    /* reserve first 4 word for reset (boot vector) */
__SRAM_POOL_END                 = 0x20000000;

__BOOT_STACK_ADDRESS            = 0x0091FFFF;
__KERNEL_DATA_END               = DATA_BASE_ADDR_END;

SECTIONS
{
    /* place vectors at the start, each section has only one symbol */
    .vectors :
    {
        *(.vectors_rom)
    } > text
    
    /* place text */
    .text :
    {
        *(KERNEL)
        *(.text*)
        *(.rodata*)
        
        /* glue arm/thumb and thumb/arm code */
        *(.glue_7)
        *(.glue_7t)
        
        /* unwind exception frame */
        KEEP(*(.eh_frame))
        KEEP(*(.eh_frame_hdr))
        
        . = ALIGN(0x8);
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))
        
        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))
        
        /* preinit_array */
        __preinit_array_start = .;
        KEEP (*(.preinit_array*))
        __preinit_array_end = .;
        
        /* init_array */
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        __init_array_end = .;
        
        /* fini_array */
        __fini_array_start = .;
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        __fini_array_end = .;
        
        /* gnu arm zero table */
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG (_bss_start)
        LONG (_bss_end - _bss_start)
        __zero_table_end__ = .;
        
        /* gnu arm copy table */
        /* NOTE: bootloader requires rom to ram data copy */
        . = ALIGN(4);
        __copy_table_start__ = .;
        LONG (LOADADDR(.data))
        LONG (_data_start)
        LONG (_data_end - _data_start)
        __copy_table_end__ = .;
        
    } > text
    
    /* unwind exception frame */
    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > text
    .ARM :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > text
    
    /* place data, region address must be 8B aligned */
    .data :
    {
        _data_start = .;
        *(.vectors_ram)
        *(.data*)
        . = ALIGN(8);
        _data_end = .;
    } > data AT> text
    
    /* place bss, section size must be 8 aligned because of startup */
    .bss BLOCK(8) :
    {
      _bss_start = .;
      *(.bss*)
      *(COMMON)
      . = ALIGN(8);
      _bss_end = .;
    } > data
    
    .kernel_data BLOCK(0x10) : 
    {
        __KERNEL_DATA_START = ALIGN(0x10);
    } > data
}

