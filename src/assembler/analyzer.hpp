#pragma once

#include <array>
#include <optional>
#include <expected>
#include <string_view>
#include <unordered_set>

#include "instructions.hpp"
#include "error.hpp"

namespace analyzer_mod {

    using error::Error;
    using SemErr = error::SemanticError;

    using Opt = std::optional<instruction_mod::TokenOpt>;
    using Fmt = std::array<Opt, instruction_mod::Inst::INST_SIZE - 1>; // 3 by default

    using InstructionFmt = std::unordered_map<instruction_mod::OpCode, Fmt>;
    extern const InstructionFmt instruction_fmt;    

    class Analyzer {

        private:

            size_t priv_inst_count;

        public:

            Analyzer();
            std::expected<void, Error> scout_lbl(instruction_mod::Inst& inst, std::unordered_map<std::string, size_t>& label_table); // :D
            std::expected<void, Error> validate_token(const instruction_mod::Token& token, const std::unordered_map<std::string, size_t>& label_table) const ; // :D
            std::expected<void, Error> validate_opcode(instruction_mod::Inst& inst, instruction_mod::OpCode opcode, const std::unordered_map<std::string, size_t>& label_table) const; // :D
            std::expected<void, Error> analyze(instruction_mod::Inst& inst, const std::unordered_map<std::string, size_t>& label_table) const; // :D
            void RI_inst_classify(instruction_mod::Inst& inst) const; // !

    };

}