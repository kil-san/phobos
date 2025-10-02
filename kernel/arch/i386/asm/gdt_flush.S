.intel_syntax noprefix
.global gdt_flush

# Argument: pointer to gdt_ptr struct in eax (passed from C)
gdt_flush:
    mov eax, [esp + 4]     # load address of gdt_ptr
    lgdt [eax]             # load GDT

    # Reload segment registers
    mov ax, 0x10           # kernel data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    # Far jump to reload CS
    jmp 0x08:flush2
flush2:
    ret
