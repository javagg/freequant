#include <iostream>
#include <functional>
#include <random>
#include <string>

#include <boost/phoenix.hpp>

#include <quickfix/Exceptions.h>
#include <quickfix/FixFields.h>
#include <quickfix/fix44/ExecutionReport.h>
#include <quickfix/fix44/NewOrderSingle.h>

#include <quickfix/fix44/DontKnowTrade.h>
#include <quickfix/fix44/MarketDataRequest.h>
#include <quickfix/fix44/MarketDataRequestReject.h>
#include <quickfix/fix44/MarketDataIncrementalRefresh.h>
#include <quickfix/fix44/MarketDataSnapshotFullRefresh.h>
#include <quickfix/fix44/Logon.h>
#include <quickfix/fix44/Logout.h>
#include <quickfix/fix44/OrderCancelReject.h>
#include <quickfix/fix44/QuoteStatusReport.h>
#include <quickfix/fix44/RequestForPositions.h>
#include <quickfix/fix44/Reject.h>
#include <quickfix/fix44/SecurityList.h>
#include <quickfix/fix44/SecurityListRequest.h>
#include <quickfix/fix44/SecurityTypes.h>
#include <quickfix/fix44/SecurityTypeRequest.h>
#include <quickfix/fix44/SecurityDefinition.h>
#include <quickfix/fix44/SecurityDefinitionRequest.h>
#include <quickfix/fix44/TradeCaptureReport.h>
#include <quickfix/fix44/TradeCaptureReportAck.h>
#include <quickfix/fix44/TradingSessionStatus.h>
#include <quickfix/fix44/UserResponse.h>

#include <quickfix/fix44/SecurityTypeRequest.h>

#include <quickfix/Session.h>

#include <freequant/utils/RandomMarketDataGenerator.h>
#include <freequant/utils/Utility.h>

#include "Executor.h"


using namespace std;
using namespace boost::phoenix;

namespace FreeQuant {

Executor::Executor() {
    _mdGenerator.reset(new FreeQuant::RandomMarketDataGenerator());
    _timerMd.reset(new FreeQuant::Timer(1000, boost::bind(&Executor::generateBars, this)));
    _timerMd->start();
}

Executor::~Executor() {
}

void Executor::onCreate(const FIX::SessionID& sessionID) {
    cout << __FUNCTION__ << ": " << sessionID << endl;
}


void Executor::onLogon(const FIX::SessionID& sessionID) {
    cout << __FUNCTION__ << ": " << sessionID << endl;
}


void Executor::onLogout(const FIX::SessionID& sessionID) {
//    _sessionIDs.remove(sessionID);
}

void Executor::toAdmin(FIX::Message& message, const FIX::SessionID& sessionID) {
    crack(message, sessionID);
}

void Executor::toApp(FIX::Message& message, const FIX::SessionID& sessionID) throw(FIX::DoNotSend) {
    crack(message, sessionID);
}

void Executor::fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionID)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {
    crack(message, sessionID);
}

void Executor::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
        throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    crack(message, sessionID);
}

void Executor::onMessage(const FIX44::NewOrderSingle& message, const FIX::SessionID& sessionID) {
    FIX::ClOrdID clOrdID;
    message.get(clOrdID);
    FIX::Side side;
    message.get(side);
    FIX::Symbol symbol;
    message.get(symbol);

    FIX44::ExecutionReport response;
    response.set(clOrdID);
    response.set(FIX::ExecID("fssfsf"));
    response.set(FIX::ExecType(FIX::ExecType_REJECTED));
    response.set(FIX::OrdStatus(FIX::OrdStatus_REJECTED));
    response.set(symbol);
    response.set(side);

    FIX::LeavesQty leavesQty(11);
    FIX::CumQty cumQty(12);
    FIX::AvgPx avgPx(100.0);

    response.set(leavesQty);
    response.set(cumQty);
    response.set(avgPx);

//    FIX::Symbol symbol;
//  FIX::Side side;
//  FIX::OrdType ordType;
//  FIX::OrderQty orderQty;
//  FIX::Price price;
//  FIX::ClOrdID clOrdID;
//  FIX::Account account;

//  message.get( ordType );

//  if ( ordType != FIX::OrdType_LIMIT )
//    throw FIX::IncorrectTagValue( ordType.getField() );

//  message.get( symbol );
//  message.get( side );
//  message.get( orderQty );
//  message.get( price );
//  message.get( clOrdID );

//  FIX44::ExecutionReport executionReport = FIX44::ExecutionReport
//      ( FIX::OrderID( genOrderID() ),
//        FIX::ExecID( genExecID() ),
//        FIX::ExecType( FIX::ExecType_FILL ),
//        FIX::OrdStatus( FIX::OrdStatus_FILLED ),
//        side,
//        FIX::LeavesQty( 0 ),
//        FIX::CumQty( orderQty ),
//        FIX::AvgPx( price ) );

//  executionReport.set( clOrdID );
//  executionReport.set( symbol );
//  executionReport.set( orderQty );
//  executionReport.set( FIX::LastQty( orderQty ) );
//  executionReport.set( FIX::LastPx( price ) );

//  if( message.isSet(account) )
//    executionReport.setField( message.get(account) );

    FIX::Session::sendToTarget(response, sessionID);
}

void Executor::onMessage(const FIX44::Logon& message, const FIX::SessionID& sessionID) {
    FIX::Username username;
    FIX::Password password;
    message.get(username);
    message.get(password);

    string expected = "simuser";
    if (password != expected) {
         throw FIX::RejectLogon();
    }
}

void Executor::onMessage(const FIX44::MarketDataRequest& message, const FIX::SessionID& sessionID) {
    Symbols requested;
    FIX::NoRelatedSym numSyms;
    message.get(numSyms);

    for (int i = 1; i <= numSyms; i++) {
        FIX44::MarketDataRequest::NoRelatedSym group;
        message.getGroup(i, group);
        FIX::Symbol symbol;
        group.get(symbol);
        requested.push_back(symbol);
    }

    _mdGenerator->addSymbols(requested);
    Symbols& subscribed = _subscriptions[sessionID];
    subscribed.insert(subscribed.end(), requested.begin(), requested.end());
//    _subscriptions[sessionID] = subscribed;
//    _subscriptions.insert()
    //    std::set<std::string> allSyms;
//    for (auto i = _subscriptions.begin(); i != _subscriptions.end(); i++) {
//        std::set<std::string>& syms = i->second;
//        allSyms.insert(syms.begin(), syms.end());
//    }
//    _mdGenerator->setSymbols(std::vector<std::string>(requestedSymbols.begin(), requestedSymbols.end()));


//    FIX::SubscriptionRequestType subscriptionRequestType;
//    message.get(subscriptionRequestType);
//    if (subscriptionRequestType == FIX::SubscriptionRequestType_DISABLE_PREVIOUS_SNAPSHOT_PLUS_UPDATE_REQUEST) {
//        std::set<std::string> result;
//        std::set_difference(subscribedSymbols.begin(), subscribedSymbols.end(),
//            requestSymbols.begin(), requestSymbols.end(), std::inserter(result, result.end()));
//        subscribedSymbols = result;
//    } else if (subscriptionRequestType == FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES) {
//        subscribedSymbols.insert(requestSymbols.begin(), requestSymbols.end());
//    }
//    _subscriptions[sessionID] = subscribedSymbols;


//    FIX::MDReqID mdReqID;

//    FIX::MarketDepth marketDepth;
//    FIX::MDUpdateType mdUpdateType;
//    FIX::AggregatedBook aggregatedBook;
//    FIX::OpenCloseSettleFlag settleFlag;
//    FIX::Scope scope;
//    FIX::MDImplicitDelete mdImplicitDelete;
//    FIX::NoMDEntryTypes noMDEntryTypes;

//    message.get(mdReqID);
//    message.get(subscriptionRequestType);

//    message.get(marketDepth);
//    message.get(mdUpdateType);
//    message.get(aggregatedBook);
//    message.get(scope);
//    message.get(mdImplicitDelete);
//    message.get(noMDEntryTypes);

//    _sessionID = sessionID;
//    FIX44::MarketDataSnapshotFullRefresh mdFull;

//    mdFull.set(mdReqID);
//    mdFull.set(FIX::Symbol("GOOG"));
//    mdFull.set(FIX::SecurityID("GOOG"));
//    mdFull.set(FIX::SecurityIDSource());
//    mdFull.set(FIX::Product());
//    mdFull.set(FIX::CFICode());
//    mdFull.set(FIX::SecurityType(FIX::SecurityType_COMMONSTOCK));
//    mdFull.set(FIX::MaturityMonthYear("2012"));
//    mdFull.set(FIX::MaturityDate("2012-12-11"));
//    mdFull.set(FIX::CouponPaymentDate("2012-12-11"));
//    mdFull.set(FIX::IssueDate("2012-12-11"));
//    mdFull.set(FIX::RepoCollateralSecurityType(1));
//    mdFull.set(FIX::RepurchaseTerm(1));
//    mdFull.set(FIX::RepurchaseRate(0.3));
//    mdFull.set(FIX::Factor(0.1));
//    mdFull.set(FIX::CreditRating("AAA"));
//    mdFull.set(FIX::InstrRegistry("DD"));
//    mdFull.set(FIX::CountryOfIssue);
//    mdFull.set(FIX::StateOrProvinceOfIssue);
//    mdFull.set(FIX::LocaleOfIssue);
//    mdFull.set(FIX::RedemptionDate);
//    mdFull.set(FIX::StrikePrice(99.99));
//    mdFull.set(FIX::OptAttribute('d'));
//    mdFull.set(FIX::ContractMultiplier(1));
//    mdFull.set(FIX::CouponRate(0.2));
//    mdFull.set(FIX::SecurityExchange("NYEX"));
//    mdFull.set(FIX::Issuer("sf"));
//    mdFull.set(FIX::EncodedIssuerLen(10));
//    mdFull.set(FIX::EncodedIssuer("sf"));
//    mdFull.set(FIX::SecurityDesc("dadad"));
//    mdFull.set(FIX::EncodedSecurityDescLen(20));
//    mdFull.set(FIX::EncodedSecurityDesc("fdfs"));
//    mdFull.set(FIX::NoSecurityAltID(1));

//    mdInc.set(mdReqID);
//    FIX::NoMDEntries count;

//    mdFull.set(FIX::NoMDEntries(2));
//    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries mdEntries1;
//    mdEntries1.set(FIX::MDEntryType(FIX::MDEntryType_BID));
//    mdEntries1.set(FIX::MDEntryPx(100));
//    mdEntries1.set(FIX::MDEntrySize(1));

//    mdFull.addGroup(mdEntries1);
//    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries mdEntries2;
//    mdEntries2.set(FIX::MDEntryType(FIX::MDEntryType_OFFER));
//    mdEntries2.set(FIX::MDEntryPx(110));
//    mdEntries2.set(FIX::MDEntrySize(2));

//    mdFull.addGroup(mdEntries2);

//    try {
//        FIX::Session::sendToTarget(mdFull, sessionID);
//    } catch (FIX::SessionNotFound&) {}
}

void Executor::onMessage(const FIX44::OrderCancelRequest& message, const FIX::SessionID& sessionID) {
    FIX44::OrderCancelReject response;
    FIX::Session::sendToTarget(response, sessionID);
}

void Executor::onMessage(const FIX44::OrderCancelReplaceRequest& message, const FIX::SessionID& sessionID) {
    FIX44::Reject response;
    FIX::Session::sendToTarget(response, sessionID);
}

void Executor::onMessage(const FIX44::SecurityDefinitionRequest& message, const FIX::SessionID& sessionID) {
    FIX::SecurityReqID regID;
    FIX::Symbol symbol;
    message.get(regID);
    message.get(symbol);

    FIX44::SecurityDefinition response;
    response.set(regID);
    response.set(FIX::SecurityResponseID("dfsfs"));
    response.set(FIX::SecurityResponseType(FIX::SecurityResponseType_LIST_OF_SECURITIES_RETURNED_PER_REQUEST));
    response.set(symbol);
    response.set(FIX::MaturityDate("2012-11-30"));
    FIX::Session::sendToTarget(response, sessionID);
}

void Executor::generateBars() {
    std::vector<FreeQuant::Bar> bars = _mdGenerator->generate();
    if (bars.empty()) return;

    std::map<std::string, FreeQuant::Bar> barMap;
    for (auto i = bars.begin(); i != bars.end(); i++) {
        FreeQuant::Bar& bar = *i;
        barMap[bar.symbol()] = bar;
    }
    for (auto i = _subscriptions.begin(); i != _subscriptions.end(); i++) {
        auto symbols = i->second;
        for (auto j = symbols.begin(); j != symbols.end(); j++) {
            auto bar = barMap[*j];
            sendBar(i->first, bar);
        }
    }
}

void Executor::sendBar(const FIX::SessionID& sessionID, const FreeQuant::Bar& bar) {
    FIX44::MarketDataSnapshotFullRefresh message;
    message.set(FIX::MDReqID(FreeQuant::createGuid()));
    message.set(FIX::Symbol(bar.symbol()));
//    message.set(FIX::NoMDEntries(2));

    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
    group.set(FIX::MDEntryType(FIX::MDEntryType_OPENING_PRICE));
    group.set(FIX::MDEntryPx(bar.open()));
//    group.set(FIX::MDEntrySize(1));
    message.addGroup(group);

    group.set(FIX::MDEntryType(FIX::MDEntryType_CLOSING_PRICE));
    group.set(FIX::MDEntryPx(bar.close()));
//    group.set(FIX::MDEntrySize(2));
    message.addGroup(group);

    try {
        FIX::Session::sendToTarget(message, sessionID);
    } catch(FIX::SessionNotFound&) {}
}

} // namespace FreeQuant
