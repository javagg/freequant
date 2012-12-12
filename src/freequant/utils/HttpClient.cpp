//#include <boost/network/protocol/http.hpp>
#include "HttpClient.h"

using namespace std;

namespace FreeQuant {

const string& HttpClient::get(const string& url) {
//    namespace http = boost::network::http;
//    namespace uri = boost::network::uri;
//    http::client client;
//    http::client::request request(url);
//    http::client::response response = client.get(request);
//    buffer = static_cast<std::string>(body(response));
    return buffer;
}

} // namespace FreeQuant
