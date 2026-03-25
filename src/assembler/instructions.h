#pragma once

enum class OpCode {

    //memory and registers
    LOAD,
    SEND,
    COPY,
    SET,
    SWAP,

    //bitwise
    NOT,
    AND,
    OR,
    XOR,

    //shift and rotation
    STL,
    STR,
    RTL,
    RTR,

    //arithmetic
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NEG,

    //comparison and branching
    CMP,
    GOTO,
    WEQ,
    WGT,
    WLT,

    //stacks and sub-routines
    CAL,
    RET,
    PUSH,
    POP,

    //  i/o
    PRINT,
    PRINTC,

    //misc. and debugging
    END,
    CLRC,
    CLRR,

};