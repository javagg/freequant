#include <boost/filesystem.hpp>

#include "CsvParser.h"
#include <csv_parser/csv_parser.hpp>

namespace FreeQuant {

CsvParser::CsvParser(char delimiter, char terminator, char enclosing) : _parser(new csv_parser) {
    _parser->set_enclosed_char(enclosing, ENCLOSURE_OPTIONAL);
    _parser->set_field_term_char(delimiter);
    _parser->set_line_term_char(terminator);
}

bool CsvParser::load(const std::string filename) {
    boost::filesystem::path path(filename);
    if (!boost::filesystem::exists(path) || boost::filesystem::is_directory(path)) {
        return false;
    }
    _parser->init(filename.c_str());
    return true;
}

void CsvParser::rewind() {
    _parser->reset_record_count();
}

std::size_t CsvParser::rowCount() {
    return _parser->get_record_count();
}

void CsvParser::setSkipRows(int rows) {
    _parser->set_skip_lines(rows);
}

bool CsvParser::hasMore() const {
    return _parser->has_more_rows();
}

std::vector<std::string> CsvParser::row() {
    return _parser->get_row();
}

} // namespace FreeQuant
