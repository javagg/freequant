#include <string>

#include "yahooprovider.h"

using namespace std;
namespace FreeQuant { namespace MarketData {

static string url = "http://finance.yahoo.com/d/quotes.csv?s=<股票名称>&f=<数据列选项>";

YahooProvider::YahooProvider() {
}

}}
