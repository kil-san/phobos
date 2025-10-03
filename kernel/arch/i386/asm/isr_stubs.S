.extern divide_by_zero_handler
.extern exception_handler

/* Macros */
.macro isr_err_stub num, handler
isr_stub_\num:
    pushl $\num         # Push interrupt number
    movl %esp, %eax     # Pointer to struct regs
    push %eax
    call \handler
    addl $4, %esp       # Pop argument pointer
    addl $8, %esp       # Pop int_no and err_code
    iret
.endm

.macro isr_no_err_stub num, handler
isr_stub_\num:
    pushl $0            # Dummy error code if exception does not push one
    pushl $\num         # Push interrupt number
    movl %esp, %eax     # Pointer to struct regs
    push %eax
    call \handler
    addl $4, %esp       # Pop argument pointer
    addl $8, %esp       # Pop int_no and err_code
    iret
.endm

/*-------------------------------
 * ISR definitions
 *-------------------------------*/
/* Divide-by-zero (exception 0) uses custom handler */
isr_no_err_stub 0, divide_by_zero_handler

/* Other exceptions use generic handler */
isr_no_err_stub 1, exception_handler
isr_no_err_stub 2, exception_handler
isr_no_err_stub 3, exception_handler
isr_no_err_stub 4, exception_handler
isr_no_err_stub 5, exception_handler
isr_no_err_stub 6, exception_handler
isr_no_err_stub 7, exception_handler
isr_err_stub    8, exception_handler
isr_no_err_stub 9, exception_handler
isr_err_stub    10, exception_handler
isr_err_stub    11, exception_handler
isr_err_stub    12, exception_handler
isr_err_stub    13, exception_handler
isr_err_stub    14, exception_handler
isr_no_err_stub 15, exception_handler
isr_no_err_stub 16, exception_handler
isr_err_stub    17, exception_handler
isr_no_err_stub 18, exception_handler
isr_no_err_stub 19, exception_handler
isr_no_err_stub 20, exception_handler
isr_no_err_stub 21, exception_handler
isr_no_err_stub 22, exception_handler
isr_no_err_stub 23, exception_handler
isr_no_err_stub 24, exception_handler
isr_no_err_stub 25, exception_handler
isr_no_err_stub 26, exception_handler
isr_no_err_stub 27, exception_handler
isr_no_err_stub 28, exception_handler
isr_no_err_stub 29, exception_handler
isr_err_stub    30, exception_handler
isr_no_err_stub 31, exception_handler

/*-------------------------------
 * ISR Stub Table
 *-------------------------------*/

    .globl isr_stub_table
isr_stub_table:
    .long isr_stub_0
    .long isr_stub_1
    .long isr_stub_2
    .long isr_stub_3
    .long isr_stub_4
    .long isr_stub_5
    .long isr_stub_6
    .long isr_stub_7
    .long isr_stub_8
    .long isr_stub_9
    .long isr_stub_10
    .long isr_stub_11
    .long isr_stub_12
    .long isr_stub_13
    .long isr_stub_14
    .long isr_stub_15
    .long isr_stub_16
    .long isr_stub_17
    .long isr_stub_18
    .long isr_stub_19
    .long isr_stub_20
    .long isr_stub_21
    .long isr_stub_22
    .long isr_stub_23
    .long isr_stub_24
    .long isr_stub_25
    .long isr_stub_26
    .long isr_stub_27
    .long isr_stub_28
    .long isr_stub_29
    .long isr_stub_30
    .long isr_stub_31
