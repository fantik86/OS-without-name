ENTRY(_start)

SECTIONS {
    . = 0x7C00;
    
    .v86 = 0x8000;
    
    .text : {
        *(.text)          
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)           
    }
}