#include <string>
#include <sstream>

#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/time_facet.hpp>


#include "yahooprovider.h"

using namespace std;
using namespace boost;


namespace FreeQuant { namespace MarketData {

static string format = "http://download.finance.yahoo.com/d/quotes.csv?s=%1%&f=%2%";

YahooProvider::YahooProvider() {

}

YahooProvider::~YahooProvider() {

}

void YahooProvider::connect() {
    if (timer == nullptr) {
        timer = new FreeQuant::Utils::Timer(1, std::bind(&YahooProvider::getQuota, this));
//        timer->connect(boost::bind(&YahooProvider::getQuota, this));
        timer->start();
    }
}

void YahooProvider::disconnect() {
    if (timer != nullptr) {
        delete timer;
        timer = 0;
    }
}

void YahooProvider::getQuota() {
    string url = str(boost::format(format) % "000001.ss" % "d1t1k3l1");
    std::cout << url << std::endl;
    string contents = client.get(url);

    vector<string> items;
    string token;
    istringstream iss(contents);
    while (getline(iss, token, ',')) {
         trim(token);
         if (token.at(0) == '"' ) {
             token.erase(0, 1);
             token.erase(token.size()-1);
         }

         items.push_back(token);
    }
//    date_time dt;
//    stringstream ss(items.at(0));

    boost::posix_time::time_facet *facet = new boost::posix_time::time_facet("%m/%d/%Y-%H:%M");
    string time = items.at(1);
    time.erase(time.size()-2);

    string dt = items.at(0) + "-" + time;

    boost::posix_time::time_input_facet *tif = new boost::posix_time::time_input_facet("%m/%d/%Y-%H:%M");
//    tif->set_iso_extended_format();
    std::istringstream iss0(dt);
    iss0.imbue(std::locale(std::locale::classic(), tif));
    boost::posix_time::ptime abs_time;
    iss0 >> abs_time;
    std::cout << abs_time << std::endl;

    cout << dt <<endl;
    cout << time <<endl;
}

}}
