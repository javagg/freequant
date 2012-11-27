#ifndef FQ_UTILS_CSVPARSER_H
#define FQ_UTILS_CSVPARSER_H

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

class csv_parser;

namespace FreeQuant {

class CsvParser {
public:
    typedef std::vector<std::string> Row;

    CsvParser(char delimiter = ',', char terminator = '\n', char enclosing = '\"');
    void load(const std::string& filename);
    void setSkipRows(int rows);
    void rewind();
    std::size_t rowCount();
    bool hasMore() const;
    Row row();

private:
    std::shared_ptr<csv_parser> _parser;
    std::vector<std::string> columns;
    std::map<std::string, int> _cols;
};

} // namespace FreeQuant

#endif // FQ_UTILS_CSVPARSER_H
