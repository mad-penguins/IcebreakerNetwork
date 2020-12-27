#ifndef ANTARCLICA_CODE_H
#define ANTARCLICA_CODE_H

#include <exception>
#include <utility>

using namespace std;

enum class Code {
    OK,
    NotFound,
    InvalidToken,
    FormParsingFailure,
    AlreadyExists,
    WrongCredentials,
    WrongMethod,
    Empty,
    DatabaseAccessProblem
};

class APIException : exception {
public:
    const Code code;
    const string str;

    APIException(Code code, string str) : code(code), str(std::move(str)) {}
};

#endif //ANTARCLICA_CODE_H
