#include "analyzer.h"

using instruction_mod::OpCode;
using TT = instruction_mod::TokenType;

namespace analyzer_mod {
    
    using Opt = std::optional<instruction_mod::TokenOpt>;
    using Fmt = std::array<Opt, instruction_mod::Inst::INST_SIZE - 1>; // 3 by default

    constexpr Opt OPT(TT t) { return instruction_mod::TokenOpt{t}; }
    constexpr Opt OPT(std::initializer_list<TT> ts) { return instruction_mod::TokenOpt{ts}; }

    constexpr Fmt DefineFmt(Opt a, Opt b, Opt c) {
        return Fmt{ a, b, c };
    }

    //destination is (almost) always first
    constexpr Fmt RegAdr() { return DefineFmt( OPT(TT::Register), OPT({TT::Address, TT::Variable}), std::nullopt ); }
    constexpr Fmt AdrReg() { return DefineFmt( OPT({TT::Address, TT::Variable}), OPT(TT::Register), std::nullopt ); }
    constexpr Fmt RegReg() { return DefineFmt( OPT(TT::Register), OPT(TT::Register), std::nullopt ); }
    constexpr Fmt RegImm() { return DefineFmt( OPT(TT::Register), OPT(TT::Immediate), std::nullopt ); }

    inline const InstructionFmt instruction_fmt {
        { OpCode::LOAD, RegAdr() },
        { OpCode::SEND, AdrReg() },
        { OpCode::COPY, RegReg() },
        { OpCode::SET,  RegImm() },
    };

}