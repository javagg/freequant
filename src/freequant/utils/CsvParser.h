#ifndef FQ_UTILS_CSVPARSER_H
#define FQ_UTILS_CSVPARSER_H

namespace FreeQuant {

class CsvParser {
public:
    CsvParser(char delimiter = ',', char terminator = '\n')
        : _delimiter(delimiter), _terminator(terminator) {}
    bool load(const std::string filename);
    bool parse(const std::string content);

    char delimiter() const { return _delimiter; }
    char terminator() const { return _terminator; }
    void setSkipRows(int rows);
    int skippedRows() const { return _skippedRows; }
    bool hasMoreRows() const;
private:
    char _delimiter;
    char _terminator;
    int _skippedRows;
};

} // namespace FreeQuant

#endif // FQ_UTILS_CSVPARSER_H
