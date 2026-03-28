#pragma once

#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <optional>
#include <unordered_map>

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
        Adt,    //address transition ('x' in '0x')
        Adr,    //address (eg. 0xDEADBEEF)
        Cmt,    //comment (;)
        Nil,    //none (whitespace type char)
        Err,    //error/unknown state
    };

    enum class StateType {
        Word,
        RTransition, // special variation of transition since its alphanumeric
        Transition,
        Separator, // mostly redundant with StateType::None, helps with readability though
        None,
    };

    static const std::unordered_map<State, StateType> state_map {
        { State::Idn, StateType::Word },
        { State::Reg, StateType::Word },
        { State::Imm, StateType::Word },
        { State::Lbl, StateType::Word },
        { State::Adr, StateType::Word },
        { State::Rgt, StateType::RTransition },
        { State::Imt, StateType::Transition },
        { State::Lbt, StateType::Transition },
        { State::Adt, StateType::Transition },
        { State::Zer, StateType::Transition },
        { State::Sep, StateType::Separator },
        { State::Cmt, StateType::None },
        { State::Nil, StateType::None },
        { State::Err, StateType::None },
    };

    enum class Action {
        Push,   //push character to buffer
        Emit,   //emit token in buffer
        Idle,   //do nothing
    };

    class Register { //probably creating a single wrapper for an int here
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
            State prev_state;
            Action cur_action;
            std::string buffer;
            unsigned char cur_ch;
            size_t ch_count;    //characters counted from input
            size_t line_count;
            size_t col_count;
            bool error_detected;
            
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

