#include <iostream>

#include <boost/algorithm/string.hpp>

#include "TwsTradeProvider.h"

using namespace std;

namespace FreeQuant { namespace Trade {

TwsTradeProvider::TwsTradeProvider() : _socket(new EPosixClientSocket(this)) {

}

vector<string> TwsTradeProvider::availableAccounts() const {
    _socket->reqManagedAccts();
    return vector<string>();
}

void TwsTradeProvider::updateAccounts() {
    string code = _accoutCodes.front();
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
    cout << "timeStamp: " << timeStamp << endl;
}

void TwsTradeProvider::accountDownloadEnd(const IBString& accountName) {
    cout << "accountName: " << accountName << endl;
}

void TwsTradeProvider::managedAccounts(const IBString& accountsList) {

    vector<string> accounts;
    boost::split(accounts, accountsList, boost::is_any_of(","), boost::token_compress_on); // SplitVec == { "hello abc","ABC","aBc goodbye" }


//        split_vector_type SplitVec; // #2: Search for tokens
//        split( SplitVec, str1, is_any_of("-*"), token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }

//    accountsList

//    The comma delimited list of FA managed accounts.
}

}}
