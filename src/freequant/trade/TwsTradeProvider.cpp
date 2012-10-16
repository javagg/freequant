#include <iostream>

#include <boost/algorithm/string.hpp>

#include "TwsTradeProvider.h"
#include "Order.h"
#include "Contract.h"

namespace FreeQuant {

TwsTradeProvider::TwsTradeProvider() : _socket(new EPosixClientSocket(this)) {

}

std::vector<std::string> TwsTradeProvider::availableAccounts() const {
    _socket->reqManagedAccts();
    return std::vector<std::string>();
}

void TwsTradeProvider::updateAccounts() {
    std::string code = _accoutCodes.front();
    _socket->reqAccountUpdates(true, code);
}

void TwsTradeProvider::updateAccountValue(const IBString& key, const IBString& val,
    const IBString& currency, const IBString& accountName) {

}

void TwsTradeProvider::updatePortfolio(const Contract& contract, int position,
    double marketPrice, double marketValue, double averageCost,
    double unrealizedPNL, double realizedPNL, const IBString& accountName) {

}

void TwsTradeProvider::updateAccountTime(const IBString& timeStamp) {
    std::cout << "timeStamp: " << timeStamp << std::endl;
}

void TwsTradeProvider::accountDownloadEnd(const IBString& accountName) {
    std::cout << "accountName: " << accountName << std::endl;
}

void TwsTradeProvider::managedAccounts(const IBString& accountsList) {

    std::vector<std::string> accounts;
    boost::split(accounts, accountsList, boost::is_any_of(","), boost::token_compress_on); // SplitVec == { "hello abc","ABC","aBc goodbye" }


//        split_vector_type SplitVec; // #2: Search for tokens
//        split( SplitVec, str1, is_any_of("-*"), token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }

//    accountsList

//    The comma delimited list of FA managed accounts.
}

void TwsTradeProvider::sendOrder(FreeQuant::Order& order) {
    OrderId orderId = 111;
    Contract contract;
    ::Order o;
    _socket->placeOrder(orderId, contract, o);
}
void TwsTradeProvider::cancelOrder(FreeQuant::Order& order) {
    OrderId orderId = 111;
    _socket->cancelOrder(orderId);
}
void TwsTradeProvider::replaceOrder(FreeQuant::Order& order) {
}

} // namespace FreeQuant
