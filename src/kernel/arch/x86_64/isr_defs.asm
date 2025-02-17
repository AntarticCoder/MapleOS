.macro isr_err_stub num
isr_stub_\num:
    call exception_handler
    iret 
.endm
# if writing for 64-bit, use iretq instead
.macro isr_no_err_stub num
isr_stub_\num:
    call exception_handler
    iret
.endm

.extern exception_handler

.text
.global isr_no_err_stub_0
.global isr_no_err_stub_1
.global isr_no_err_stub_2
.global isr_no_err_stub_3
.global isr_no_err_stub_4
.global isr_no_err_stub_5
.global isr_no_err_stub_6
.global isr_no_err_stub_7
.global isr_err_stub_8
.global isr_no_err_stub_9
.global isr_err_stub_10
.global isr_err_stub_11
.global isr_err_stub_12
.global isr_err_stub_13
.global isr_err_stub_14
.global isr_no_err_stub_15
.global isr_no_err_stub_16
.global isr_err_stub_17
.global isr_no_err_stub_18
.global isr_no_err_stub_19
.global isr_no_err_stub_20
.global isr_no_err_stub_21
.global isr_no_err_stub_22
.global isr_no_err_stub_23
.global isr_no_err_stub_24
.global isr_no_err_stub_25
.global isr_no_err_stub_26
.global isr_no_err_stub_27
.global isr_no_err_stub_28
.global isr_no_err_stub_29
.global isr_err_stub_30
.global isr_no_err_stub_31
