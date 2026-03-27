#include <cctype>

#include "parser.h"
#include "errorlist.h"

using namespace Parser;

using ParseErr = Error::ParsingError;

Register::Register(std::string_view n, int i) : 
    name{n}, 
    id{i} 
{ }

Inst::Inst(Instruction::OpCode i, Reg r1, Reg r2, Reg r3 ) :
    instruction{i}, 
    args{r1, r2, r3} 
{ }

Tokenizer::Tokenizer() :
    cur_state{State::Nil},
    cur_action{Action::Push},
    buffer{""},
    cur_ch{0},
    ch_count{0},
    ir_vec{}
{ }

void Tokenizer::set_state() {

    switch (cur_state) {    //cur_state before changing

        case State::Cmt:
        
            if (cur_ch == '\n') {
                cur_state = State::Nil;
            }
            break;

        default:

            if (cur_ch == ';') {

                cur_state = State::Cmt;
                
            } else if (cur_state == State::Zer && cur_ch == 'x') { //0x detection

                cur_state = State::Adr;

            } else if (cur_ch == 'R') {

                switch (cur_state) {
                    case State::Nil:
                    case State::Sep:
                        cur_state = State::Rgt;
                        break;
                    case State::Rgt:
                    case State::Reg:
                        cur_state = State::Idn;
                        break;
                    case State::Adr:
                        raise_parsing_error(ParseErr::IncorrectAddressFmt);
                        break;
                    case State::Imt:
                    case State::Imm:
                        raise_parsing_error(ParseErr::ImmediateValueError);
                        break;
                    case State::Zer:
                        raise_parsing_error(ParseErr::IdentifierNamingError);
                        break;
                    case State::Cmt:
                    case State::Err:
                        std::abort();
                    default:
                        break;
                }

            } else if (cur_ch == '@') {
                
                switch (cur_state) {
                    case State::Idn:
                    case State::Rgt:
                    case State::Reg:
                    case State::Zer:
                        raise_parsing_error(ParseErr::IdentifierNamingError);
                        break;
                    case State::Imt:
                    case State::Imm:
                        raise_parsing_error(ParseErr::ImmediateValueError);
                        break;
                    case State::Lbl:
                    case State::Lbt:
                        raise_parsing_error(ParseErr::LabelNamingError);
                        break;
                    case State::Adr:
                        raise_parsing_error(ParseErr::AddressNamingError);
                        break;
                    case State::Sep:
                    case State::Nil:
                        cur_state = State::Lbt;
                        break;
                    case State::Cmt:
                    case State::Err:
                        std::abort();
                }

            } else if (cur_ch == '#') {

                switch (cur_state) {
                    case State::Idn:
                    case State::Rgt:
                    case State::Reg:
                    case State::Zer:
                        raise_parsing_error(ParseErr::IdentifierNamingError);
                        break;
                    case State::Imt:
                    case State::Imm:
                        raise_parsing_error(ParseErr::ImmediateValueError);
                        break;
                    case State::Lbl:
                    case State::Lbt:
                        raise_parsing_error(ParseErr::LabelNamingError);
                        break;
                    case State::Adr:
                        raise_parsing_error(ParseErr::AddressNamingError);
                        break;
                    case State::Sep:
                    case State::Nil:
                        cur_state = State::Imt;
                        break;
                    case State::Cmt:
                    case State::Err:
                        std::abort();
                }

            } else if (cur_ch == '_') {

                switch (cur_state) {
                    case State::Idn:
                    case State::Rgt:
                    case State::Reg:
                    case State::Sep:
                    case State::Nil:
                        cur_state = State::Idn;
                        break;
                    case State::Zer:
                        raise_parsing_error(ParseErr::IdentifierNamingError);
                        break;
                    case State::Imt:
                    case State::Imm:
                        raise_parsing_error(ParseErr::ImmediateValueError);
                        break;
                    case State::Lbl:
                    case State::Lbt:
                        cur_state = State::Lbl;
                        break;
                    case State::Adr:
                        raise_parsing_error(ParseErr::AddressNamingError);
                        break;
                    case State::Cmt:
                    case State::Err:
                        std::abort();
                }
                
            } else if (std::isdigit(cur_ch)) {

                switch (cur_state) {
                    case State::Idn:
                        cur_state = State::Idn;
                        break;
                    case State::Rgt:
                    case State::Reg:
                        cur_state = State::Reg;
                        break;
                    case State::Sep:
                    case State::Nil:
                        if (cur_ch == '0') { //if its zero, set to zer to transition to address, else raise error
                            cur_state = State::Zer;
                        } else {
                            raise_parsing_error(ParseErr::IdentifierNamingError);
                        }
                        break;
                    case State::Imt:
                    case State::Imm:
                        cur_state = State::Imm;
                        break;
                    case State::Lbt:
                    case State::Lbl:
                        cur_state = State::Lbl;
                    case State::Zer:
                        raise_parsing_error(ParseErr::ImmediateValueError);
                    case State::Adr:
                        cur_state = State::Adr;
                        break;
                    case State::Cmt:
                    case State::Err:
                        std::abort();
                }

            } else if (std::isalpha(cur_ch)) {

                switch (cur_state) {
                    case State::Idn:
                    case State::Rgt:
                    case State::Reg:
                    case State::Sep:
                    case State::Nil:
                        cur_state = State::Idn;
                    case State::Imm:
                    case State::Imt:
                        raise_parsing_error(ParseErr::ImmediateValueError);
                        break;
                    case State::Lbt:
                    case State::Lbl:
                        cur_state = State::Lbl;
                        break;
                    case State::Zer:
                    case State::Adr:
                        if ((cur_ch >= 'A' && cur_ch <= 'F') || (cur_ch >= 'a' && cur_ch <= 'f')) { //if between A-F or a-f
                            cur_state = State::Adr;
                        }
                        raise_parsing_error(ParseErr::IdentifierNamingError);
                        break;
                    case State::Cmt:
                    case State::Err:
                        std::abort();
                    
                }

            } else {

                cur_state = State::Err;
                raise_parsing_error(ParseErr::UnknownCharError);
                break;

            }
            break;

    }

}

void Tokenizer::tokenize() {
    set_state();
    set_action();
    create_inst();
}

void Tokenizer::raise_parsing_error(ParseErr e) {

}