#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

#include "YahooMarketDataGenerator.h"

using namespace std;

namespace FreeQuant {

static string format = "http://download.finance.yahoo.com/d/quotes.csv?s=%1%&f=%2%";

vector<string> YahooMarketDataGenerator::availableSymbols() const {
    return vector<string>();
}

FreeQuant::Bar YahooMarketDataGenerator::generate(string symbol) {
    string url = str(boost::format(format) % symbol % "d1t1k3l1");
    std::cout << url << std::endl;
    string content = _http.get(url);

    // "10/17/2012","3:01am",N/A,2105.618

    vector<string> items;
    string token;
    istringstream iss(content);
    while (getline(iss, token, ',')) {
         boost::trim(token);
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
    return FreeQuant::Bar(1,1,1,1,1);
}

} // namespace FreeQuant
