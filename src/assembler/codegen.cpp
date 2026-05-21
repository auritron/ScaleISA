#include "codegen.hpp"
#include "../overload.hpp"
#include "../panic.hpp"

namespace codegen_mod {

    using instruction_mod::OpCode;

    const std::unordered_map<OpCode, uint8_t> opcode_mapping {
        // R/I-types
        { OpCode::NOT,    0b00000 },
        { OpCode::AND,    0b00001 },
        { OpCode::OR,     0b00010 },
        { OpCode::XOR,    0b00011 },
        { OpCode::STL,    0b00100 },
        { OpCode::STR,    0b00101 },
        { OpCode::RTL,    0b00110 },
        { OpCode::RTR,    0b00111 },
        { OpCode::ADD,    0b01000 },
        { OpCode::SUB,    0b01001 },
        { OpCode::NEG,    0b01011 },
        { OpCode::MUL,    0b01100 },
        { OpCode::DIV,    0b01110 },
        { OpCode::MOD,    0b01111 },
        { OpCode::SET,    0b10000 },
        { OpCode::CMP,    0b10001 },

        // M-types
        { OpCode::LOAD,   0b00000 },
        { OpCode::SEND,   0b00001 },

        // S-types
        { OpCode::PUSH,   0b00000 },
        { OpCode::POP,    0b00001 },
        { OpCode::PRINT,  0b10000 },
        { OpCode::PRINTC, 0b10001 },

        // J-types
        { OpCode::WEQ,    0b00000 },
        { OpCode::WNE,    0b00001 },
        { OpCode::WGT,    0b00010 },
        { OpCode::WLT,    0b00011 },
        { OpCode::WCY,    0b00100 },
        { OpCode::WOV,    0b00101 },
        { OpCode::WDZ,    0b00110 },
        { OpCode::GOTO,   0b01000 },
        { OpCode::CAL,    0b01001 },

        // N-types
        { OpCode::RET,    0b00000 },
        { OpCode::END,    0b11111 },
        { OpCode::CLR,    0b10000 },
    };

    CodeGen::CodeGen() :
        next_unused_adr{instruction_mod::Inst::ADR_OFFSET},
        var_table{}
    { }

    uint32_t CodeGen::encode_R(uint8_t opcode, uint8_t dest, uint8_t src1, uint8_t src2) {
        return (opcode << 24) | (dest << 20) | (src1 << 16) | (src2 << 12);
    }

    uint32_t CodeGen::encode_I(uint8_t opcode, uint8_t dest, uint8_t src, uint16_t imm) {
        return (opcode << 24) | (dest << 20) | (src << 16) | (imm);
    }

    uint32_t CodeGen::encode_M(uint8_t opcode, uint8_t reg, uint16_t adr) {
        return (opcode << 24) | (reg << 20) | (adr);
    }

    uint32_t CodeGen::encode_J(uint8_t opcode, uint16_t adr) {
        return (opcode << 24) | (adr);
    }

    uint32_t CodeGen::encode_S(uint8_t opcode, uint8_t reg) {
        return (opcode << 24) | (reg << 20);
    }

    uint32_t CodeGen::encode_N(uint8_t opcode) {
        return (opcode << 24);
    }

    void CodeGen::write_inst(std::ofstream& output, uint32_t encoded_bytes) {

    }

    void CodeGen::generate(std::ofstream& output, const instruction_mod::Inst& inst) {
        uint32_t encoded_inst{0};
        uint32_t encoded_opcode{0};
        switch (inst.inst_type) {
            case instruction_mod::InstType::R:
            case instruction_mod::InstType::I:
            case instruction_mod::InstType::M:
            case instruction_mod::InstType::J:
            case instruction_mod::InstType::S:
            case instruction_mod::InstType::N:
                std::visit(overload{
                    [&inst, &encoded_opcode](OpCode oc) {
                        auto map_res = opcode_mapping.find(oc);
                        if (map_res == opcode_mapping.end()) { 
                            panic::panic();
                        } else {
                            encoded_opcode = map_res->second;
                        } 
                    },
                    [](auto) { panic::panic(); }
                }, inst.token_arr[0]->value);
        }
    }

}