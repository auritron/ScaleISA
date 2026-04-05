#pragma once

#include <array>
#include <optional>

#include "instructions.h"
#include "errorlist.h"

namespace analyzer_mod {

    using ValidationMap = std::unordered_map<instruction_mod::OpCode, 
        std::array<std::optional<instruction_mod::TokenOpt>, instruction_mod::Inst::INST_SIZE - 1>>; //size is 3 by default
    extern const ValidationMap validation_map;

    class Analyzer {

        public:

            void analyze(const instruction_mod::Pipeline& pipeline) const;
            void raise_semantic_error(Error::SemanticError e);

    };

}