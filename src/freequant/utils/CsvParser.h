#ifndef FQ_UTILS_CSVPARSER_H
#define FQ_UTILS_CSVPARSER_H

#include <memory>
#include <vector>
#include <string>

class csv_parser;

namespace FreeQuant {

class CsvParser {
public:
    CsvParser(char delimiter = ',', char terminator = '\n', char enclosing = '\"');
    bool load(const std::string filename);
    void setSkipRows(int rows);
    void rewind();
    std::size_t rowCount();
    bool hasMore() const;
    std::vector<std::string> row();

private:
    std::auto_ptr<csv_parser> _parser;
};

} // namespace FreeQuant

#endif // FQ_UTILS_CSVPARSER_H
