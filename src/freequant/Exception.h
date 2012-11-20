#ifndef FQ_EXCEPTION_H
#define FQ_EXCEPTION_H

#include <stdexcept>

namespace FreeQuant {

class Exception : public std::logic_error {
public:
    explicit Exception(const std::string& message) : logic_error(message) {}
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

}

#endif // FQ_EXCEPTION_H
