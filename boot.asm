section .text
extern kernel_main
global _start

BITS 16
_start:
    mov ax,0x0003
    int 10h ; Switch video mode
    lgdt [gdt_pointer]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_kmain
.hang:
    hlt
	jmp .hang
.end:

gdt_start:
    dq 0x0
gdt_code:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_end:

gdt_pointer:
    dw gdt_end - gdt_start - 1    
    dd gdt_start    

CODE_SEG equ gdt_code - gdt_start 
DATA_SEG equ gdt_data - gdt_start  

BITS 32
init_kmain:
    cli
    mov ax,DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x10000
    mov ebp, esp
    call kernel_main

times 510-($-$$) db 0
dw 0xAA55
