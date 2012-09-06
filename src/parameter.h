#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

namespace FreeQuant {

class Parameter {
public:
	Parameter();
	virtual ~Parameter();

    std::string name();

};

} /* namespace FreeQuant */

#endif /* PARAMETER_H */
