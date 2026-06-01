#pragma once

#include <vector>
#include <variant>
#include <concepts>
#include <string_view>

namespace error {

    enum class ParsingError {
        ImmediateValueError,
        IdentifierNamingError,
        LabelNamingError,
        AddressNamingError,
        UnknownCharError,
        RegisterOutOfRange,
        ImmediateValueTooBig,
        AddressOutOfRange,
        InstructionTooLong,
    };

    enum class SemanticError {
        MissingOpCodeError,
        IncorrectFirstToken,
        IncorrectOperandFmt,
        UnknownSemanticError,
        InvalidOpCodePosition,
        RegisterOutOfRange,
        ImmediateOutOfRange,
        AddressOutOfRange,
        LabelAlreadyExists,
        LabelTooLongError,
        UndefinedLabelError,
    };

    template <typename T>
    concept Err = std::same_as<T, ParsingError> || std::same_as<T, SemanticError>;

    class Error {

        public:

            std::variant<ParsingError, SemanticError> error;
            size_t err_line;
            size_t err_col;


            Error() = delete;

            Error(Err auto error, size_t err_ln, size_t err_cl) :
                error{error},
                err_line{err_ln},
                err_col{err_cl}
            { }

            std::string_view fmt_error_as_str();

    };

}