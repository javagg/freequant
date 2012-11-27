#ifndef FQ_EXCEPTION_H
#define FQ_EXCEPTION_H

#include <stdexcept>

namespace FreeQuant {

class Exception : public std::logic_error {
public:
    explicit Exception(const std::string& message) : std::logic_error(message) {}
    virtual ~Exception() throw() {}
};

class ConfigError :  public Exception {

};

class SocketException : public Exception {

};

class RuntimeError : public Exception {

};

class OrderTypeNotSupport : public Exception {

};

class Timeout : public Exception {
public:
    explicit Timeout(const std::string& message) : Exception(message) {}
};

class InvalidPath : public Exception {
public:
    explicit InvalidPath(const std::string& message) : Exception(message) {}
};

class ConnectionTimeout : public std::runtime_error {
public:
    explicit ConnectionTimeout(const std::string& message) : std::runtime_error(message) {}
};

}

#endif // FQ_EXCEPTION_H
