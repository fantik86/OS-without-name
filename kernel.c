#include <stdlib.h>
char* vidptr = (char*)0xB8000;

void print(char* str) {
    int pos = 0;
    for (char* i = &(str[0]); *i != '\0'; ++i) {
        vidptr[pos] = *i;
        vidptr[pos+1] = 0x07;
        pos += 2;
    }
}

#define HALT __asm__(\
    "mov eax, %0\n" \
    "push eax\n" \
    "call print\n" \
    "hlt" : : "r" "CPU HALT"))

void print_pos(char* str, unsigned char x, unsigned char y) {
    int pos = (y * 80) * 2 + (x * 2);
    uint8_t last_byte = (uint16_t)pos & 0xFF;
    if (last_byte % 2 == 1) {
        pos+=1;
    }
    for (char* i = &(str[0]); *i != '\0'; ++i, pos+=2) {
        vidptr[pos] = *i;
    }
}

typedef struct {
    uint16_t offset_1;
    uint16_t segment_selector;
    const uint8_t reserved;
    uint8_t attributes;
    uint16_t offset_2;
} __attribute__((packed)) idt_entry;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_ptr;

typedef idt_entry idt[256];

void interrupt_handler(void* ptr) {
  print("Interrupt activated!");
  __asm__("pop ebp\n"
	  "iret");
}

void set_idt_entry(idt* _idt, idt_entry entry, uint8_t index) {
  (*_idt)[index].offset_1 = entry.offset_1;
  (*_idt)[index].segment_selector = entry.segment_selector;
  (*_idt)[index].attributes = entry.attributes;
  (*_idt)[index].offset_2 = entry.offset_2;
}



void kernel_main(void) {
  idt _idt;
    idt_entry ent;
    ent.offset_1 = (uint16_t)(((uintptr_t)interrupt_handler) & 0xFFFF);
    ent.offset_2 = (uint16_t)(((uintptr_t)interrupt_handler >> 16) & 0xFFFF);
    ent.segment_selector = 0x08;
    ent.attributes = 0b10001110;

    set_idt_entry(&_idt, ent, 5);
    idt_ptr idt_pointer;
    idt_pointer.limit = (sizeof(idt_entry) * 256) - 1;
    idt_pointer.base = (uint32_t)&_idt;
    
    __asm__(
        "lidt %0" : : "m" (idt_pointer));
    __asm__("int 5");
    //print("ok");
    __asm__("hlt");
}
