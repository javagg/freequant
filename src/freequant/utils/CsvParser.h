#ifndef FQ_UTILS_CSVPARSER_H
#define FQ_UTILS_CSVPARSER_H

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include <boost/shared_ptr.hpp>

class csv_parser;

namespace FreeQuant {

class CsvParser {
public:
    typedef std::vector<std::string> Row;

    CsvParser(bool header = true, char delim = ',', char enclosing = '\"');
    ~CsvParser();
    void load(const std::string& filename);
    void setSkipRows(int rows);
    void rewind();
    std::size_t rowCount();
    bool hasMore();
    Row row();

private:
    void skip(int nrow);
    char _delim;
    int _skippedRows;
    bool _hasHeader;
    std::ifstream fin;
    std::vector<std::string> columns;
    std::map<std::string, int> _cols;
};

} // namespace FreeQuant

#endif // FQ_UTILS_CSVPARSER_H
