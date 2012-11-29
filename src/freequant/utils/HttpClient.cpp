#include <curl/curl.h>
#include "HttpClient.h"

using namespace std;

namespace FreeQuant {

static int writer(char *data, size_t size, size_t nmemb, string *writerData) {
  if (writerData == nullptr)
    return 0;

  writerData->append(data, size*nmemb);
  return size*nmemb;
}

const string& HttpClient::get(const string& url) {
    buffer.clear();
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return buffer;
}

} // namespace FreeQuant
