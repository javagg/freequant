#include "FixServer.h"

using namespace FIX;

namespace FreeQuant {

FixServer::FixServer() {}

FixServer::FixServer(const std::string& filename) {}
FixServer::~FixServer() {}
void FixServer::onCreate(const FIX::SessionID&) {}
void FixServer::onLogon(const FIX::SessionID&) {}
void FixServer::onLogout(const FIX::SessionID&) {}
void FixServer::toAdmin(FIX::Message&, const FIX::SessionID&) {}
void FixServer::toApp(FIX::Message&, const FIX::SessionID&) throw(FIX::DoNotSend) {}
void FixServer::fromAdmin(const FIX::Message&, const FIX::SessionID&)
    throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {}
void FixServer::fromApp(const FIX::Message&, const FIX::SessionID&)
    throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) {}
}
