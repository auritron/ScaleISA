#pragma once

namespace Error {

    enum class ParsingError {
        IncorrectAddressFmt,
        ImmediateValueError,
        IdentifierNamingError,
        LabelNamingError,
        AddressNamingError,
        UnknownCharError,
    };

}