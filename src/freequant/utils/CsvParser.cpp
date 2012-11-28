#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

#include <freequant/Exception.h>
#include "CsvParser.h"

using namespace std;

namespace FreeQuant {

CsvParser::CsvParser(bool hasHeader, char delim, char enclosing) :
    _delim(delim), _skippedRows(0),
    _hasHeader(hasHeader) {
}

CsvParser::~CsvParser() {
    if (fin.is_open()) fin.close();
}

void CsvParser::load(const std::string& filename) {
    boost::filesystem::path path(filename);
    if (!boost::filesystem::exists(path) || boost::filesystem::is_directory(path)) {
        throw InvalidPath(filename);
    }

    if (fin.is_open()) fin.close();

    fin.open(filename.c_str());
    if (!fin.is_open()) {
        // TODO
        throw InvalidPath(filename);
    }
    _cols.clear();
    if (hasMore()) {
        columns = row();
        int i = 0;
        for_each(columns.begin(), columns.end(), [&](const std::string& str) {
            _cols.insert(make_pair(str, i++));
        });
    }
}

void CsvParser::rewind() {
    fin.seekg(0);
    int nrow = _skippedRows;
    if (_hasHeader) {
        ++nrow;
    }
    skip(nrow);
}

std::size_t CsvParser::rowCount() {
    long long count = 0;
    if (fin.is_open()) {
        struct TestEol {
            TestEol() : last(0) {}
            bool operator()(char c) {
                last = c;
                return last == '\n';
            }
            char last;
        };
        TestEol test;
        auto pos = fin.tellg();
        fin.seekg(0);
        count = count_if(istreambuf_iterator<char>(fin), istreambuf_iterator<char>(), test);
        if (test.last != '\n') {
            ++count;
        }
        fin.seekg(pos);
    }
    return count;
}

void CsvParser::setSkipRows(int rows) {
    _skippedRows = rows;
}

bool CsvParser::hasMore() {
    return fin.peek() != EOF;
}

void CsvParser::skip(int nrow) {
    for (int i = 0; i < nrow; ++i)
        row();
}

CsvParser::Row CsvParser::row() {
    string line;
    getline(fin, line);

    vector<string> fields;
    if (line.size() > 0) {
        using namespace boost::algorithm;
        split(fields, line, boost::is_any_of(","), boost::token_compress_on);
        for_each(fields.begin(), fields.end(), [](string& str) {
            if (boost::algorithm::starts_with(str, "\"") && boost::algorithm::ends_with(str, "\"")) {
                 boost::algorithm::replace_first(str, "\"", "");
                 boost::algorithm::replace_last(str, "\"", "");
            }
//            boost::algorithm::trim(str);
        });
    }
    return fields;
}

} // namespace FreeQuant
