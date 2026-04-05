#include "analyzer.h"

using instruction_mod::OpCode;
using TT = instruction_mod::TokenType;

namespace analyzer_mod {

    inline std::optional<instruction_mod::TokenOpt> OPT(TT t) {
        return instruction_mod::TokenOpt{t};
    }

    inline std::optional<instruction_mod::TokenOpt> OPT(std::initializer_list<TT> ts) {
        return instruction_mod::TokenOpt{ts};
    }

    const ValidationMap validation_map {

        { OpCode::LOAD, { OPT(TT::Register) , OPT(TT::Address) , std::nullopt } }, 
    };

}