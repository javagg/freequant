#include "executor.h"
#include "quickfix/Session.h"

#include "quickfix/fix40/ExecutionReport.h"
#include "quickfix/fix41/ExecutionReport.h"
#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix43/ExecutionReport.h"
#include "quickfix/fix44/ExecutionReport.h"
#include "quickfix/fix50/ExecutionReport.h"

namespace FreeQuant { namespace Server {

void Executor::onCreate(const FIX::SessionID& sessionID) {

}


void Executor::onLogon(const FIX::SessionID& sessionID) {

}


void Executor::onLogout(const FIX::SessionID& sessionID) {

}

void Executor::toAdmin(FIX::Message& message, const FIX::SessionID& sessionID) {

}

void Executor::toApp(FIX::Message& message, const FIX::SessionID& sessionID) throw(FIX::DoNotSend) {

}

void Executor::fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionID)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {

}

void Executor::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
        throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    crack(message, sessionID);
}

void Executor::onMessage(const FIX40::NewOrderSingle& message, const FIX::SessionID& sessionID) {
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

  FIX40::ExecutionReport executionReport = FIX40::ExecutionReport
      ( FIX::OrderID( genOrderID() ),
        FIX::ExecID( genExecID() ),
        FIX::ExecTransType( FIX::ExecTransType_NEW ),
        FIX::OrdStatus( FIX::OrdStatus_FILLED ),
        symbol,
        side,
        orderQty,
        FIX::LastShares( orderQty ),
        FIX::LastPx( price ),
        FIX::CumQty( orderQty ),
        FIX::AvgPx( price ) );

  executionReport.set( clOrdID );

  if( message.isSet(account) )
    executionReport.setField( message.get(account) );

  try
  {
    FIX::Session::sendToTarget( executionReport, sessionID );
  }
  catch ( FIX::SessionNotFound& ) {}
}

void Executor::onMessage( const FIX41::NewOrderSingle& message,
                             const FIX::SessionID& sessionID )
{
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

  FIX41::ExecutionReport executionReport = FIX41::ExecutionReport
      ( FIX::OrderID( genOrderID() ),
        FIX::ExecID( genExecID() ),
        FIX::ExecTransType( FIX::ExecTransType_NEW ),
        FIX::ExecType( FIX::ExecType_FILL ),
        FIX::OrdStatus( FIX::OrdStatus_FILLED ),
        symbol,
        side,
        orderQty,
        FIX::LastShares( orderQty ),
        FIX::LastPx( price ),
        FIX::LeavesQty( 0 ),
        FIX::CumQty( orderQty ),
        FIX::AvgPx( price ) );

  executionReport.set( clOrdID );

  if( message.isSet(account) )
    executionReport.setField( message.get(account) );

  try
  {
    FIX::Session::sendToTarget( executionReport, sessionID );
  }
  catch ( FIX::SessionNotFound& ) {}
}

void Executor::onMessage(const FIX42::NewOrderSingle& message, const FIX::SessionID& sessionID) {
    FIX::Symbol symbol;
    FIX::Side side;
    FIX::OrdType ordType;
    FIX::OrderQty orderQty;
    FIX::Price price;
    FIX::ClOrdID clOrdID;
    FIX::Account account;

    message.get(ordType);
    if (ordType != FIX::OrdType_LIMIT)
        throw FIX::IncorrectTagValue(ordType.getField());

    message.get(symbol);
    message.get(side);
    message.get(orderQty);
    message.get(price);
    message.get(clOrdID);

    FIX42::ExecutionReport executionReport = FIX42::ExecutionReport(FIX::OrderID(genOrderID()),
        FIX::ExecID(genExecID()),FIX::ExecTransType(FIX::ExecTransType_NEW), FIX::ExecType(FIX::ExecType_FILL),
        FIX::OrdStatus(FIX::OrdStatus_FILLED), symbol, side, FIX::LeavesQty(0), FIX::CumQty(orderQty),
        FIX::AvgPx(price));

    executionReport.set(clOrdID);
    executionReport.set(orderQty);
    executionReport.set(FIX::LastShares(orderQty));
    executionReport.set(FIX::LastPx(price));

    if (message.isSet(account))
        executionReport.setField(message.get(account));
    try {
        FIX::Session::sendToTarget(executionReport, sessionID);
    } catch (FIX::SessionNotFound&) {}
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

void Executor::onMessage( const FIX44::NewOrderSingle& message,
                             const FIX::SessionID& sessionID )
{
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

  FIX44::ExecutionReport executionReport = FIX44::ExecutionReport
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

void Executor::onMessage( const FIX50::NewOrderSingle& message,
                             const FIX::SessionID& sessionID )
{
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

  FIX50::ExecutionReport executionReport = FIX50::ExecutionReport
      ( FIX::OrderID( genOrderID() ),
        FIX::ExecID( genExecID() ),
        FIX::ExecType( FIX::ExecType_FILL ),
        FIX::OrdStatus( FIX::OrdStatus_FILLED ),
        side,
        FIX::LeavesQty( 0 ),
        FIX::CumQty( orderQty ) );
  
  executionReport.set( clOrdID );
  executionReport.set( symbol );
  executionReport.set( orderQty );
  executionReport.set( FIX::LastQty( orderQty ) );
  executionReport.set( FIX::LastPx( price ) );
  executionReport.set( FIX::AvgPx( price ) );

  if( message.isSet(account) )
    executionReport.setField( message.get(account) );

  try {
    FIX::Session::sendToTarget( executionReport, sessionID );
  }
  catch ( FIX::SessionNotFound& ) {}
}

void Executor::onMessage(const FIX42::OrderCancelRequest& message, const FIX::SessionID& sessionID) {

    FIX::OrigClOrdID origClOrdID;
    FIX::Symbol symbol;
    FIX::Side side;

//    message.get(origClOrdID);
//    message.get(symbol);
//    message.get(side);

    try {
//        processCancel( origClOrdID, symbol, convert(side));
    } catch (std::exception&) {}
}

void Application::onMessage(const FIX42::MarketDataRequest& message, const FIX::SessionID& sessionID) {
    FIX::MDReqID mdReqID;
    FIX::SubscriptionRequestType subscriptionRequestType;
    FIX::MarketDepth marketDepth;
    FIX::NoRelatedSym noRelatedSym;
    FIX42::MarketDataRequest::NoRelatedSym noRelatedSymGroup;

    message.get(mdReqID);
    message.get(subscriptionRequestType);
    if (subscriptionRequestType != FIX::SubscriptionRequestType_SNAPSHOT)
        throw(FIX::IncorrectTagValue(subscriptionRequestType.getField()));
    message.get(marketDepth);
    message.get(noRelatedSym);

    for (int i = 1; i <= noRelatedSym; ++i) {
        FIX::Symbol symbol;
        message.getGroup(i, noRelatedSymGroup);
        noRelatedSymGroup.get(symbol);
    }
}

void Executor::updateOrder(const Order& order, char status) {
    FIX::TargetCompID targetCompID(order.getOwner());
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
  catch ( FIX::SessionNotFound& ) {}}

void Executor::rejectOrder(const FIX::SenderCompID& sender, const FIX::TargetCompID& target,
        const FIX::ClOrdID& clOrdID, const FIX::Symbol& symbol,
        const FIX::Side& side, const std::string& message) {
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
}

void Application::processOrder(const Order& order) {
    if (m_orderMatcher.insert(order)) {
        acceptOrder(order);
        std::queue <Order> orders;
        m_orderMatcher.match(order.getSymbol(), orders);


        while (orders.size()) {
            fillOrder(orders.front());
            orders.pop();
        }
    } else {
        rejectOrder(order);
    }
}

void Executor::processCancel(const std::string& id, const std::string& symbol, Order::Side side) {
//    Order& order = m_orderMatcher.find(symbol, side, id);
//    order.cancel();
//    cancelOrder(order);
//    m_orderMatcher.erase(order);
}

}}
