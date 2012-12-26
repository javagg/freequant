#ifndef FQ_FIX_SERVER_H
#define FQ_FIX_SERVER_H

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>

namespace FreeQuant {

class FixServer : public FIX::Application, public FIX::MessageCracker {
public:
    FixServer();
    FixServer(const std::string& filename);
    virtual ~FixServer();
    void onCreate(const FIX::SessionID&);
    void onLogon(const FIX::SessionID&);
    void onLogout(const FIX::SessionID&);
    void toAdmin(FIX::Message&, const FIX::SessionID&);
    void toApp(FIX::Message&, const FIX::SessionID&) throw(FIX::DoNotSend);
    void fromAdmin(const FIX::Message&, const FIX::SessionID&)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon);
    void fromApp(const FIX::Message&, const FIX::SessionID&)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);

};

}

#endif // FQ_FIX_SERVER_H
