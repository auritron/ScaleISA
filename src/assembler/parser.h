#pragma once

#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <optional>

#include "instructions.h"
#include "errorlist.h"

namespace Parser { 

    enum class State {
        Idn,    //identifier mode, transition state, can be pushed as variable or opcode
        Rgt,    //register transition state (when 'R' is detected)
        Reg,    //register
        Sep,    //seperator (,)
        Imt,    //immediate transition state (when '#' is detected)
        Imm,    //immediate
        Lbt,    //label transition (when '@' is detected)
        Lbl,    //label
        Zer,    //zero prefix, transition state
        Adr,    //address (eg. 0xDEADBEEF)
        Cmt,    //comment (;)
        Nil,    //none (whitespace type char)
        Err,    //error/unknown state
    };

    enum class Action {
        Push,   //push character to buffer
        Emit,   //emit token in buffer
        PsEm,   //both push and emit
        Idle,   //do nothing
    };

    class Register {
        private:

            std::string_view name;
            int id;

        public:

            Register() = delete;

            Register(std::string_view n, int i);

    };

    class Inst { //instruction node

        using Reg = std::optional<Register>;

        private:

            Instruction::OpCode instruction;
            std::array<Reg, 3> args;

        public:

            Inst(Instruction::OpCode i, Reg r1 = std::nullopt, Reg r2 = std::nullopt, Reg r3 = std::nullopt);

    };

    class Tokenizer {
        
        private:
            State cur_state;
            Action cur_action;
            std::string buffer;
            unsigned char cur_ch;
            size_t ch_count;    //characters counted from input
            
        public:

            std::vector<Inst> ir_vec;

            Tokenizer();
            void tokenize();
            Inst create_inst();
            std::optional<Instruction::OpCode> match_token();
            void set_state();
            void set_action();
            void raise_parsing_error(Error::ParsingError e);

    };

}

