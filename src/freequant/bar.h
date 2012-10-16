#ifndef FQ_BAR_H
#define FQ_BAR_H

#include <freequant/utils/datetime.h>

namespace FreeQuant {

class Bar {
public:
    Bar();
    FreeQuant::DateTime beginTime() const;
    FreeQuant::DateTime endTime() const;
    double open() const;
    double high() const;
    double low() const;
    double close() const;
    long volume() const;
    long openInterest() const;
    long size() const;
    double median() const { return (high()+low())/2; }
    double typical() const { return (high()+low()+close())/3; }
    double weighted() const { return (high()+low()+2*close())/4; }

    friend inline std::ostream& operator<<(std::ostream &os, Bar& bar) {
//          cout << "class t(" << t1.v << ")" << endl;
          return os;
    }
    friend inline std::istream& operator>>(std::istream &is, Bar& bar){
//          cin >> t1.v;
          return is;
    }
};

}
#endif // FQ_BAR_H
