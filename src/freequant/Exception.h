#ifndef FQ_EXCEPTION_H
#define FQ_EXCEPTION_H

#include <stdexcept>

namespace FreeQuant {

class Exception : public std::logic_error {
public:
    virtual ~Exception() throw() {}
};

class ConfigException :  public Exception {

};

class SocketException : public Exception {

};

class RuntimeError : public Exception {

};

class OrderTypeNotSupport : public Exception {

};

}

#endif // FQ_EXCEPTION_H
