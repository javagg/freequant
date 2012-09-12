#ifndef FQ_STRATEGY_PARAMETER_H
#define FQ_STRATEGY_PARAMETER_H

#include <string>

namespace FreeQuant { namespace Strategy {

class Parameter {
public:
	Parameter();
	virtual ~Parameter();

    std::string name();

};

}} /* namespace FreeQuant */

#endif /* FQ_STRATEGY_PARAMETER_H */
