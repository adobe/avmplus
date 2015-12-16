#import "TargetConditionals.h"

#if !TARGET_IPHONE_SIMULATOR
#if !TARGET_CPU_ARM64
.section    __TEXT,__text,regular,pure_instructions
.section    __TEXT,__textcoal_nt,coalesced,pure_instructions
.section    __TEXT,__const_coal,coalesced
.section    __TEXT,__picsymbolstub4,symbol_stubs,none,16
.section    __TEXT,__StaticInit,regular,pure_instructions
.section    __TEXT,__cstring,cstring_literals
.syntax unified
.section    __TEXT,__text,regular,pure_instructions
.globl _returnCoercer32
.align  2
_returnCoercer32:                                ## @returnCoercer32
@ BB#0:
mov         a2, a3
mov         a3, a4
b           _returnCoercer32Impl

.globl _returnCoercerN32
.align  2
_returnCoercerN32:                              ## @returnCoercerN32
@ BB#0:
mov         a2, a3
mov         a3, a4
b           _returnCoercerN32Impl

.globl _returnCoercerN
.align  2
_returnCoercerN:                                ## @returnCoercerN
@ BB#0:
b           _returnCoercerNImpl

.globl _coerce32CdeclShim
.align  2
_coerce32CdeclShim:                             ## @coerce32CdeclShim
@ BB#0:
stmdb  sp!, {v1, v2, v3, v7, lr}
mov v7, sp
// a1 = callee
// a2 = calleeArgDescBufSize
// a3 = argCoercer
// a4 = env
// [v7] = retTraits
// [v7, #4] = callerArgDesc
// [v7, #8] = callerAp
sub sp, sp, a2; // make room for args
bic sp, sp, #7; // double word align
mov v2, a3; // save off argCoercer
mov v3, a4; // save off env

// a1 stays callee
mov a2, a4; // pass env
ldr a3, [v7, #20]; // pass retTraits
ldr a4, [v7, #24]; // pass callerArgDesc
mov v1, sp; // pass calleeArgDescBuf
stmdb sp!, {v1};
ldr v1, [v7, #28]; // pass callerAp
stmdb sp!, {v1};
mov v1, a1; // save off callee
bl _via_v2; // call coercer!
add sp, sp, #8; // restore stack
mov v2, a1; // remember returnCoercer
ldmia  sp!, {a1, a2, a3, a4}; // move first 4 arg words into registers
bl _via_v1; // call the implementation!
mov sp, v7; // restore stack
cmp v2, #0; // maybe call returnCoercer -- a1 and a2 will be the double or a1 will be the 32 and a2 will be a dummy
ldrne a3, [v7, #20]; // retTraits
movne a4, v3; // env
blne _via_v2;
ldmia  sp!, {v1, v2, v3, v7, pc}; // done!
_via_v1: bx v1;
_via_v2: bx v2;

.globl _coerceNCdeclShim
.align  2
_coerceNCdeclShim:                      ## @coerceNCdeclShim
@ BB#0:
b           _coerce32CdeclShim


#else // TARGET_CPU_ARM64

.section    __TEXT,__text,regular,pure_instructions
    .globl _returnCoercer32
    .align  2
_returnCoercer32:                                ; @returnCoercer32
.cfi_startproc
; BB#0:
    mov         x1, x2
    mov         x2, x3
    b           _returnCoercer32Impl
.cfi_endproc

    .globl _returnCoercerN32
    .align  2
_returnCoercerN32:                              ; @returnCoercerN32
.cfi_startproc
; BB#0:
    mov         x1, x2
    mov         x2, x3
    b           _returnCoercerN32Impl
.cfi_endproc

// Double argument is returned in register d0
    .globl _returnCoercerN
    .align  2
_returnCoercerN:                                ; @returnCoercerN
.cfi_startproc
; BB#0:
    mov         x0, x2
    mov         x1, x3
    b           _returnCoercerNImpl
.cfi_endproc


.globl  _coerce32CdeclShim
.align  2
_coerce32CdeclShim:                             ; @coerce32CdeclShim
.cfi_startproc
; BB#0:
stp     x29, x30, [sp, #-16]!;      // save previous frame pointer and return address in the stack
mov     x29, sp;                    // frame pointer points to the (prev-fp, return-address) pair
sub     sp, sp, #48  ;              //decrement stack pointer by 40 bytes (5 64-bit words)
stp     x19, x20, [sp];             // callee saved registers,save x19-x23
stp     x21, x22, [sp, #16];        // callee saved registers,save x19-x23
str     x23, [sp, #32];             // callee saved registers,save x19-x23
mov     x23, sp;                    //Save current sp

// x0 = callee
// x1 = calleeArgDescBufSize
// x2 = argCoercer
// x3 = env
// x4 = retTraits
// x5 = callerArgDesc
// x6 = callerAp

mov     x9, #15;        // quad word align
add     x1, x1, x9;     // quad word align
bic     x1, x1, x9;     // quad word align
sub     sp, sp, x1;     // make room for args, after quad word align

mov     x19, x0;        // save callee
mov     x20, x2;        // save argCoercer
mov     x21, x3;        // save env
mov     x22, x4;        // save retTraits , required to call returnCoercer

// x0 stays callee
mov     x1, x3;         // pass env
mov     x2, x4;         // pass retTraits
mov     x3, x5;         // pass callerArgDesc
mov     x4, x6;         // pass callerAp
mov     x5, sp;         // pass calleeArgDescBuf

blr     x20;            // call coercer!
mov     x20, x0;        // remember returnCoercer

// Load first 8 FP registers from memory and then 8 param registers
ldp     d0, d1, [sp];          // move first 8 arg words into registers
ldp     d2, d3, [sp, #16];   // move first 8 arg words into registers
ldp     d4, d5, [sp, #32];   // move first 8 arg words into registers
ldp     d6, d7, [sp, #48];   // move first 8 arg words into registers
ldp     x0, x1, [sp, #64];          // move first 8 arg words into registers
ldp     x2, x3, [sp, #80];   // move first 8 arg words into registers
ldp     x4, x5, [sp, #96];   // move first 8 arg words into registers
ldp     x6, x7, [sp, #112];   // move first 8 arg words into registers
add     sp, sp, #128;

blr     x19;                    // call the implementation!
mov     sp, x23;                // restore stack

cbnz    x20, callRetCoerce;     // maybe call returnCoercer -- x0 will have the double or 32 value

//Restore Callee saved registers and stack
ldp     x19, x20, [sp]; 
ldp     x21, x22, [sp, #16]; 
ldr     x23, [sp, #32]; 
add     sp, sp, #0x48;           // increment stack pointer over these 5 64-bit words
mov     sp, x29;                 // restore sp from frame pointer
ldp     x29, x30, [sp], #16;          // load previous fp and return address
ret;                            // transfer to return address (lr)

callRetCoerce:
//x0 return value either atom or double (both 64 bit)
mov     x1, x22;                // retTraits
mov     x3, x21;                // env
blr     x20;

.cfi_endproc

    .globl _coerceNCdeclShim
    .align  2
_coerceNCdeclShim:                      ; @coerceNCdeclShim
.cfi_startproc
; BB#0:
    b           _coerce32CdeclShim
.cfi_endproc


#endif // AVMPLUS_64BIT
#endif // TARGET_IPHONE_SIMULATOR