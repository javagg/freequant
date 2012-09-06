#include <string>
#include <sstream>

#include <boost/format.hpp>
#include "yahooprovider.h"

using namespace std;

namespace FreeQuant { namespace MarketData {

static string format = "http://finance.yahoo.com/d/quotes.csv?s=%1%&f=%2%";

YahooProvider::YahooProvider() {

}

void YahooProvider::connect() {
    if (timer == 0) {
        timer = new FreeQuant::Utils::Timer(1);
        timer->start();
    }
}

void YahooProvider::disconnect() {
    if (timer != 0) {
        delete timer;
        timer == 0;
    }
}

void YahooProvider::getQuota() {
    string url = str(boost::format(format) % "MSFT" % "d1k3l1t1");
    string contents = client.get(url);

    //string line = "What,the,hell,are,you,say,in,mo,fo";
    vector<string> items;
    string token;
    istringstream iss(contents);
    while (getline(iss, token, ',')) {
         items.push_back(token);
         cout << token <<endl;
    }
}

}}
