#pragma once

#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <optional>

#include "instructions.h"

enum class State {
    Ins,
    Reg,
    Sep,
    Imm,
    Cmt,
    End,
};

class Register {
    private:

        std::string_view name;
        int id;

    public:

        Register() = delete;

        Register(std::string_view n, int i) : 
            name{n}, id{i} { };

};

class Inst {

    typedef std::optional<Register> Reg;

    private:

        OpCode instruction;
        std::array<Reg, 3> args;

    public:

        Inst(OpCode i, Reg r1 = std::nullopt, Reg r2 = std::nullopt, Reg r3 = std::nullopt) :
            instruction{i}, args{r1, r2, r3} { };

};

class Parser {
    private:
        State cur_state;
        std::string buffer;
        std::vector<Inst> ir_vec;
    
    public:
        
};