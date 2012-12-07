#ifndef FQ_STRATEGY_PORTFOLIO_H
#define FQ_STRATEGY_PORTFOLIO_H

namespace FreeQuant {

class Portfolio {
public:
    virtual void transactionAdded();
    virtual void positionOpened();
    virtual void positionClosed();
    virtual void positionChanged();
    virtual void valueChanged();
    virtual void cleared();
    virtual void compositionChanged();
    virtual void consolidationStarted();
    virtual void consolidationFinished();
    void addTran();
    void consolidate();
    double positionValue();
    double accountValue();
    double marginValue();
    double debtValue();
    double coreEquity();
    double totalEquity();
    double leverage();
    double debtEquityRatio();
    double cashFlow();
    double netCashFlow();
    double exposure();
};

}

#endif // FQ_STRATEGY_PORTFOLIO_H
