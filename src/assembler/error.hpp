#pragma once

#include <vector>
#include <variant>
#include <concepts>

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
    };

    template <typename T>
    concept Err = std::same_as<T, ParsingError> || std::same_as<T, SemanticError>;

    class Error {

        using ErrorType = std::variant<ParsingError, SemanticError>;
        ErrorType error;

        public:

            Error() = delete;
            Error(Err auto error);
            void display_error(Err auto error);

    };

}