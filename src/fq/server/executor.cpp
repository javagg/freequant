#include <iostream>
#include <string>

#include "executor.h"

#include <quickfix/Exceptions.h>
#include <quickfix/FixFields.h>
#include <quickfix/fix40/ExecutionReport.h>
#include <quickfix/fix41/ExecutionReport.h>
#include <quickfix/fix42/ExecutionReport.h>
#include <quickfix/fix43/ExecutionReport.h>
#include <quickfix/fix44/ExecutionReport.h>
#include <quickfix/fix50/ExecutionReport.h>
#include <quickfix/fix42/MarketDataRequest.h>
#include <quickfix/fix42/Logon.h>
#include <quickfix/fix43/Logon.h>
#include <quickfix/Session.h>

using namespace std;

namespace FreeQuant { namespace Server {

void Executor::onCreate(const FIX::SessionID& sessionID) {
    cerr << "Executor::onCreate" << endl;
}


void Executor::onLogon(const FIX::SessionID& sessionID) {
    cerr << "Executor::onLogon" << endl;
}


void Executor::onLogout(const FIX::SessionID& sessionID) {
    cerr << "Executor::onLogout" << endl;
}

void Executor::toAdmin(FIX::Message& message, const FIX::SessionID& sessionID) {
//    cerr << "Executor::toAdmin" << endl;
}

void Executor::toApp(FIX::Message& message, const FIX::SessionID& sessionID) throw(FIX::DoNotSend) {
//    cerr << "Executor::toApp" << endl;

}

void Executor::fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionID)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {
//    cerr << "Executor::fromAdmin" << endl;
    crack(message, sessionID);
}

void Executor::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
        throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
//    cerr << "Executor::fromApp" << endl;
    crack(message, sessionID);
}

void Executor::onMessage(const FIX43::NewOrderSingle& message, const FIX::SessionID& sessionID) {
  FIX::Symbol symbol;
  FIX::Side side;
  FIX::OrdType ordType;
  FIX::OrderQty orderQty;
  FIX::Price price;
  FIX::ClOrdID clOrdID;
  FIX::Account account;

  message.get( ordType );

  if ( ordType != FIX::OrdType_LIMIT )
    throw FIX::IncorrectTagValue( ordType.getField() );

  message.get( symbol );
  message.get( side );
  message.get( orderQty );
  message.get( price );
  message.get( clOrdID );

  FIX43::ExecutionReport executionReport = FIX43::ExecutionReport
      ( FIX::OrderID( genOrderID() ),
        FIX::ExecID( genExecID() ),
        FIX::ExecType( FIX::ExecType_FILL ),
        FIX::OrdStatus( FIX::OrdStatus_FILLED ),
        side,
        FIX::LeavesQty( 0 ),
        FIX::CumQty( orderQty ),
        FIX::AvgPx( price ) );

  executionReport.set( clOrdID );
  executionReport.set( symbol );
  executionReport.set( orderQty );
  executionReport.set( FIX::LastQty( orderQty ) );
  executionReport.set( FIX::LastPx( price ) );

  if( message.isSet(account) )
    executionReport.setField( message.get(account) );

  try
  {
    FIX::Session::sendToTarget( executionReport, sessionID );
  }
  catch ( FIX::SessionNotFound& ) {}
}

void Executor::onMessage(const FIX43::Logon& message, const FIX::SessionID& sessionID) {
    cerr << "Logon message: " << message << sessionID << endl;

    FIX::Username username;
    FIX::Password password;
//    message.get(username);
//    message.get(password);

    string expected  = "12345";

//    if (password != expected) {
//         throw new FIX::RejectLogon();
//    }
}

//void Executor::updateOrder(const Order& order, char status) {
/*    FIX::TargetCompID targetCompID(order.getOwner());
    FIX::SenderCompID senderCompID(order.getTarget());

  FIX42::ExecutionReport fixOrder
  ( FIX::OrderID ( order.getClientID() ),
    FIX::ExecID ( m_generator.genExecutionID() ),
    FIX::ExecTransType ( FIX::ExecTransType_NEW ),
    FIX::ExecType ( status ),
    FIX::OrdStatus ( status ),
    FIX::Symbol ( order.getSymbol() ),
    FIX::Side ( convert( order.getSide() ) ),
    FIX::LeavesQty ( order.getOpenQuantity() ),
    FIX::CumQty ( order.getExecutedQuantity() ),
    FIX::AvgPx ( order.getAvgExecutedPrice() ) );

  fixOrder.set( FIX::ClOrdID( order.getClientID() ) );
  fixOrder.set( FIX::OrderQty( order.getQuantity() ) );

  if ( status == FIX::OrdStatus_FILLED ||
       status == FIX::OrdStatus_PARTIALLY_FILLED )
  {
    fixOrder.set( FIX::LastShares( order.getLastExecutedQuantity() ) );
    fixOrder.set( FIX::LastPx( order.getLastExecutedPrice() ) );
  }

  try
  {
    FIX::Session::sendToTarget( fixOrder, senderCompID, targetCompID );
  }
  catch ( FIX::SessionNotFound& ) {}*/
//}

//void Executor::rejectOrder(const FIX::SenderCompID& sender, const FIX::TargetCompID& target,
//        const FIX::ClOrdID& clOrdID, const FIX::Symbol& symbol,
//        const FIX::Side& side, const std::string& message) {
//    FIX::TargetCompID targetCompID(sender.getValue());
//    FIX::SenderCompID senderCompID(target.getValue());

//    FIX42::ExecutionReport fixOrder(FIX::OrderID(clOrdID.getValue()), FIX::ExecID (m_generator.genExecutionID()),
//        FIX::ExecTransType ( FIX::ExecTransType_NEW), FIX::ExecType(FIX::ExecType_REJECTED),
//        FIX::OrdStatus(FIX::ExecType_REJECTED), symbol, side, FIX::LeavesQty(0), FIX::CumQty(0), FIX::AvgPx(0));

//    fixOrder.set(clOrdID);
//    fixOrder.set(FIX::Text(message));
//    try {
//        FIX::Session::sendToTarget(fixOrder, senderCompID, targetCompID);
//    } catch (FIX::SessionNotFound&) {}
//}

//void Executor::processOrder(const Order& order) {
//    if (m_orderMatcher.insert(order)) {
//        acceptOrder(order);
//        std::queue <Order> orders;
//        m_orderMatcher.match(order.getSymbol(), orders);


//        while (orders.size()) {
//            fillOrder(orders.front());
//            orders.pop();
//        }
//    } else {
//        rejectOrder(order);
//    }
//}

//void Executor::processCancel(const std::string& id, const std::string& symbol, Order::Side side) {
////    Order& order = m_orderMatcher.find(symbol, side, id);
////    order.cancel();
////    cancelOrder(order);
////    m_orderMatcher.erase(order);
//}

}}
