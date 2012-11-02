#ifndef FQ_MANAGER_DATAMANAGER_H
#define FQ_MANAGER_DATAMANAGER_H

namespace FreeQuant {

class TimeSeries;

class DataManager {
public:
    void compressBars(const FreeQuant::TimeSeries& ts);
    void deleteBar();
    void deleteQuote();
    void deleteTrade();
};

} // namespace FreeQuant

#endif // FQ_MANAGER_DATAMANAGER_H
