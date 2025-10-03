.extern irq_handler
.extern keyboard_handler

/* Macros (IRQ always have no error code) */
.macro irq_stub num, handler
irq_stub_\num:
    pushl $\num           # interrupt number
    # CPU already pushed real error code under ESP
    mov %esp, %eax        # pointer to struct regs
    push %eax
    call \handler
    add $8, %esp          # pop pointer + int_no
    iret
.endm


/*-------------------------------
 * IRQ Stubs (32–47 after PIC remap)
 *-------------------------------*/
irq_stub 32, irq_handler   /* Timer */
irq_stub 33, keyboard_handler   /* Keyboard */
irq_stub 34, irq_handler
irq_stub 35, irq_handler
irq_stub 36, irq_handler
irq_stub 37, irq_handler
irq_stub 38, irq_handler
irq_stub 39, irq_handler
irq_stub 40, irq_handler
irq_stub 41, irq_handler
irq_stub 42, irq_handler
irq_stub 43, irq_handler
irq_stub 44, irq_handler
irq_stub 45, irq_handler
irq_stub 46, irq_handler
irq_stub 47, irq_handler

/*-------------------------------
 * IRQ Stub Table
 *-------------------------------*/
 
    .globl irq_stub_table
irq_stub_table:
    .long irq_stub_32
    .long irq_stub_33
    .long irq_stub_34
    .long irq_stub_35
    .long irq_stub_36
    .long irq_stub_37
    .long irq_stub_38
    .long irq_stub_39
    .long irq_stub_40
    .long irq_stub_41
    .long irq_stub_42
    .long irq_stub_43
    .long irq_stub_44
    .long irq_stub_45
    .long irq_stub_46
    .long irq_stub_47
