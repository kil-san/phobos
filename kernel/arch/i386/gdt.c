#include <arch/i386/gdt.h>

/* GDT with 5 entries: null, code PL0, data PL0, code PL3, data PL3 */
struct gdt_entry gdt[5];
struct gdt_ptr gp;

/* Assembly function to load GDT */
extern void gdt_flush(uint32_t);

/* Helper to create a GDT entry */
static void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = limit & 0xFFFF;
    gdt[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[num].access      = access;
}

void gdt_install(void) {
    gp.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gp.base  = (uint32_t)&gdt;

    /* Null descriptor */
    gdt_set_entry(0, 0, 0, 0, 0);

    /* Kernel code segment */
    gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);

    /* Kernel data segment */
    gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF);

    /* User code segment */
    gdt_set_entry(3, 0, 0xFFFFF, 0xFA, 0xCF);

    /* User data segment */
    gdt_set_entry(4, 0, 0xFFFFF, 0xF2, 0xCF);

    /* Load the GDT */
    gdt_flush((uint32_t)&gp);
}
