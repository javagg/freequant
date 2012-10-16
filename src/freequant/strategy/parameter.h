#ifndef FQ_STRATEGY_PARAMETER_H
#define FQ_STRATEGY_PARAMETER_H

#include <string>

#include <boost/any.hpp>

namespace FreeQuant {

class Parameter {
public:
	Parameter();
	virtual ~Parameter();

    std::string name() { return m_name; }
    int toInt();
    std::string toString();
    double toDouble();

private:
    std::string m_name;
    boost::any m_value;
};

} // namespace FreeQuant

#endif /* FQ_STRATEGY_PARAMETER_H */
